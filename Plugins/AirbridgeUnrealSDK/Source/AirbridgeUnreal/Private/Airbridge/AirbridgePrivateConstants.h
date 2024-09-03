// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"

namespace AirbridgeConstants
{
	namespace Hybrid
	{
		static const FString Method					(TEXT("method"));
		static const FString SetUserMethod			(TEXT("setUser"));
		static const FString ClearUserMethod		(TEXT("clearUser"));
		static const FString TrackEventMethod		(TEXT("trackEvent"));
		
		static const FString Payload						(TEXT("payload"));
		static const FString UserIdKey						(TEXT("id"));
		static const FString UserEmailKey					(TEXT("email"));
		static const FString UserPhoneKey					(TEXT("phone"));
		static const FString UserAliasKey					(TEXT("alias"));
		static const FString UserAttributesKey				(TEXT("attributes"));
		static const FString EventCategoryKey				(TEXT("category"));
		static const FString EventActionKey					(TEXT("action"));
		static const FString EventLabelKey					(TEXT("label"));
		static const FString EventValueKey					(TEXT("value"));
		static const FString EventSemanticAttributesKey		(TEXT("semantic_attributes"));
		static const FString EventCustomAttributesKey		(TEXT("custom_attributes"));
	}
}
