pragma solidity ^0.5.4;

import "./Storage.sol";

contract Product is Storage {

    event EditProduct(string productUuid, string name, uint256 price);
    event EditProductStatusPause(string productUuid);
    event EditProductStatusByOwner(string productUuid, string hashValue, Type.ProductStatus status);

    function addProduct(string  calldata _productUuid,
                        string  calldata _name,
                        string  calldata _ipfsLink,
                        string  calldata _encryptedIpfsKey,
                        uint256 _price) external {

        require(customers[msg.sender].status != Type.CustomerStatus.NONMEMBER, "You must regist customer first");
        require(creators[msg.sender].tier != Type.CreatorTier.NONE, "You must regist creator first");
        require(products[_productUuid].status == Type.ProductStatus.NONE, "Product already exist");
        require(bytes(_name).length < 60, "name should be less than 48 characters long");
        require(_price > 0, "Price is must upper 0 MM");

        products[_productUuid] = Type.ProductInfo(msg.sender, _name, _ipfsLink, _encryptedIpfsKey, "", _price, 0, 0, 0, Type.ProductStatus.REQUEST_SALE);
    }

    function editProduct(string calldata _productUuid,
                         string calldata _name,
                         uint256         _price) external {

        Type.ProductInfo storage p = products[_productUuid];
        require(p.status  != Type.ProductStatus.NONE, "Product does not exist");
        require(msg.sender == p.creator, "You are not the creator of this product");
        require(bytes(_name).length < 60, "name should be less than 48 characters long");
        require(_price > 0, "Price is must upper 0 MM");

        p.name      = _name;
        p.price     = _price;
        p.hashValue = "";
        p.status    = Type.ProductStatus.REQUEST_UPDATE;

        emit EditProduct(_productUuid, _name, _price);
    }

    function editProductStatusPause(string calldata _productUuid) external {

        Type.ProductInfo storage p = products[_productUuid];
        require(p.status  != Type.ProductStatus.NONE, "Product does not exist");
        require(msg.sender == p.creator, "You are not the creator of this product");

        p.status = Type.ProductStatus.PAUSE;

        emit EditProductStatusPause(_productUuid);
    }

    function editProductStatusByOwner(string calldata _productUuid, string calldata _hashValue, Type.ProductStatus _status) external {

        Type.ProductInfo storage p = products[_productUuid];

        require(msg.sender == owner, "Not owner");
        require(p.status  != Type.ProductStatus.NONE, "Product does not exist");

        p.hashValue = _hashValue;
        p.status    = _status;

        emit EditProductStatusByOwner(_productUuid, _hashValue, _status);
    }

    function removeProduct(string calldata _productUuid) external {

        require(products[_productUuid].status != Type.ProductStatus.NONE, "Product does not exist");
        require(msg.sender == products[_productUuid].creator, "Only product registrants can remove");

        delete products[_productUuid];
    }
}
