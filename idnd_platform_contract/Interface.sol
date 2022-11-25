pragma solidity ^0.5.4;

import "./Type.sol";
import "./Storage.sol";

contract Interface {
    
    //Manage
    function withdrawOwnerBalance() external;

    function setLockAfterTime(uint32 _lockAfterTime) external;
    
    function setTradeFee(uint16[6] calldata _tierFeeDiv) external;
                         
    function setCreatorTier(address _creator, Type.CreatorTier _tier) external;
    
    function rewardCoupon(address _to, string calldata _couponName, uint8 _count) external;
    
    function transactionRollback(address _buyer, string calldata _productUuid) external;
    
    //User
    function setCustomer(address _address) external;

    function setCreator(address _customer) external;
    
    function setCreaters(address[] calldata _customers) external;

    function removeCreator(address _creator) external;

    function removeCustomer(address _customer) external;

    //Product
    function addProduct(string  calldata _productUuid,
                        string  calldata _name,
                        string  calldata _ipfsLink,
                        string  calldata _encryptedIpfsKey,
                        uint256 _price) external;

    function editProduct(string calldata _productUuid,
                         string calldata _name,
                         uint256         _price) external;

    function editProductStatusPause(string calldata _productUuid) external;

    function editProductStatusByOwner(string calldata _productUuid, string calldata _hashValue, Type.ProductStatus _status) external;

    function removeProduct(string calldata _productUuid) external;

    //Trade
    function purchaseProduct(string calldata _productUuid) external;

    function purchaseCancel(string calldata _productUuid) external;

    function sellApprove(address _buyer,
                         string calldata _productUuid,
                         string calldata _encryptedIpfsKey,
                         bool _isUseFeeCoupon) external;
    
    function sellReject(address _buyer, string calldata _productUuid) external;

    //Review
    function postReview(string calldata _productUuid,
                        uint8  _rating) external;

    function removeReview(string calldata _productUuid) external;

    function editReview(string calldata _productUuid, uint8 _rating) external;

    //MakersMarket
    function setMapper(address _mapper) external;
    
    function transferOwnership(address _newOwner) external;
    
    function balanceOfContract() external view returns (uint256);
    
    function balanceOfOwner() external view returns (uint256);
    
    function getWithdrawableOwnerBalance() external view returns (uint256);
    
    function balanceOf(address _customer) external view returns (uint256);
    
    function withdraw() external;
    
    function getWithdrawableBalance(address _customer) external view returns (uint256);
    
    function lockCount(address _customer) external view returns (uint256);
    
    function lockState(address _customer, uint256 _idx) external view returns (uint256, uint256);
    
    function getCustomer(address _customer) external view returns (uint32  reviewCount,
                                                                   uint32  purchaseCount,
                                                                   uint256 totalPurchaseAmount,
                                                                   uint256 purchaseDeposit,
                                                                   Type.CustomerStatus status);

    function getCreator(address _creator) external view returns (uint32      sellCount,
                                                                 uint256     totalSalesAmount,
                                                                 Type.CreatorTier tier);

    function getProduct(string calldata _productUuid) external view returns (address creator,
                                                                             string memory name,
                                                                             string memory ipfsLink,
                                                                             string memory encryptedIpfsKey,
                                                                             string memory hashValue,
                                                                             uint256 price,
                                                                             uint32  sellCount,
                                                                             uint32  totalReviewRating,
                                                                             uint32  reviewCount,
                                                                             Type.ProductStatus status);

    function getReview(address _buyer, string calldata _productUuid) external view returns (uint8 rating, Type.ReviewStatus status);

    function getPurchase(address _buyer, string calldata _productUuid) external view returns (address creator,
                                                                                              string memory ipfsLink,
                                                                                              string memory encryptedIpfsKey,
                                                                                              string memory productHash,
                                                                                              Type.PurchaseStatus status);
}