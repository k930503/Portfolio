pragma solidity ^0.5.4;

import "./Storage.sol";

contract User is Storage {
    
    function setCustomer(address _address) external {
        
        require(msg.sender == owner, "Not owner");
        require(customers[_address].status == Type.CustomerStatus.NONMEMBER, "Customer already exist");
        
        customers[_address] = Type.CustomerInfo(0, 0, 0, 0, Type.CustomerStatus.ACTIVE);
    }
    
    function setCreator(address _customer) external {
        
        require(msg.sender == owner, "Not owner");
        require(customers[_customer].status != Type.CustomerStatus.NONMEMBER, "You must regist customer first");
        require(creators[_customer].tier == Type.CreatorTier.NONE, "Creator already exist");

        creators[_customer] = Type.CreatorInfo(0, 0, Type.CreatorTier.E);
    }
    
    function removeCreator(address _creator) external {
        
        require(msg.sender == owner, "Not owner");
        require(creators[_creator].tier != Type.CreatorTier.NONE, "Creator does not exist");

        delete creators[_creator];
    }

    function removeCustomer(address _customer) external {

        require(msg.sender == owner, "Not owner");
        require(customers[_customer].status != Type.CustomerStatus.NONMEMBER, "Customer does not exist");

        delete customers[_customer];
    }
}