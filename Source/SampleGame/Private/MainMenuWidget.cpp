// Copyright © 2023 ab180. All rights reserved.

#include "MainMenuWidget.h"

#include "AirbridgeUnreal.h"
#include "UtilsBlueprintFunction.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"

#if PLATFORM_IOS
#include "IOSAppTrackingTransparencyLib.h"
#endif

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	this->InitButton();

#if PLATFORM_IOS
	const EIOSAppTrackingAuthStatus Status = UIOSAppTrackingTransparencyLib::GetIOSAppTrackingAuthStatus();
	if (Status == EIOSAppTrackingAuthStatus::NotDetermined)
	{
		UIOSAppTrackingTransparencyLib::RequestIOSAppTracking();
	}
#endif
}

void UMainMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMainMenuWidget::OnClickSetUserIdButton()
{
	if (!UserIdEditableText->GetText().IsEmpty())
	{
		FAirbridgeUnreal::SetUserID(UserIdEditableText->GetText().ToString());
		UUtilsBlueprintFunction::ShowToast("Set User Id");
	}
}

void UMainMenuWidget::OnClickSetUserEmailButton()
{
	if (!UserEmailEditableText->GetText().IsEmpty())
	{
		FAirbridgeUnreal::SetUserEmail(UserEmailEditableText->GetText().ToString());
		UUtilsBlueprintFunction::ShowToast("Set User Email");
	}
}

void UMainMenuWidget::OnClickSetUserPhoneButton()
{
	if (!UserPhoneEditableText->GetText().IsEmpty())
	{
		FAirbridgeUnreal::SetUserPhone(UserPhoneEditableText->GetText().ToString());
		UUtilsBlueprintFunction::ShowToast("Set User Phone");
	}
}

void UMainMenuWidget::OnClickSetUserAliasButton()
{
	if (!UserAliasKeyEditableText->GetText().IsEmpty() && !UserAliasValueEditableText->GetText().IsEmpty())
	{
		FAirbridgeUnreal::SetUserAlias(
			UserAliasKeyEditableText->GetText().ToString(),
			UserAliasValueEditableText->GetText().ToString()
		);
		FAirbridgeUnreal::SetUserAlias(TEXT("test_key"), TEXT("test_value"));
		UUtilsBlueprintFunction::ShowToast("Set User Alias");
	}
}

void UMainMenuWidget::OnClickRemoveUserAliasButton()
{
	if (!UserAliasKeyEditableText->GetText().IsEmpty())
	{
		FAirbridgeUnreal::RemoveUserAlias(UserAliasKeyEditableText->GetText().ToString());
		UUtilsBlueprintFunction::ShowToast("Remove User Alias");
	}
}

void UMainMenuWidget::OnClickClearUserAliasButton()
{
	FAirbridgeUnreal::ClearUserAlias();
	UUtilsBlueprintFunction::ShowToast("Clear User Alias");
}

void UMainMenuWidget::OnClickSetUserAttributesButton()
{
	FAirbridgeUnreal::SetUserAttribute(TEXT("test_int_1"), 100);
	FAirbridgeUnreal::SetUserAttribute(TEXT("test_int_2"), 200);

	FAirbridgeUnreal::SetUserAttribute(TEXT("test_long_1"), 1000);
	FAirbridgeUnreal::SetUserAttribute(TEXT("test_long_2"), 2000);
	
	FAirbridgeUnreal::SetUserAttribute(TEXT("test_float_1"), 3.14F);
	FAirbridgeUnreal::SetUserAttribute(TEXT("test_float_2"), 5.67F);

	FAirbridgeUnreal::SetUserAttribute(TEXT("test_boolean_1"), true);
	FAirbridgeUnreal::SetUserAttribute(TEXT("test_boolean_2"), false);

	FAirbridgeUnreal::SetUserAttribute(TEXT("test_string_1"), TEXT("Hello_World"));
	FAirbridgeUnreal::SetUserAttribute(TEXT("test_string_2"), TEXT("Airbridge_Test"));

	UUtilsBlueprintFunction::ShowToast("Set User Attributes");
}

void UMainMenuWidget::OnClickClearUserAttributesButton()
{
	FAirbridgeUnreal::ClearUserAttributes();
	UUtilsBlueprintFunction::ShowToast("Clear User Attributes");
}

void UMainMenuWidget::OnClickClearAirbridgeUserButton()
{
	FAirbridgeUnreal::ClearUser();
	UUtilsBlueprintFunction::ShowToast("Clear Airbridge User");
}

void UMainMenuWidget::OnClickOpenEventMenuButton()
{
	UGameplayStatics::OpenLevel(this, "Event_Menu");
	this->RemoveFromParent();
}

void UMainMenuWidget::OnClickOpenExtraMenuButton()
{
	UGameplayStatics::OpenLevel(this, "Extra_Menu");
	this->RemoveFromParent();
}

void UMainMenuWidget::OnClickStartTrackingButton()
{
	FAirbridgeUnreal::StartTracking();
	UUtilsBlueprintFunction::ShowToast("Start Tracking");
}

void UMainMenuWidget::InitButton()
{
	if (!SetUserIdButton->OnClicked.IsBound())
	{
		SetUserIdButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickSetUserIdButton);
	}
	if (!SetUserEmailButton->OnClicked.IsBound())
	{
		SetUserEmailButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickSetUserEmailButton);
	}
	if (!SetUserPhoneButton->OnClicked.IsBound())
	{
		SetUserPhoneButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickSetUserPhoneButton);
	}
	if (!SetUserAliasButton->OnClicked.IsBound())
	{
		SetUserAliasButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickSetUserAliasButton);
	}
	if (!RemoveUserAliasButton->OnClicked.IsBound())
	{
		RemoveUserAliasButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickRemoveUserAliasButton);
	}
	if (!ClearUserAliasButton->OnClicked.IsBound())
	{
		ClearUserAliasButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickClearUserAliasButton);
	}
	if (!SetUserAttributesButton->OnClicked.IsBound())
	{
		SetUserAttributesButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickSetUserAttributesButton);
	}
	if (!ClearUserAttributesButton->OnClicked.IsBound())
	{
		ClearUserAttributesButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickClearUserAttributesButton);
	}
	if (!ClearAirbridgeUserButton->OnClicked.IsBound())
	{
		ClearAirbridgeUserButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickClearAirbridgeUserButton);
	}
	if (!OpenEventMenuButton->OnClicked.IsBound())
	{
		OpenEventMenuButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickOpenEventMenuButton);
	}
	if (!OpenExtraMenuButton->OnClicked.IsBound())
	{
		OpenExtraMenuButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickOpenExtraMenuButton);
	}
	if (!StartTrackingButton->OnClicked.IsBound())
	{
		StartTrackingButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickStartTrackingButton);
	}
}
