pragma solidity ^0.5.4;

import "./AddressMapper.sol";
import "./IERC20.sol";
import "./Type.sol";

contract Storage {

    mapping(address => Type.CustomerInfo)                    internal customers;
    mapping(address => Type.CreatorInfo)                     internal creators;
    mapping(string  => Type.ProductInfo)                     internal products;
    mapping(address => Type.LockInfo[])                      internal lockInfo;
    
    mapping(address => mapping(string => uint8))             internal couponInfo;
    mapping(address => mapping(string => Type.ReviewInfo))   internal reviews;
    mapping(address => mapping(string => Type.PurchaseInfo)) internal purchaseTable;
    
    Type.LockInfo[] ownerLockBalance;
    
    uint256 public totalFee;
    uint32  public lockAfterTime;
    
    uint16 public tierEFeeDiv;
    uint16 public tierDFeeDiv;
    uint16 public tierCFeeDiv;
    uint16 public tierBFeeDiv;
    uint16 public tierAFeeDiv;
    uint16 public brandFeeDiv;
    
    address public owner;
    IERC20 mm;
    
    AddressMapper public mapper;
}