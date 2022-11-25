pragma solidity ^0.5.4;

import "./Storage.sol";

contract Delegator is Storage {
    
    constructor(AddressMapper _mapper) public {
        mapper  = _mapper;
    }
    
    modifier onlyOwner() {
        require(msg.sender == owner, "Not owner");
        _;
    }
    
    //Manage
    function withdrawOwnerBalance() external {
        
        address logic = mapper.getLogicContract("Manage");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("withdrawOwnerBalance()"));
 
        require(success);
    }
    
    function setLockAfterTime(uint32 _lockAfterTime) external {
        
        address logic = mapper.getLogicContract("Manage");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("setLockAfterTime(uint32)", _lockAfterTime));
 
        require(success);
    }
    
    function setTradeFee(uint16[6] calldata _tierFeeDiv) external {
        
        address logic = mapper.getLogicContract("Manage");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("setTradeFee(uint16[6])", _tierFeeDiv));
 
        require(success);
    }
    
    function rewardCoupon(address _to, string calldata _couponName, uint8 _count) external {
        
        address logic = mapper.getLogicContract("Manage");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("rewardCoupon(address,string,uint8)", 
                                                                       _to, _couponName, _count));
 
        require(success);
    }
    
    function transactionRollback(address _buyer, string calldata _productUuid) external {
        
        address logic = mapper.getLogicContract("Manage");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("transactionRollback(address,string)",
                                                                       _buyer, _productUuid));
 
        require(success);
    }
    
    function setCreatorTier(address _creator, Type.CreatorTier _tier) external {
        
        require(msg.sender == owner, "Not owner");
        
        address logic = mapper.getLogicContract("Manage");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("setCreatorTier(address,uint8)",
                                                                       _creator, _tier));
    }
    
    //User
    function setCustomer(address _address) external {
        
        address logic = mapper.getLogicContract("User");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("setCustomer(address)", _address));
 
        require(success);
    }

    function setCreator(address _customer) external {
        
        address logic = mapper.getLogicContract("User");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("setCreator(address)", _customer));
 
        require(success);
    }
    
    function setCreators(address[] calldata _customers) external {
        
        address logic = mapper.getLogicContract("User");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("setCreators(address[])", _customers));
 
        require(success);
    }

    function removeCreator(address _creator) external {
        
        address logic = mapper.getLogicContract("User");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("removeCreator(address)", _creator));
 
        require(success);
    }

    function removeCustomer(address _customer) external {
        
        address logic = mapper.getLogicContract("User");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("removeCustomer(address)", _customer));
 
        require(success);
    }

    //Product
    function addProduct(string  calldata _productUuid,
                        string  calldata _name,
                        string  calldata _ipfsLink,
                        string  calldata _encryptedIpfsKey,
                        uint256 _price) external {
        
        address logic = mapper.getLogicContract("Product");                    
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature(
                                                                        "addProduct(string,string,string,string,uint256)",
                                                                        _productUuid, _name, _ipfsLink, _encryptedIpfsKey, _price));
 
        require(success);
    }

    function editProduct(string calldata _productUuid,
                         string calldata _name,
                         uint256         _price) external {
        
        address logic = mapper.getLogicContract("Product");                     
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature(
                                                                        "editProduct(string,string,uint256)",
                                                                        _productUuid, _name, _price));
 
        require(success);
    }

    function editProductStatusPause(string calldata _productUuid) external {
        
        address logic = mapper.getLogicContract("Product");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("editProductStatusPause(string)", _productUuid));
 
        require(success);
    }

    function editProductStatusByOwner(string calldata _productUuid, string calldata _hashValue, Type.ProductStatus _status) external {
        
        address logic = mapper.getLogicContract("Product");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature(
                                                                        "editProductStatusByOwner(string,string,uint8)",
                                                                        _productUuid, _hashValue, _status));
 
        require(success);
    }

    function removeProduct(string calldata _productUuid) external {
        
        address logic = mapper.getLogicContract("Product");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("removeProduct(string)", _productUuid));
 
        require(success);
    }

    //Trade
    function purchaseProduct(string calldata _productUuid) external {
        
        address logic = mapper.getLogicContract("Trade");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("purchaseProduct(string)", _productUuid));
 
        require(success);
    }

    function purchaseCancel(string calldata _productUuid) external {
        
        address logic = mapper.getLogicContract("Trade");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("purchaseCancel(string)", _productUuid));
 
        require(success);
    }

    function sellApprove(address _buyer,
                         string calldata _productUuid,
                         string calldata _encryptedIpfsKey,
                         bool _isUseFeeCoupon) external {
        
        address logic = mapper.getLogicContract("Trade");                     
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature(
                                                                        "sellApprove(address,string,string,bool)",
                                                                        _buyer, _productUuid, _encryptedIpfsKey, _isUseFeeCoupon));
 
        require(success);
    }
    
    function sellReject(address _buyer, string calldata _productUuid) external {

        address logic = mapper.getLogicContract("Trade");                     
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature(
                                                                        "sellReject(address,string)",
                                                                        _buyer, _productUuid));
 
        require(success);
    }

    //Review
    function postReview(string calldata _productUuid,
                        uint8  _rating) external {
        
        address logic = mapper.getLogicContract("Review");                    
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature(
                                                                        "postReview(string,uint8)",
                                                                        _productUuid, _rating));
 
        require(success);
    }

    function removeReview(string calldata _productUuid) external {
        
        address logic = mapper.getLogicContract("Review");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature("removeReview(string)", _productUuid));
 
        require(success);
    }

    function editReview(string calldata _productUuid,
                        uint8 _rating) external {
        
        address logic = mapper.getLogicContract("Review");
        (bool success, bytes memory returnedData) = logic.delegatecall(abi.encodeWithSignature(
                                                                        "editReview(string,uint8)",
                                                                        _productUuid, _rating));
 
        require(success);
    }
}