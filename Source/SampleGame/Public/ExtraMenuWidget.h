// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExtraMenuWidget.generated.h"

class UEditableText;
class UButton;

/**
 * 
 */
UCLASS()
class SAMPLEGAME_API UExtraMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableText* TrackingLinkEditableText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableText* DeviceAliasKeyEditableText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableText* DeviceAliasValueEditableText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableText* DeviceAliasEditableText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ClickTrackingLinkButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ImpressionTrackingLinkButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SetDeviceAliasButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RemoveDeviceAliasButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ClearDeviceAliasButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* OpenMainMenuButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* StartTrackingButton;

private:
	UFUNCTION()
	void OnClickTrackingLinkClickButton();

	UFUNCTION()
	void OnClickTrackingLinkImpressionButton();

	UFUNCTION()
	void OnClickSetDeviceAliasButton();

	UFUNCTION()
	void OnClickRemoveDeviceAliasButton();
	
	UFUNCTION()
	void OnClickClearDeviceAliasButton();

	UFUNCTION()
	void OnClickOpenMainMenuButton();

	UFUNCTION()
	void OnClickStartTrackingButton();
	
	UFUNCTION()
	void InitButton();
};
