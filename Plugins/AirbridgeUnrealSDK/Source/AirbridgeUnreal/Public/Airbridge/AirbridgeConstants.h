// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AirbridgeConstants.generated.h"

namespace AirbridgeConstants
{
	namespace CATEGORY
	{
		static const FString SIGN_UP	(TEXT("airbridge.user.signup"));
		static const FString SIGN_IN	(TEXT("airbridge.user.signin"));
		static const FString SIGN_OUT	(TEXT("airbridge.user.signout"));

		[[deprecated("The constant VIEW_HOME will be deprecated. Consider using HOME_VIEWED instead.")]]
		static const FString VIEW_HOME				(TEXT("airbridge.ecommerce.home.viewed"));
		static const FString HOME_VIEWED			(TEXT("airbridge.ecommerce.home.viewed"));

		[[deprecated("The constant VIEW_SEARCH_RESULT will be deprecated. Consider using SEARCH_RESULTS_VIEWED instead.")]]
		static const FString VIEW_SEARCH_RESULT		(TEXT("airbridge.ecommerce.searchResults.viewed"));
		static const FString SEARCH_RESULTS_VIEWED	(TEXT("airbridge.ecommerce.searchResults.viewed"));

		[[deprecated("The constant VIEW_PRODUCT_LIST will be deprecated. Consider using PRODUCT_LIST_VIEWED instead.")]]
		static const FString VIEW_PRODUCT_LIST		(TEXT("airbridge.ecommerce.productList.viewed"));
		static const FString PRODUCT_LIST_VIEWED	(TEXT("airbridge.ecommerce.productList.viewed"));

		[[deprecated("The constant VIEW_PRODUCT_DETAILS will be deprecated. Consider using PRODUCT_VIEWED instead.")]]
		static const FString VIEW_PRODUCT_DETAILS	(TEXT("airbridge.ecommerce.product.viewed"));
		static const FString PRODUCT_VIEWED			(TEXT("airbridge.ecommerce.product.viewed"));

		[[deprecated("The constant ADD_TO_CART will be deprecated. Consider using ADDED_TO_CART instead.")]]
		static const FString ADD_TO_CART			(TEXT("airbridge.ecommerce.product.addedToCart"));
		static const FString ADDED_TO_CART			(TEXT("airbridge.ecommerce.product.addedToCart"));

		[[deprecated("The constant ORDER_COMPLETE will be deprecated. Consider using ORDER_COMPLETED instead.")]]
		static const FString ORDER_COMPLETE			(TEXT("airbridge.ecommerce.order.completed"));
		static const FString ORDER_COMPLETED		(TEXT("airbridge.ecommerce.order.completed"));

		static const FString ADD_PAYMENT_INFO		(TEXT("airbridge.addPaymentInfo"));
		static const FString ADD_TO_WISHLIST		(TEXT("airbridge.addToWishlist"));
		static const FString INITIATE_CHECKOUT		(TEXT("airbridge.initiateCheckout"));
		static const FString ORDER_CANCELED			(TEXT("airbridge.ecommerce.order.canceled"));
		static const FString START_TRIAL			(TEXT("airbridge.startTrial"));
		static const FString SUBSCRIBE				(TEXT("airbridge.subscribe"));
		static const FString UNSUBSCRIBE			(TEXT("airbridge.unsubscribe"));
		static const FString AD_IMPRESSION			(TEXT("airbridge.adImpression"));
		static const FString AD_CLICK				(TEXT("airbridge.adClick"));
		static const FString COMPLETE_TUTORIAL		(TEXT("airbridge.completeTutorial"));
		static const FString ACHIEVE_LEVEL			(TEXT("airbridge.achieveLevel"));
		static const FString UNLOCK_ACHIEVEMENT		(TEXT("airbridge.unlockAchievement"));
		static const FString RATE					(TEXT("airbridge.rate"));
		static const FString SHARE					(TEXT("airbridge.share"));
		static const FString SCHEDULE				(TEXT("airbridge.schedule"));
		static const FString SPEND_CREDITS			(TEXT("airbridge.spendCredits"));
	}

	namespace ATTRIBUTES
	{
		static const FString QUERY				(TEXT("query"));
		static const FString PRODUCT_LIST_ID	(TEXT("productListID"));
		static const FString CART_ID			(TEXT("cartID"));
		static const FString TRANSACTION_ID		(TEXT("transactionID"));
		static const FString IN_APP_PURCHASED	(TEXT("inAppPurchased"));
		static const FString PRODUCTS			(TEXT("products"));
		static const FString CURRENCY			(TEXT("currency"));
		static const FString TOTAL_VALUE		(TEXT("totalValue"));
		static const FString TOTAL_QUANTITY		(TEXT("totalQuantity"));

		static const FString ORIGINAL_CURRENCY					(TEXT("originalCurrency"));
		static const FString PERIOD								(TEXT("period"));
		static const FString IS_RENEWAL							(TEXT("isRenewal"));
		static const FString RENEWAL_COUNT						(TEXT("renewalCount"));
		static const FString TRANSACTION_TYPE					(TEXT("transactionType"));
		static const FString TRANSACTION_PAIRED_EVENT_CATEGORY	(TEXT("transactionPairedEventCategory"));
		static const FString TRANSACTION_PAIRED_EVENT_TIMESTAMP	(TEXT("transactionPairedEventTimestamp"));
		static const FString CONTRIBUTION_MARGIN				(TEXT("contributionMargin"));
		static const FString ORIGINAL_CONTRIBUTION_MARGIN		(TEXT("originalContributionMargin"));
		static const FString LIST_ID							(TEXT("listID"));
		static const FString RATE_ID							(TEXT("rateID"));
		static const FString RATE								(TEXT("rate"));
		static const FString MAX_RATE							(TEXT("maxRate"));
		static const FString ACHIEVEMENT_ID						(TEXT("achievementID"));
		static const FString SHARED_CHANNEL						(TEXT("sharedChannel"));
		static const FString DATE_TIME							(TEXT("datetime"));
		static const FString DESCRIPTION						(TEXT("description"));
		static const FString IS_REVENUE							(TEXT("isRevenue"));
		static const FString PLACE								(TEXT("place"));
		static const FString SCHEDULE_ID						(TEXT("scheduleID"));
		static const FString TYPE								(TEXT("type"));
		static const FString LEVEL								(TEXT("level"));
		static const FString SCORE								(TEXT("score"));
	}

	namespace PRODUCT
	{
		static const FString ID			(TEXT("productID"));
		static const FString NAME		(TEXT("name"));
		static const FString CURRENCY	(TEXT("currency"));
		static const FString PRICE		(TEXT("price"));
		static const FString QUANTITY	(TEXT("quantity"));
		static const FString POSITION	(TEXT("position"));

		static const FString CATEGORY_ID	(TEXT("categoryID"));
		static const FString CATEGORY_NAME	(TEXT("categoryName"));
		static const FString BRAND_ID		(TEXT("brandID"));
		static const FString BRAND_NAME		(TEXT("brandName"));
	}
}

UCLASS()
class AIRBRIDGEUNREAL_API UAirbridgeConstants : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

#pragma region CATEGORY
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::SIGN_UP")
	static UPARAM(DisplayName = "Category") FString GetCategorySignUp()
	{
		return AirbridgeConstants::CATEGORY::SIGN_UP;
	}
 
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::SIGN_IN")
	static UPARAM(DisplayName = "Category") FString GetCategorySignIn()
	{       
		return AirbridgeConstants::CATEGORY::SIGN_IN;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::SIGN_OUT")
	static UPARAM(DisplayName = "Category") FString GetCategorySignOut()
	{       
		return AirbridgeConstants::CATEGORY::SIGN_OUT;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::VIEW_HOME",
		meta=(DeprecatedFunction,
			DeprecationMessage="The constant CATEGORY::VIEW_HOME will be deprecated. Consider using CATEGORY::HOME_VIEWED instead."))
	static UPARAM(DisplayName = "Category") FString GetCategoryViewHome()
	{       
		return AirbridgeConstants::CATEGORY::VIEW_HOME;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::HOME_VIEWED")
	static UPARAM(DisplayName = "Category") FString GetCategoryHomeViewed()
	{       
		return AirbridgeConstants::CATEGORY::HOME_VIEWED;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::VIEW_SEARCH_RESULT",
		meta=(DeprecatedFunction,
			DeprecationMessage="The constant CATEGORY::VIEW_SEARCH_RESULT will be deprecated. Consider using CATEGORY::SEARCH_RESULTS_VIEWED instead."))
	static UPARAM(DisplayName = "Category") FString GetCategoryViewSearchResult()
	{       
		return AirbridgeConstants::CATEGORY::VIEW_SEARCH_RESULT;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::SEARCH_RESULTS_VIEWED")
	static UPARAM(DisplayName = "Category") FString GetCategorySearchResultsViewed()
	{       
		return AirbridgeConstants::CATEGORY::SEARCH_RESULTS_VIEWED;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::VIEW_PRODUCT_LIST",
		meta=(DeprecatedFunction,
			DeprecationMessage="The constant CATEGORY::VIEW_PRODUCT_LIST will be deprecated. Consider using CATEGORY::PRODUCT_LIST_VIEWED instead."))
	static UPARAM(DisplayName = "Category") FString GetCategoryViewProductList()
	{       
		return AirbridgeConstants::CATEGORY::VIEW_PRODUCT_LIST;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::PRODUCT_LIST_VIEWED")
	static UPARAM(DisplayName = "Category") FString GetCategoryProductListViewed()
	{       
		return AirbridgeConstants::CATEGORY::PRODUCT_LIST_VIEWED;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::VIEW_PRODUCT_DETAILS",
		meta=(DeprecatedFunction,
			DeprecationMessage="The constant CATEGORY::VIEW_PRODUCT_DETAILS will be deprecated. Consider using CATEGORY::PRODUCT_VIEWED instead."))
	static UPARAM(DisplayName = "Category") FString GetCategoryViewProductDetails()
	{       
		return AirbridgeConstants::CATEGORY::VIEW_PRODUCT_DETAILS;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::PRODUCT_VIEWED")
	static UPARAM(DisplayName = "Category") FString GetCategoryProductViewed()
	{       
		return AirbridgeConstants::CATEGORY::PRODUCT_VIEWED;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::ADD_TO_CART",
		meta=(DeprecatedFunction,
			DeprecationMessage="The constant CATEGORY::ADD_TO_CART will be deprecated. Consider using CATEGORY::ADDED_TO_CART instead."))
	static UPARAM(DisplayName = "Category") FString GetCategoryAddToCart()
	{       
		return AirbridgeConstants::CATEGORY::ADD_TO_CART;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::ADDED_TO_CART")
	static UPARAM(DisplayName = "Category") FString GetCategoryAddedToCart()
	{       
		return AirbridgeConstants::CATEGORY::ADDED_TO_CART;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::ORDER_COMPLETE",
		meta=(DeprecatedFunction,
			DeprecationMessage="The constant CATEGORY::ORDER_COMPLETE will be deprecated. Consider using CATEGORY::ORDER_COMPLETED instead."))
	static UPARAM(DisplayName = "Category") FString GetCategoryOrderComplete()
	{       
		return AirbridgeConstants::CATEGORY::ORDER_COMPLETE;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::ORDER_COMPLETED")
	static UPARAM(DisplayName = "Category") FString GetCategoryOrderCompleted()
	{       
		return AirbridgeConstants::CATEGORY::ORDER_COMPLETED;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::ADD_PAYMENT_INFO")
	static UPARAM(DisplayName = "Category") FString GetCategoryAddPaymentInfo()
	{       
		return AirbridgeConstants::CATEGORY::ADD_PAYMENT_INFO;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::ADD_TO_WISHLIST")
	static UPARAM(DisplayName = "Category") FString GetCategoryAddToWishlist()
	{       
		return AirbridgeConstants::CATEGORY::ADD_TO_WISHLIST;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::INITIATE_CHECKOUT")
	static UPARAM(DisplayName = "Category") FString GetCategoryInitiateCheckout()
	{       
		return AirbridgeConstants::CATEGORY::INITIATE_CHECKOUT;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::ORDER_CANCELED")
	static UPARAM(DisplayName = "Category") FString GetCategoryOrderCanceled()
	{       
		return AirbridgeConstants::CATEGORY::ORDER_CANCELED;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::START_TRIAL")
	static UPARAM(DisplayName = "Category") FString GetCategoryStartTrial()
	{       
		return AirbridgeConstants::CATEGORY::START_TRIAL;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::SUBSCRIBE")
	static UPARAM(DisplayName = "Category") FString GetCategorySubscribe()
	{       
		return AirbridgeConstants::CATEGORY::SUBSCRIBE;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::UNSUBSCRIBE")
	static UPARAM(DisplayName = "Category") FString GetCategoryUnsubscribe()
	{       
		return AirbridgeConstants::CATEGORY::UNSUBSCRIBE;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::AD_IMPRESSION")
	static UPARAM(DisplayName = "Category") FString GetCategoryAdImpression()
	{       
		return AirbridgeConstants::CATEGORY::AD_IMPRESSION;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::AD_CLICK")
	static UPARAM(DisplayName = "Category") FString GetCategoryAdClick()
	{       
		return AirbridgeConstants::CATEGORY::AD_CLICK;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::COMPLETE_TUTORIAL")
	static UPARAM(DisplayName = "Category") FString GetCategoryCompleteTutorial()
	{       
		return AirbridgeConstants::CATEGORY::COMPLETE_TUTORIAL;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::ACHIEVE_LEVEL")
	static UPARAM(DisplayName = "Category") FString GetCategoryAchieveLevel()
	{       
		return AirbridgeConstants::CATEGORY::ACHIEVE_LEVEL;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::UNLOCK_ACHIEVEMENT")
	static UPARAM(DisplayName = "Category") FString GetCategoryUnlockAchievement()
	{       
		return AirbridgeConstants::CATEGORY::UNLOCK_ACHIEVEMENT;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::RATE")
	static UPARAM(DisplayName = "Category") FString GetCategoryRate()
	{       
		return AirbridgeConstants::CATEGORY::RATE;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::SHARE")
	static UPARAM(DisplayName = "Category") FString GetCategoryShare()
	{       
		return AirbridgeConstants::CATEGORY::SHARE;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::SCHEDULE")
	static UPARAM(DisplayName = "Category") FString GetCategorySchedule()
	{       
		return AirbridgeConstants::CATEGORY::SCHEDULE;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Category", DisplayName = "CATEGORY::SPEND_CREDITS")
	static UPARAM(DisplayName = "Category") FString GetCategorySpendCredits()
	{       
		return AirbridgeConstants::CATEGORY::SPEND_CREDITS;
	}

#pragma endregion CATEGORY

#pragma region ATTRIBUTES
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::QUERY")
	static UPARAM(DisplayName = "Key") FString GetAttributesQuery()
	{
		return AirbridgeConstants::ATTRIBUTES::QUERY;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::PRODUCT_LIST_ID")
	static UPARAM(DisplayName = "Key") FString GetAttributesProductListID()
	{
		return AirbridgeConstants::ATTRIBUTES::PRODUCT_LIST_ID;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::CART_ID")
	static UPARAM(DisplayName = "Key") FString GetAttributesCartID()
	{
		return AirbridgeConstants::ATTRIBUTES::CART_ID;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::TRANSACTION_ID")
	static UPARAM(DisplayName = "Key") FString GetAttributesTransactionID()
	{
		return AirbridgeConstants::ATTRIBUTES::TRANSACTION_ID;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::IN_APP_PURCHASED")
	static UPARAM(DisplayName = "Key") FString GetAttributesInAppPurchased()
	{
		return AirbridgeConstants::ATTRIBUTES::IN_APP_PURCHASED;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::PRODUCTS")
	static UPARAM(DisplayName = "Key") FString GetAttributesProducts()
	{
		return AirbridgeConstants::ATTRIBUTES::PRODUCTS;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::CURRENCY")
	static UPARAM(DisplayName = "Key") FString GetAttributesCurrency()
	{
		return AirbridgeConstants::ATTRIBUTES::CURRENCY;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::TOTAL_VALUE")
	static UPARAM(DisplayName = "Key") FString GetAttributesTotalValue()
	{
		return AirbridgeConstants::ATTRIBUTES::TOTAL_VALUE;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::TOTAL_QUANTITY")
	static UPARAM(DisplayName = "Key") FString GetAttributesTotalQuantity()
	{
		return AirbridgeConstants::ATTRIBUTES::TOTAL_QUANTITY;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::ORIGINAL_CURRENCY")
	static UPARAM(DisplayName = "Key") FString GetAttributesOriginalCurrency()
	{
		return AirbridgeConstants::ATTRIBUTES::ORIGINAL_CURRENCY;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::PERIOD")
	static UPARAM(DisplayName = "Key") FString GetAttributesPeriod()
	{
		return AirbridgeConstants::ATTRIBUTES::PERIOD;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::IS_RENEWAL")
	static UPARAM(DisplayName = "Key") FString GetAttributesIsRenewal()
	{
		return AirbridgeConstants::ATTRIBUTES::IS_RENEWAL;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::RENEWAL_COUNT")
	static UPARAM(DisplayName = "Key") FString GetAttributesRenewalCount()
	{
		return AirbridgeConstants::ATTRIBUTES::RENEWAL_COUNT;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::TRANSACTION_TYPE")
	static UPARAM(DisplayName = "Key") FString GetAttributesTransactionType()
	{
		return AirbridgeConstants::ATTRIBUTES::TRANSACTION_TYPE;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::TRANSACTION_PAIRED_EVENT_CATEGORY")
	static UPARAM(DisplayName = "Key") FString GetAttributesTransactionPairedEventCategory()
	{
		return AirbridgeConstants::ATTRIBUTES::TRANSACTION_PAIRED_EVENT_CATEGORY;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::TRANSACTION_PAIRED_EVENT_TIMESTAMP")
	static UPARAM(DisplayName = "Key") FString GetAttributesTransactionPairedEventTimestamp()
	{
		return AirbridgeConstants::ATTRIBUTES::TRANSACTION_PAIRED_EVENT_TIMESTAMP;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::CONTRIBUTION_MARGIN")
	static UPARAM(DisplayName = "Key") FString GetAttributesContributionMargin()
	{
		return AirbridgeConstants::ATTRIBUTES::CONTRIBUTION_MARGIN;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::ORIGINAL_CONTRIBUTION_MARGIN")
	static UPARAM(DisplayName = "Key") FString GetAttributesOriginalContributionMargin()
	{
		return AirbridgeConstants::ATTRIBUTES::ORIGINAL_CONTRIBUTION_MARGIN;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::LIST_ID")
	static UPARAM(DisplayName = "Key") FString GetAttributesListID()
	{
		return AirbridgeConstants::ATTRIBUTES::LIST_ID;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::RATE_ID")
	static UPARAM(DisplayName = "Key") FString GetAttributesRateID()
	{
		return AirbridgeConstants::ATTRIBUTES::RATE_ID;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::RATE")
	static UPARAM(DisplayName = "Key") FString GetAttributesRate()
	{
		return AirbridgeConstants::ATTRIBUTES::RATE;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::MAX_RATE")
	static UPARAM(DisplayName = "Key") FString GetAttributesMaxRate()
	{
		return AirbridgeConstants::ATTRIBUTES::MAX_RATE;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::ACHIEVEMENT_ID")
	static UPARAM(DisplayName = "Key") FString GetAttributesAchievementID()
	{
		return AirbridgeConstants::ATTRIBUTES::ACHIEVEMENT_ID;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::SHARED_CHANNEL")
	static UPARAM(DisplayName = "Key") FString GetAttributesSharedChannel()
	{
		return AirbridgeConstants::ATTRIBUTES::SHARED_CHANNEL;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::DATE_TIME")
	static UPARAM(DisplayName = "Key") FString GetAttributesDatetime()
	{
		return AirbridgeConstants::ATTRIBUTES::DATE_TIME;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::DESCRIPTION")
	static UPARAM(DisplayName = "Key") FString GetAttributesDescription()
	{
		return AirbridgeConstants::ATTRIBUTES::DESCRIPTION;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::IS_REVENUE")
	static UPARAM(DisplayName = "Key") FString GetAttributesIsRevenue()
	{
		return AirbridgeConstants::ATTRIBUTES::IS_REVENUE;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::PLACE")
	static UPARAM(DisplayName = "Key") FString GetAttributesPlace()
	{
		return AirbridgeConstants::ATTRIBUTES::PLACE;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::SCHEDULE_ID")
	static UPARAM(DisplayName = "Key") FString GetAttributesScheduleID()
	{
		return AirbridgeConstants::ATTRIBUTES::SCHEDULE_ID;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::TYPE")
	static UPARAM(DisplayName = "Key") FString GetAttributesType()
	{
		return AirbridgeConstants::ATTRIBUTES::TYPE;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::LEVEL")
	static UPARAM(DisplayName = "Key") FString GetAttributesLevel()
	{
		return AirbridgeConstants::ATTRIBUTES::LEVEL;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Attributes", DisplayName = "ATTRIBUTES::SCORE")
	static UPARAM(DisplayName = "Key") FString GetAttributesScore()
	{
		return AirbridgeConstants::ATTRIBUTES::SCORE;
	}

#pragma endregion ATTRIBUTES

#pragma region PRODUCT
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Product", DisplayName = "PRODUCT::ID")
	static UPARAM(DisplayName = "Key") FString GetProductID()
	{
		return AirbridgeConstants::PRODUCT::ID;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Product", DisplayName = "PRODUCT::NAME")
	static UPARAM(DisplayName = "Key") FString GetProductName()
	{
		return AirbridgeConstants::PRODUCT::NAME;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Product", DisplayName = "PRODUCT::CURRENCY")
	static UPARAM(DisplayName = "Key") FString GetProductCurrency()
	{
		return AirbridgeConstants::PRODUCT::CURRENCY;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Product", DisplayName = "PRODUCT::PRICE")
	static UPARAM(DisplayName = "Key") FString GetProductPrice()
	{
		return AirbridgeConstants::PRODUCT::PRICE;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Product", DisplayName = "PRODUCT::QUANTITY")
	static UPARAM(DisplayName = "Key") FString GetProductQuantity()
	{
		return AirbridgeConstants::PRODUCT::QUANTITY;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Product", DisplayName = "PRODUCT::POSITION")
	static UPARAM(DisplayName = "Key") FString GetProductPosition()
	{
		return AirbridgeConstants::PRODUCT::POSITION;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Product", DisplayName = "PRODUCT::CATEGORY_ID")
	static UPARAM(DisplayName = "Key") FString GetProductCategoryID()
	{
		return AirbridgeConstants::PRODUCT::CATEGORY_ID;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Product", DisplayName = "PRODUCT::CATEGORY_NAME")
	static UPARAM(DisplayName = "Key") FString GetProductCategoryName()
	{
		return AirbridgeConstants::PRODUCT::CATEGORY_NAME;
	}
	
	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Product", DisplayName = "PRODUCT::BRAND_ID")
	static UPARAM(DisplayName = "Key") FString GetProductBrandID()
	{
		return AirbridgeConstants::PRODUCT::BRAND_ID;
	}

	UFUNCTION(BlueprintPure, Category = "Airbridge Constants|Product", DisplayName = "PRODUCT::BRAND_NAME")
	static UPARAM(DisplayName = "Key") FString GetProductBrandName()
	{
		return AirbridgeConstants::PRODUCT::BRAND_NAME;
	}

#pragma endregion PRODUCT
};
