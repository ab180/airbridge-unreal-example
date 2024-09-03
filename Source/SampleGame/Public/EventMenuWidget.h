// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EventMenuWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class SAMPLEGAME_API UEventMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SignUpButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SignInButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SignOutButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ViewHomeScreenButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ViewSearchResultButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ViewProductListButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ViewProductDetailButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* AddToCartButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* PurchaseButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* CustomEventButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* OpenMainMenuButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* StartTrackingButton;

private:
	UFUNCTION()
	void OnClickSignUpButton();
	
	UFUNCTION()
	void OnClickSignInButton();
	
	UFUNCTION()
	void OnClickSignOutButton();

	UFUNCTION()
	void OnClickViewHomeScreenButton();

	UFUNCTION()
	void OnClickViewSearchResultButton();

	UFUNCTION()
	void OnClickViewProductListButton();

	UFUNCTION()
	void OnClickViewProductDetailButton();

	UFUNCTION()
	void OnClickAddToCartButton();

	UFUNCTION()
	void OnClickPurchaseButton();

	UFUNCTION()
	void OnClickCustomEventButton();

	UFUNCTION()
	void OnClickOpenMainMenuButton();

	UFUNCTION()
	void OnClickStartTrackingButton();
	
	UFUNCTION()
	void InitButton();
};
