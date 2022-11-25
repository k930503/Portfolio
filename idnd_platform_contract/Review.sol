pragma solidity ^0.5.4;

import "./Storage.sol";

contract Review is Storage {
    
    function postReview(string calldata _productUuid,
                        uint8  _rating) external {

        Type.CustomerInfo storage c = customers[msg.sender];
        require(c.status != Type.CustomerStatus.NONMEMBER, "You must regist customer first");
        require(_rating <= 10, "Rating must under 10");
        Type.ProductInfo storage p = products[_productUuid];
        require(p.status != Type.ProductStatus.NONE, "Product does not exist");
        require(purchaseTable[msg.sender][_productUuid].status == Type.PurchaseStatus.ACCEPT, "This product has not been purchased");
        require(reviews[msg.sender][_productUuid].status == Type.ReviewStatus.NONE, "Review already exist");

        reviews[msg.sender][_productUuid] = Type.ReviewInfo(_rating, Type.ReviewStatus.ON);
        p.totalReviewRating += _rating;
        p.reviewCount++;
        c.reviewCount++;
    }

    function removeReview(string calldata _productUuid) external {
        
        Type.CustomerInfo storage c = customers[msg.sender];
        Type.ReviewInfo storage r = reviews[msg.sender][_productUuid];

        require(c.status != Type.CustomerStatus.NONMEMBER, "You must regist customer first");
        require(r.status != Type.ReviewStatus.NONE, "Review does not exist");

        Type.ProductInfo storage p = products[_productUuid];

        p.totalReviewRating -= r.rating;
        p.reviewCount--;
        c.reviewCount--;

        delete reviews[msg.sender][_productUuid];
    }
}