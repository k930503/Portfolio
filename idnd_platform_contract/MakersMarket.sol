pragma solidity ^0.5.4;

import "./Storage.sol";
import "./SafeMath.sol";

contract MakersMarket is Storage {
    
    using SafeMath for uint256;
    
    constructor(address _mapper, IERC20 _mm, uint8[6] memory _tierFeeDiv) public {
        
        owner  = msg.sender;
        mapper = AddressMapper(_mapper);
        mm     = _mm;
        
        for (uint8 i = 0; i < tierFeeDiv.length; i++) {
            tierFeeDiv[i] = _tierFeeDiv[i];
        }

        lockAfterTime = 604800; // 7 days
    }
 
    modifier onlyOwner() {
        
        require(msg.sender == owner, "Not owner");
        _;
    }
    
    function () payable external {
        
        address contractAddress = mapper.getDelegator();
        
        assembly {
            
            let ptr := mload(0x40)
            calldatacopy(ptr, 0, calldatasize)
            let result := delegatecall(gas, contractAddress, ptr, calldatasize, 0, 0)
            let size := returndatasize
            returndatacopy(ptr, 0, size)
 
            switch result
            case 0 { revert(ptr, size) }
            default { return(ptr, size) }
        }
    }
 
    function setMapper(address _mapper) external {
        
        require(msg.sender == owner, "Not owner");
        
        mapper = AddressMapper(_mapper);
    }
    
    function transferOwnership(address _newOwner) external {
        
        require(msg.sender == owner, "Not owner");
        require(_newOwner != address(0), "invalid address");
        
        owner = _newOwner;
    }
    
    function balanceOfContract() external view returns (uint256) {
        
        return address(this).balance;
    }
    
    function balanceOfOwner() external view returns (uint256) {
        
        uint256 lockBalance = 0;
        
        for(uint256 i = 0; i < ownerLockBalance.length ; i++ ) {
            
            lockBalance = lockBalance.add(ownerLockBalance[i].balance);
        }
        
        return lockBalance;
    }
    
    function getWithdrawableOwnerBalance() external view returns (uint256) {

        uint256 withdrawableBalance = 0;
        
        for (uint256 i = 0; i < ownerLockBalance.length; i++) {
            if (ownerLockBalance[i].releaseTime <= now) {
                withdrawableBalance = withdrawableBalance.add(ownerLockBalance[i].balance);
            }
        }
        
        return withdrawableBalance;
    }
    
    function balanceOf(address _customer) external view returns (uint256) {
        
        uint256 lockedBalance = 0;
        
        for(uint256 i = 0; i < lockInfo[_customer].length ; i++ ) {
            
            lockedBalance = lockedBalance.add(lockInfo[_customer][i].balance);
        }
        
        return customers[_customer].purchaseDeposit.add(lockedBalance);
    }
    
    function withdraw() external {
        
        uint256 balance = 0;
        
        for(uint256 i = 0; i < lockInfo[msg.sender].length; i++) {
            if (lockInfo[msg.sender][i].releaseTime <= now) {
                balance = balance.add(lockInfo[msg.sender][i].balance);
                lockInfo[msg.sender][i].balance = 0;

                if (i != lockInfo[msg.sender].length - 1) {
                    lockInfo[msg.sender][i] = lockInfo[msg.sender][lockInfo[msg.sender].length - 1];
                    i--;
                }
                lockInfo[msg.sender].length--;
            }
        }

        require(balance > 0, "No balance to withdraw");
        
        mm.transfer(msg.sender, balance);
    }
    
    function getWithdrawableBalance(address _customer) external view returns (uint256) {

        uint256 withdrawableBalance = 0;
        
        for (uint256 i = 0; i < lockInfo[_customer].length; i++) {
            if (lockInfo[_customer][i].releaseTime <= now) {
                withdrawableBalance = withdrawableBalance.add(lockInfo[_customer][i].balance);
            }
        }
        
        return withdrawableBalance;
    }
    
    function lockCount(address _customer) external view returns (uint256) {
        
        return lockInfo[_customer].length;
    }
    
    function lockState(address _customer, uint256 _idx) external view returns (uint256, uint256) {
        
        return (lockInfo[_customer][_idx].releaseTime, lockInfo[_customer][_idx].balance);
    }
    
    function getCustomer(address _customer) external view returns (uint32  reviewCount,
                                                                   uint32  purchaseCount,
                                                                   uint256 totalPurchaseAmount,
                                                                   uint256 purchaseDeposit,
                                                                   Type.CustomerStatus status) {
        
        reviewCount         = customers[_customer].reviewCount;
        purchaseCount       = customers[_customer].purchaseCount;
        totalPurchaseAmount = customers[_customer].totalPurchaseAmount;
        purchaseDeposit     = customers[_customer].purchaseDeposit;
        status              = customers[_customer].status;
    }

    function getCreator(address _creator) external view returns (uint32  sellCount,
                                                                 uint256 totalSalesAmount,
                                                                 Type.CreatorTier tier) {
        
        sellCount        = creators[_creator].sellCount;
        totalSalesAmount = creators[_creator].totalSalesAmount;
        tier             = creators[_creator].tier;
    }

    function getProduct(string calldata _productUuid) external view returns (address creator,
                                                                             string memory name,
                                                                             string memory ipfsLink,
                                                                             string memory encryptedIpfsKey,
                                                                             string memory hashValue,
                                                                             uint256 price,
                                                                             uint32  sellCount,
                                                                             uint32  totalReviewRating,
                                                                             uint32  reviewCount,
                                                                             Type.ProductStatus status) {
        
        creator           = products[_productUuid].creator;
        name              = products[_productUuid].name;
        ipfsLink          = products[_productUuid].ipfsLink;
        encryptedIpfsKey  = products[_productUuid].encryptedIpfsKey;
        hashValue         = products[_productUuid].hashValue;
        price             = products[_productUuid].price;
        sellCount         = products[_productUuid].sellCount;
        totalReviewRating = products[_productUuid].totalReviewRating;
        reviewCount       = products[_productUuid].reviewCount;
        status            = products[_productUuid].status;
        
    }

    function getReview(address _buyer, string calldata _productUuid) external view returns (uint8 rating, Type.ReviewStatus status) {
        
        rating = reviews[_buyer][_productUuid].rating;
        status = reviews[_buyer][_productUuid].status;
    }

    function getPurchase(address _buyer, string calldata _productUuid) external view returns (address creator,
                                                                                              string memory ipfsLink,
                                                                                              string memory encryptedIpfsKey,
                                                                                              string memory productHash,
                                                                                              Type.PurchaseStatus status) {
        
        creator          = purchaseTable[_buyer][_productUuid].creator;
        ipfsLink         = purchaseTable[_buyer][_productUuid].ipfsLink;
        encryptedIpfsKey = purchaseTable[_buyer][_productUuid].encryptedIpfsKey;
        productHash      = purchaseTable[_buyer][_productUuid].productHash;
        status           = purchaseTable[_buyer][_productUuid].status;
    }

    function getCouponCount(address _target, string calldata _couponName) external view returns (uint8) {
        
        return couponInfo[_target][_couponName];
    }
}