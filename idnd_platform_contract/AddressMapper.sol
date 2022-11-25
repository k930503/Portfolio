pragma solidity ^0.5.4;

contract AddressMapper {
    
    address delegator;
    mapping(string => address) internal logic;
    
    address public owner;
    
    constructor() public {
        owner = msg.sender;
    }
    
    modifier onlyOwner() {
        require(msg.sender == owner, "Not owner");
        _;
    }
    
    function transferOwnership(address _newOwner) external onlyOwner {
        
        require(_newOwner != address(0), "invalid address");
        
        owner = _newOwner;
    }
    
    function setDelegator(address _delegator) external onlyOwner {
        delegator = _delegator;
    }
 
    function getDelegator() external view returns (address) {
        return delegator;
    }
    
    function addLogicContract(string calldata _name, address _logicContract) external onlyOwner {
        logic[_name] = _logicContract;
    }
    
    function removeLogicContract(string calldata _name) external onlyOwner {
        delete logic[_name];
    }
    
    function getLogicContract(string calldata _name) external view returns (address) {
        return logic[_name];
    }
}