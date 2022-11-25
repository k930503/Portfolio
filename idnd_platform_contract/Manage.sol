pragma solidity ^0.5.4;

import "./Storage.sol";
import "./SafeMath.sol";

contract Manage is Storage {
    
    using SafeMath for uint256;
    
    function withdrawOwnerBalance() external {
        
        require(msg.sender == owner, "Not owner");
        
        uint256 balance = 0;
        
        for(uint256 i = 0; i < ownerLockBalance.length; i++) {
            if (ownerLockBalance[i].releaseTime <= now) {
                balance = balance.add(ownerLockBalance[i].balance);
                ownerLockBalance[i].balance = 0;

                if (i != ownerLockBalance.length - 1) {
                    ownerLockBalance[i] = ownerLockBalance[ownerLockBalance.length - 1];
                    i--;
                }
                ownerLockBalance.length--;
            }
        }

        require(balance > 0, "No balance to withdraw");
        
        mm.transfer(owner, balance);
    }
    
    function setLockAfterTime(uint32 _lockAfterTime) external {
        
        require(msg.sender == owner, "Not owner");
        
        lockAfterTime = _lockAfterTime;
    }
    
    function setTradeFee(uint16 _tierEFeeDiv,
                         uint16 _tierDFeeDiv,
                         uint16 _tierCFeeDiv,
                         uint16 _tierBFeeDiv,
                         uint16 _tierAFeeDiv,
                         uint16 _brandFeeDiv) external {
        
        require(msg.sender == owner, "Not owner");
        
        tierEFeeDiv = _tierEFeeDiv;
        tierDFeeDiv = _tierDFeeDiv;
        tierCFeeDiv = _tierCFeeDiv;
        tierBFeeDiv = _tierBFeeDiv;
        tierAFeeDiv = _tierAFeeDiv;
        brandFeeDiv = _brandFeeDiv;
    }
    
    function setCreatorTier(address _creator, Type.CreatorTier _tier) external {
        
        require(msg.sender == owner, "Not owner");
        
        creators[_creator].tier = _tier;
    }

    function rewardCoupon(address _to, string calldata _couponName, uint8 _count) external {
        
        require(msg.sender == owner, "Not owner");

        couponInfo[_to][_couponName] += _count;
    }
    
    function transactionRollback(address _buyer, string calldata _productUuid) external {
        
        require(msg.sender == owner, "Not owner");
        
        Type.PurchaseInfo storage pur     = purchaseTable[_buyer][_productUuid];
        Type.CustomerInfo storage buyer   = customers[_buyer];
        Type.CreatorInfo  storage creator = creators[pur.creator];
        Type.ReviewInfo   storage r       = reviews[_buyer][_productUuid];
        Type.ProductInfo  storage p       = products[_productUuid];
        Type.LockInfo[]   storage li      = lockInfo[pur.creator];
        
        require(pur.status == Type.PurchaseStatus.ACCEPT, "This purchase is not complete.");
        
        uint256 amount = 0;
        
        if (buyer.status != Type.CustomerStatus.NONMEMBER) {
            buyer.reviewCount--;
            buyer.purchaseCount--;
            buyer.totalPurchaseAmount = buyer.totalPurchaseAmount.sub(pur.price);
        }
        
        if (creator.tier != Type.CreatorTier.NONE) {
            creator.sellCount--;
            creator.totalSalesAmount = creator.totalSalesAmount.sub(pur.price);
        }
        
        if (r.status != Type.ReviewStatus.NONE) {
            delete reviews[msg.sender][_productUuid];
        }

        if (p.status != Type.ProductStatus.NONE) {
            p.totalReviewRating -= r.rating;
            p.reviewCount--;
            p.sellCount--;
        }
        
        for (uint256 i = 0; i < li.length; i++) {
            
            if (li[i].buyer == _buyer &&
                keccak256(abi.encodePacked(li[i].productUuid)) == keccak256(abi.encodePacked(_productUuid)) &&
                li[i].releaseTime > now) {
                
                amount = li[i].balance;
                li[i].balance = 0;

                if (i != li.length - 1) {
                    li[i] = li[li.length - 1];
                }
                
                li.length--;
                
                break;
            }
        }

        require(amount > 0, "Rollback is not possible");

        for (uint256 i = 0; i < ownerLockBalance.length; i++) {
            
            if (ownerLockBalance[i].buyer == _buyer &&
                keccak256(abi.encodePacked(ownerLockBalance[i].productUuid)) == keccak256(abi.encodePacked(_productUuid)) &&
                ownerLockBalance[i].releaseTime > now) {
                
                amount = amount.add(ownerLockBalance[i].balance);
                ownerLockBalance[i].balance = 0;

                if (i != ownerLockBalance.length - 1) {
                    ownerLockBalance[i] = ownerLockBalance[ownerLockBalance.length - 1];
                }
                
                ownerLockBalance.length--;
                
                break;
            }
        }
        
        pur.status = Type.PurchaseStatus.ROLLBACK;
        mm.transfer(_buyer, amount);
    }
}