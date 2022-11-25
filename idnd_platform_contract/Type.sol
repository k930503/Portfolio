pragma solidity ^0.5.4;

library Type {
    
    enum CustomerStatus {
        NONMEMBER,
        ACTIVE,
        PAUSE
    }

    enum PurchaseStatus {
        NONE,
        ACCEPT,
        REQUEST,
        REJECT,
        ROLLBACK
    }

    enum ProductStatus {
        NONE,
        ON_SALE,
        REQUEST_SALE,
        REQUEST_UPDATE,
        REJECT,
        PAUSE
    }

    enum ReviewStatus {
        NONE,
        ON,
        OFF
    }

    enum CreatorTier {
        NONE,
        E,
        D,
        C,
        B,
        A,
        BRAND
    }

    struct CustomerInfo {
        uint32         reviewCount;
        uint32         purchaseCount;
        uint256        totalPurchaseAmount;
        uint256        purchaseDeposit;
        CustomerStatus status;
    }

    struct CreatorInfo {
        uint32      sellCount;
        uint256     totalSalesAmount;
        CreatorTier tier;
    }
    
    struct ProductInfo { 
        address       creator;
        string        name;
        string        ipfsLink;
        string        encryptedIpfsKey;
        string        hashValue;
        uint256       price;
        uint32        sellCount;
        uint32        totalReviewRating;
        uint32        reviewCount;
        ProductStatus status;
    }
    
    struct PurchaseInfo {
        address        creator;
        string         ipfsLink;
        string         encryptedIpfsKey;
        string         productHash;
        uint256        price;
        PurchaseStatus status;
    }

    struct ReviewInfo {
        uint8       rating;
        ReviewStatus status;
    }
    
    struct LockInfo {
        uint256 releaseTime;
        uint256 balance;
        address buyer;
        string  productUuid;
    }
}