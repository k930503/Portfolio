pragma solidity ^0.5.4;

import "./Storage.sol";
import "./SafeMath.sol";

contract Trade is Storage {
    
    event PurchaseProduct(address buyer, string productUuid, uint256 purchaseDeposit);
    event PurchaseCancel(address buyer, string productUuid);
    event SellApprove(address buyer, string productUuid, string encryptedIpfsKey);
    event SellReject(address buyer, string productUuid);
    
    using SafeMath for uint256;
    
    function purchaseProduct(string calldata _productUuid) external {

        Type.CustomerInfo storage c = customers[msg.sender];
        Type.ProductInfo  storage p = products[_productUuid];

        require(c.status != Type.CustomerStatus.NONMEMBER, "You must regist customer first");
        require(p.status == Type.ProductStatus.ON_SALE, "Product status is not ON_SALE");
        require(msg.sender != p.creator, "You cannot purchase your product");
        require(purchaseTable[msg.sender][_productUuid].status == Type.PurchaseStatus.NONE, "This product has already been requested to be purchased");

        purchaseTable[msg.sender][_productUuid] = Type.PurchaseInfo(p.creator, p.ipfsLink, "", p.hashValue, p.price, Type.PurchaseStatus.REQUEST);
        c.purchaseDeposit = c.purchaseDeposit.add(p.price);
        mm.transferFrom(msg.sender, address(this), p.price);

        emit PurchaseProduct(msg.sender, _productUuid, c.purchaseDeposit);
    }

    function purchaseCancel(string calldata _productUuid) external {

        Type.CustomerInfo storage c = customers[msg.sender];

        require(c.status != Type.CustomerStatus.NONMEMBER, "You must regist customer first");
        require(purchaseTable[msg.sender][_productUuid].status == Type.PurchaseStatus.REQUEST, "This product has not been requested by the buyer");

        uint256 amount = purchaseTable[msg.sender][_productUuid].price;

        delete purchaseTable[msg.sender][_productUuid];

        c.purchaseDeposit = c.purchaseDeposit.sub(amount);

        mm.transfer(msg.sender, amount);
        
        emit PurchaseCancel(msg.sender, _productUuid);
    }

    function sellApprove(address _buyer,
                         string calldata _productUuid,
                         string calldata _encryptedIpfsKey,
                         bool _isUseFeeCoupon) external {

        Type.ProductInfo  storage product  = products[_productUuid];
        Type.PurchaseInfo storage purchase = purchaseTable[_buyer][_productUuid];
        Type.CreatorInfo  storage creator  = creators[product.creator];
        Type.CustomerInfo storage buyer    = customers[_buyer];

        require(customers[msg.sender].status != Type.CustomerStatus.NONMEMBER, "You must regist customer first");
        require(product.status != Type.ProductStatus.NONE, "Product does not exist");
        require(product.status == Type.ProductStatus.ON_SALE, "Product does not on_sale");
        require(purchase.status == Type.PurchaseStatus.REQUEST, "This product has not been requested by the buyer");
        require(creator.tier != Type.CreatorTier.NONE, "Creator does not exist");
        require(msg.sender == product.creator, "You are not the creator of the product");
        require(keccak256(abi.encodePacked(product.hashValue)) == keccak256(abi.encodePacked(purchase.productHash)), "Product changed after request");

        product.sellCount++;
        creator.sellCount++;
        creator.totalSalesAmount = creator.totalSalesAmount.add(product.price);
        
        purchase.encryptedIpfsKey = _encryptedIpfsKey;
        purchase.status           = Type.PurchaseStatus.ACCEPT;
        
        if (buyer.status != Type.CustomerStatus.NONMEMBER) {
            buyer.purchaseCount++;
            buyer.totalPurchaseAmount = buyer.totalPurchaseAmount.add(product.price);
            buyer.purchaseDeposit     = buyer.purchaseDeposit.sub(product.price);
        }

        if (_isUseFeeCoupon) {

            require(couponInfo[msg.sender]["free_coupon"] > 0, "No coupons");

            couponInfo[msg.sender]["free_coupon"]--;
            lockInfo[msg.sender].push(Type.LockInfo(now + lockAfterTime, product.price, _buyer, _productUuid));
        }
        else {

            uint256 fee = product.price.div(tierFeeDiv[uint8(creator.tier) - 1]);
            
            totalFee = totalFee.add(fee);
            ownerLockBalance.push(Type.LockInfo(now + lockAfterTime, fee, _buyer, _productUuid));
            lockInfo[msg.sender].push(Type.LockInfo(now + lockAfterTime, product.price.sub(fee), _buyer, _productUuid));
        }

        emit SellApprove(_buyer, _productUuid, _encryptedIpfsKey);
    }

    function sellReject(address _buyer, string calldata _productUuid) external {

        Type.ProductInfo  storage p = products[_productUuid];
        Type.CreatorInfo  storage c = creators[p.creator];

        require(customers[msg.sender].status != Type.CustomerStatus.NONMEMBER, "You must regist customer first");
        require(p.status != Type.ProductStatus.NONE, "Product does not exist");
        require(purchaseTable[_buyer][_productUuid].status == Type.PurchaseStatus.REQUEST, "This product has not been requested by the buyer");
        require(c.tier != Type.CreatorTier.NONE, "Creator does not exist");
        require(msg.sender == p.creator, "You are not the creator of the product");

        if (customers[msg.sender].status != Type.CustomerStatus.NONMEMBER) {
            customers[_buyer].purchaseDeposit = customers[_buyer].purchaseDeposit.sub(p.price);
        }

        delete purchaseTable[_buyer][_productUuid];

        mm.transfer(_buyer, p.price);
        
        emit SellReject(_buyer, _productUuid);
    }
}