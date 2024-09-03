// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UEditableText;
class UButton;

/**
 * 
 */
UCLASS()
class SAMPLEGAME_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableText* UserIdEditableText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableText* UserEmailEditableText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableText* UserPhoneEditableText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableText* UserAliasKeyEditableText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableText* UserAliasValueEditableText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SetUserIdButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SetUserEmailButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SetUserPhoneButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SetUserAliasButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RemoveUserAliasButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ClearUserAliasButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SetUserAttributesButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ClearUserAttributesButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ClearAirbridgeUserButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* OpenEventMenuButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* OpenExtraMenuButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* StartTrackingButton;

private:
	UFUNCTION()
	void OnClickSetUserIdButton();
	
	UFUNCTION()
	void OnClickSetUserEmailButton();
	
	UFUNCTION()
	void OnClickSetUserPhoneButton();

	UFUNCTION()
	void OnClickSetUserAliasButton();

	UFUNCTION()
	void OnClickRemoveUserAliasButton();

	UFUNCTION()
	void OnClickClearUserAliasButton();

	UFUNCTION()
	void OnClickSetUserAttributesButton();

	UFUNCTION()
	void OnClickClearUserAttributesButton();

	UFUNCTION()
	void OnClickClearAirbridgeUserButton();

	UFUNCTION()
	void OnClickOpenEventMenuButton();

	UFUNCTION()
	void OnClickOpenExtraMenuButton();
	
	UFUNCTION()
	void OnClickStartTrackingButton();

	UFUNCTION()
	void InitButton();
};
