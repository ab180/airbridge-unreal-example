// Copyright © 2023 ab180. All rights reserved.

#include "EventMenuWidget.h"

#include "AirbridgeUnreal.h"
#include "UtilsBlueprintFunction.h"
#include "Airbridge/AirbridgeConstants.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UEventMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->InitButton();
}

void UEventMenuWidget::OnClickSignUpButton()
{
	FAirbridgeUnreal::SetUserID("personID");
	FAirbridgeUnreal::SetUserEmail("persondoe@airbridge.io");
	FAirbridgeUnreal::SetUserPhone("1(123)123-1234");
	FAirbridgeUnreal::SetUserAlias(TEXT("alias1"), TEXT("value"));

	FAirbridgeUnreal::TrackEvent(AirbridgeConstants::CATEGORY::SIGN_UP);
	UUtilsBlueprintFunction::ShowToast("Track Event : " + AirbridgeConstants::CATEGORY::SIGN_UP);
}

void UEventMenuWidget::OnClickSignInButton()
{
	FAirbridgeUnreal::SetUserID("personID");
	FAirbridgeUnreal::SetUserEmail("persondoe@airbridge.io");
	FAirbridgeUnreal::SetUserPhone("1(123)123-1234");
	FAirbridgeUnreal::SetUserAlias(TEXT("alias1"), TEXT("value"));

	FAirbridgeUnreal::TrackEvent(AirbridgeConstants::CATEGORY::SIGN_IN);
	UUtilsBlueprintFunction::ShowToast("Track Event : " + AirbridgeConstants::CATEGORY::SIGN_IN);
}

void UEventMenuWidget::OnClickSignOutButton()
{
	FAirbridgeUnreal::TrackEvent(AirbridgeConstants::CATEGORY::SIGN_OUT);
	FAirbridgeUnreal::ClearUser();

	UUtilsBlueprintFunction::ShowToast("Track Event : " + AirbridgeConstants::CATEGORY::SIGN_OUT);
}

void UEventMenuWidget::OnClickViewHomeScreenButton()
{
	FAirbridgeUnreal::TrackEvent(AirbridgeConstants::CATEGORY::HOME_VIEWED);
	UUtilsBlueprintFunction::ShowToast("Track Event : " + AirbridgeConstants::CATEGORY::HOME_VIEWED);
}

void UEventMenuWidget::OnClickViewSearchResultButton()
{
	UAirbridgeList* Beverages = UAirbridgeList::CreateObject();

	UAirbridgeMap* Cocacola = UAirbridgeMap::CreateObject()
	->Set(AirbridgeConstants::PRODUCT::ID, "beverage_1")
	->Set(AirbridgeConstants::PRODUCT::NAME, "Coca Cola")
	->Set(AirbridgeConstants::PRODUCT::PRICE, 1.25)
	->Set(AirbridgeConstants::PRODUCT::CURRENCY, "USD")
	->Set(AirbridgeConstants::PRODUCT::QUANTITY, 1)
	->Set(AirbridgeConstants::PRODUCT::POSITION, 0);
	Beverages->Add(Cocacola);

	UAirbridgeMap* Fanta = UAirbridgeMap::CreateObject()
	->Set(AirbridgeConstants::PRODUCT::ID, "beverage_2")
	->Set(AirbridgeConstants::PRODUCT::NAME, "Fanta")
	->Set(AirbridgeConstants::PRODUCT::PRICE, 10.99)
	->Set(AirbridgeConstants::PRODUCT::CURRENCY, "USD")
	->Set(AirbridgeConstants::PRODUCT::QUANTITY, 1)
	->Set(AirbridgeConstants::PRODUCT::POSITION, 1);
	Beverages->Add(Fanta);
	
	UAirbridgeMap* SemanticAttributes = UAirbridgeMap::CreateObject()
	->Set(AirbridgeConstants::ATTRIBUTES::QUERY, "SELECT * FROM beverages")
	->Set(AirbridgeConstants::ATTRIBUTES::PRODUCTS, Beverages);
	
	FAirbridgeUnreal::TrackEvent(
		AirbridgeConstants::CATEGORY::SEARCH_RESULTS_VIEWED,
		UAirbridgeEventOption::CreateObject()
		->SetValue(12.24)
		->SetSemanticAttributes(SemanticAttributes)
	);
	UUtilsBlueprintFunction::ShowToast("Track Event : " + AirbridgeConstants::CATEGORY::SEARCH_RESULTS_VIEWED);
	
	SemanticAttributes->ConditionalBeginDestroy();
	Fanta->ConditionalBeginDestroy();
	Cocacola->ConditionalBeginDestroy();
	Fanta->ConditionalBeginDestroy();
	Beverages->ConditionalBeginDestroy();
}

void UEventMenuWidget::OnClickViewProductListButton()
{
	UAirbridgeList* Beverages = UAirbridgeList::CreateObject();

	UAirbridgeMap* Cocacola = UAirbridgeMap::CreateObject()
	->Set(AirbridgeConstants::PRODUCT::ID, "beverage_1")
	->Set(AirbridgeConstants::PRODUCT::NAME, "Coca Cola")
	->Set(AirbridgeConstants::PRODUCT::PRICE, 1.25)
	->Set(AirbridgeConstants::PRODUCT::CURRENCY, "USD")
	->Set(AirbridgeConstants::PRODUCT::QUANTITY, 1)
	->Set(AirbridgeConstants::PRODUCT::POSITION, 0);
	Beverages->Add(Cocacola);

	UAirbridgeMap* Fanta = UAirbridgeMap::CreateObject()
	->Set(AirbridgeConstants::PRODUCT::ID, "beverage_3")
	->Set(AirbridgeConstants::PRODUCT::NAME, "Fanta")
	->Set(AirbridgeConstants::PRODUCT::PRICE, 10.99)
	->Set(AirbridgeConstants::PRODUCT::CURRENCY, "USD")
	->Set(AirbridgeConstants::PRODUCT::QUANTITY, 1)
	->Set(AirbridgeConstants::PRODUCT::POSITION, 2);
	Beverages->Add(Fanta);

	UAirbridgeMap* SemanticAttributes = UAirbridgeMap::CreateObject()
	->Set(AirbridgeConstants::ATTRIBUTES::PRODUCT_LIST_ID, "beverage_list_0")
	->Set(AirbridgeConstants::ATTRIBUTES::PRODUCTS, Beverages);
	
	FAirbridgeUnreal::TrackEvent(
		AirbridgeConstants::CATEGORY::PRODUCT_LIST_VIEWED,
		UAirbridgeEventOption::CreateObject()
		->SetValue(12.24)
		->SetSemanticAttributes(SemanticAttributes)
	);
	UUtilsBlueprintFunction::ShowToast("Track Event : " + AirbridgeConstants::CATEGORY::PRODUCT_LIST_VIEWED);
	
	SemanticAttributes->ConditionalBeginDestroy();
	Fanta->ConditionalBeginDestroy();
	Cocacola->ConditionalBeginDestroy();
	Fanta->ConditionalBeginDestroy();
	Beverages->ConditionalBeginDestroy();
}

void UEventMenuWidget::OnClickViewProductDetailButton()
{
	UAirbridgeList* Products = UAirbridgeList::CreateObject();
	
	UAirbridgeMap* Cocacola = UAirbridgeMap::CreateObject()
	->Set(AirbridgeConstants::PRODUCT::ID, "beverage_1")
	->Set(AirbridgeConstants::PRODUCT::NAME, "Coca Cola")
	->Set(AirbridgeConstants::PRODUCT::PRICE, 1.25)
	->Set(AirbridgeConstants::PRODUCT::CURRENCY, "USD")
	->Set(AirbridgeConstants::PRODUCT::QUANTITY, 1)
	->Set(AirbridgeConstants::PRODUCT::POSITION, 0);
	Products->Add(Cocacola);

	UAirbridgeMap* SemanticAttributes = UAirbridgeMap::CreateObject()
	->Set(AirbridgeConstants::ATTRIBUTES::PRODUCTS, Products);

	FAirbridgeUnreal::TrackEvent(
		AirbridgeConstants::CATEGORY::PRODUCT_VIEWED,
		UAirbridgeEventOption::CreateObject()
		->SetSemanticAttributes(SemanticAttributes)
	);
	UUtilsBlueprintFunction::ShowToast("Track Event : " + AirbridgeConstants::CATEGORY::PRODUCT_VIEWED);
	
	SemanticAttributes->ConditionalBeginDestroy();
	Cocacola->ConditionalBeginDestroy();
	Products->ConditionalBeginDestroy();
}

void UEventMenuWidget::OnClickAddToCartButton()
{
	UAirbridgeList* Products = UAirbridgeList::CreateObject();
    
	UAirbridgeMap* Cocacola = UAirbridgeMap::CreateObject()
		->Set(AirbridgeConstants::PRODUCT::ID, "beverage_1")
		->Set(AirbridgeConstants::PRODUCT::NAME, "Coca Cola")
		->Set(AirbridgeConstants::PRODUCT::PRICE, 1.25)
		->Set(AirbridgeConstants::PRODUCT::CURRENCY, "USD")
		->Set(AirbridgeConstants::PRODUCT::QUANTITY, 1)
		->Set(AirbridgeConstants::PRODUCT::POSITION, 0);
	Products->Add(Cocacola);

	UAirbridgeMap* SemanticAttributes = UAirbridgeMap::CreateObject()
		->Set(AirbridgeConstants::ATTRIBUTES::PRODUCTS, Products);

	FAirbridgeUnreal::TrackEvent(
		AirbridgeConstants::CATEGORY::ADDED_TO_CART,
		UAirbridgeEventOption::CreateObject()
			->SetValue(1.25)
			->SetSemanticAttributes(SemanticAttributes)
	);

	// Optional (Remove the resource immediately)
	SemanticAttributes->ConditionalBeginDestroy();
	Cocacola->ConditionalBeginDestroy();
	Products->ConditionalBeginDestroy();
}

void UEventMenuWidget::OnClickPurchaseButton()
{
	UAirbridgeList* Beverages = UAirbridgeList::CreateObject();

	UAirbridgeMap* Cocacola = UAirbridgeMap::CreateObject()
		->Set(AirbridgeConstants::PRODUCT::ID, "beverage_1")
		->Set(AirbridgeConstants::PRODUCT::NAME, "Coca Cola")
		->Set(AirbridgeConstants::PRODUCT::PRICE, 1.25)
		->Set(AirbridgeConstants::PRODUCT::CURRENCY, "USD")
		->Set(AirbridgeConstants::PRODUCT::QUANTITY, 1)
		->Set(AirbridgeConstants::PRODUCT::POSITION, 0);
	Beverages->Add(Cocacola);

	UAirbridgeMap* Fanta = UAirbridgeMap::CreateObject()
		->Set(AirbridgeConstants::PRODUCT::ID, "beverage_3")
		->Set(AirbridgeConstants::PRODUCT::NAME, "Fanta")
		->Set(AirbridgeConstants::PRODUCT::PRICE, 10.99)
		->Set(AirbridgeConstants::PRODUCT::CURRENCY, "USD")
		->Set(AirbridgeConstants::PRODUCT::QUANTITY, 1)
		->Set(AirbridgeConstants::PRODUCT::POSITION, 2);
	Beverages->Add(Fanta);
    
	UAirbridgeMap* SemanticAttributes = UAirbridgeMap::CreateObject()
		->Set(AirbridgeConstants::ATTRIBUTES::TRANSACTION_ID, "transaction_123")
		->Set(AirbridgeConstants::ATTRIBUTES::PRODUCTS, Beverages)
		->Set(AirbridgeConstants::ATTRIBUTES::IN_APP_PURCHASED, true);
    
	FAirbridgeUnreal::TrackEvent(
		AirbridgeConstants::CATEGORY::ORDER_COMPLETED,
		UAirbridgeEventOption::CreateObject()
			->SetValue(12.24)
			->SetSemanticAttributes(SemanticAttributes)
	);

	// Optional (Remove the resource immediately)
	SemanticAttributes->ConditionalBeginDestroy();
	Fanta->ConditionalBeginDestroy();
	Cocacola->ConditionalBeginDestroy();
	Fanta->ConditionalBeginDestroy();
	Beverages->ConditionalBeginDestroy();
}

// {
// 	"category": "category",
// 	"action": "action",
// 	"label": "label",
// 	"value": 100.99,
// 	"customAttributes": {
// 		"model": "MMM",
// 		"report": {
// 			"start_date": "2022-01-01",
// 			"end_date": "2022-12-31",
// 			"channel_attributions": [
// 			  {
// 				"channel": "Paid Search",
// 				"attributed_conversions": 100,
// 				"attributed_revenue": 1000
// 			  },
// 			  {
// 				"channel": "Organic Search",
// 				"attributed_conversions": 75,
// 				"attributed_revenue": 500
// 			  },
// 			  {
// 				"channel": "Email",
// 				"attributed_conversions": 50,
// 				"attributed_revenue": 250
// 			  }
// 			]
// 		}
// 	},
// 	"semanticAttributes": {
// 		"query": "query_123"
// 	}
// }
void UEventMenuWidget::OnClickCustomEventButton()
{
	FAirbridgeUnreal::TrackEvent(
		"category",
		UAirbridgeEventOption::CreateObject()
		->SetAction("action")
		->SetLabel("label")
		->SetValue(100.99)
		->SetCustomAttributes(
			UAirbridgeMap::CreateObject()
			->Set("model", "MMM")
			->Set("report", UAirbridgeMap::CreateObject()
				->Set("start_date", TEXT("2022-01-01"))
				->Set("end_date", TEXT("2022-12-31"))
				->Set("channel_attributions", UAirbridgeList::CreateObject()
					->Add(UAirbridgeMap::CreateObject()
						->Set("channel", "Paid Search")
						->Set("attributed_conversions", 100)
						->Set("attributed_revenue", 1000)
					)
					->Add(UAirbridgeMap::CreateObject()
						->Set("channel", "Organic Search")
						->Set("attributed_conversions", 75)
						->Set("attributed_revenue", 500)
					)
					->Add(UAirbridgeMap::CreateObject()
						->Set("channel", "Email")
						->Set("attributed_conversions", 50)
						->Set("attributed_revenue", 250)
					)
				)
			)
		)
		->SetSemanticAttributes(UAirbridgeMap::CreateObject()
			->Set(AirbridgeConstants::ATTRIBUTES::QUERY, "query_123"))
	);
	UUtilsBlueprintFunction::ShowToast("Track Event : Custom Events");
}

void UEventMenuWidget::OnClickOpenMainMenuButton()
{
	UGameplayStatics::OpenLevel(this, "Main_Menu");
	this->RemoveFromParent();
}

void UEventMenuWidget::OnClickStartTrackingButton()
{
	FAirbridgeUnreal::StartTracking();
	UUtilsBlueprintFunction::ShowToast("Start Tracking");
}

void UEventMenuWidget::InitButton()
{
	if (!SignUpButton->OnClicked.IsBound())
	{
		SignUpButton->OnClicked.AddDynamic(this, &UEventMenuWidget::OnClickSignUpButton);
	}
	if (!SignInButton->OnClicked.IsBound())
	{
		SignInButton->OnClicked.AddDynamic(this, &UEventMenuWidget::OnClickSignInButton);
	}
	if (!SignOutButton->OnClicked.IsBound())
	{
		SignOutButton->OnClicked.AddDynamic(this, &UEventMenuWidget::OnClickSignOutButton);
	}
	if (!ViewHomeScreenButton->OnClicked.IsBound())
	{
		ViewHomeScreenButton->OnClicked.AddDynamic(this, &UEventMenuWidget::OnClickViewHomeScreenButton);
	}
	if (!ViewSearchResultButton->OnClicked.IsBound())
	{
		ViewSearchResultButton->OnClicked.AddDynamic(this, &UEventMenuWidget::OnClickViewSearchResultButton);
	}
	if (!ViewProductListButton->OnClicked.IsBound())
	{
		ViewProductListButton->OnClicked.AddDynamic(this, &UEventMenuWidget::OnClickViewProductListButton);
	}
	if (!ViewProductDetailButton->OnClicked.IsBound())
	{
		ViewProductDetailButton->OnClicked.AddDynamic(this, &UEventMenuWidget::OnClickViewProductDetailButton);
	}
	if (!AddToCartButton->OnClicked.IsBound())
	{
		AddToCartButton->OnClicked.AddDynamic(this, &UEventMenuWidget::OnClickAddToCartButton);
	}
	if (!PurchaseButton->OnClicked.IsBound())
	{
		PurchaseButton->OnClicked.AddDynamic(this, &UEventMenuWidget::OnClickPurchaseButton);
	}
	if (!CustomEventButton->OnClicked.IsBound())
	{
		CustomEventButton->OnClicked.AddDynamic(this, &UEventMenuWidget::OnClickCustomEventButton);
	}
	if (!OpenMainMenuButton->OnClicked.IsBound())
	{
		OpenMainMenuButton->OnClicked.AddDynamic(this, &UEventMenuWidget::OnClickOpenMainMenuButton);
	}
	if (!StartTrackingButton->OnClicked.IsBound())
	{
		StartTrackingButton->OnClicked.AddDynamic(this, &UEventMenuWidget::OnClickStartTrackingButton);
	}
}
