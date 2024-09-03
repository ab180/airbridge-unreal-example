// Copyright © 2023 ab180. All rights reserved.

#include "ExtraMenuWidget.h"

#include "AirbridgeUnreal.h"
#include "UtilsBlueprintFunction.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"

void UExtraMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->InitButton();
}

void UExtraMenuWidget::OnClickTrackingLinkClickButton()
{
	if (!TrackingLinkEditableText->GetText().IsEmpty())
	{
		const FString& TrackingLink = TrackingLinkEditableText->GetText().ToString();
		FAirbridgeUnreal::Click(TrackingLink);
		UUtilsBlueprintFunction::ShowToast("Click: " + TrackingLink);
	}
}

void UExtraMenuWidget::OnClickTrackingLinkImpressionButton()
{
	if (!TrackingLinkEditableText->GetText().IsEmpty())
	{
		const FString& TrackingLink = TrackingLinkEditableText->GetText().ToString();
		FAirbridgeUnreal::Impression(TrackingLink);
		UUtilsBlueprintFunction::ShowToast("Impression: " + TrackingLink);
	}
}

void UExtraMenuWidget::OnClickSetDeviceAliasButton()
{
	if (!DeviceAliasKeyEditableText->GetText().IsEmpty() && !DeviceAliasValueEditableText->GetText().IsEmpty())
	{
		FAirbridgeUnreal::SetDeviceAlias(
			DeviceAliasKeyEditableText->GetText().ToString(),
			DeviceAliasValueEditableText->GetText().ToString()
		);
		UUtilsBlueprintFunction::ShowToast("Set Device Alias");
	}
}

void UExtraMenuWidget::OnClickRemoveDeviceAliasButton()
{
	if (!DeviceAliasEditableText->GetText().IsEmpty())
	{
		const FString& Key = DeviceAliasEditableText->GetText().ToString();
		FAirbridgeUnreal::RemoveDeviceAlias(Key);
		UUtilsBlueprintFunction::ShowToast("Remove Device Alias \"" + Key + "\"");
	}
}

void UExtraMenuWidget::OnClickClearDeviceAliasButton()
{
	FAirbridgeUnreal::ClearDeviceAlias();
	UUtilsBlueprintFunction::ShowToast("Clear Device Alias");
}

void UExtraMenuWidget::OnClickOpenMainMenuButton()
{
	UGameplayStatics::OpenLevel(this, "Main_Menu");
	this->RemoveFromParent();
}

void UExtraMenuWidget::OnClickStartTrackingButton()
{
	FAirbridgeUnreal::StartTracking();
	UUtilsBlueprintFunction::ShowToast("Start Tracking");
}

void UExtraMenuWidget::InitButton()
{
	if (!ClickTrackingLinkButton->OnClicked.IsBound())
	{
		ClickTrackingLinkButton->OnClicked.AddDynamic(this, &UExtraMenuWidget::OnClickTrackingLinkClickButton);
	}
	if (!ImpressionTrackingLinkButton->OnClicked.IsBound())
	{
		ImpressionTrackingLinkButton->OnClicked.AddDynamic(this, &UExtraMenuWidget::OnClickTrackingLinkImpressionButton);
	}
	if (!SetDeviceAliasButton->OnClicked.IsBound())
	{
		SetDeviceAliasButton->OnClicked.AddDynamic(this, &UExtraMenuWidget::OnClickSetDeviceAliasButton);
	}
	if (!RemoveDeviceAliasButton->OnClicked.IsBound())
	{
		RemoveDeviceAliasButton->OnClicked.AddDynamic(this, &UExtraMenuWidget::OnClickRemoveDeviceAliasButton);
	}
	if (!ClearDeviceAliasButton->OnClicked.IsBound())
	{
		ClearDeviceAliasButton->OnClicked.AddDynamic(this, &UExtraMenuWidget::OnClickClearDeviceAliasButton);
	}
	if (!OpenMainMenuButton->OnClicked.IsBound())
	{
		OpenMainMenuButton->OnClicked.AddDynamic(this, &UExtraMenuWidget::OnClickOpenMainMenuButton);
	}
	if (!StartTrackingButton->OnClicked.IsBound())
	{
		StartTrackingButton->OnClicked.AddDynamic(this, &UExtraMenuWidget::OnClickStartTrackingButton);
	}
}