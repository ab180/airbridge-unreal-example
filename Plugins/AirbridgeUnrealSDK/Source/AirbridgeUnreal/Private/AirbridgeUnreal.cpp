// Copyright © 2023 ab180. All rights reserved.

#include "AirbridgeUnreal.h"
#include "AirbridgeUnrealModule.h"

#define SUPPORTED_PLATFORM (PLATFORM_ANDROID || PLATFORM_IOS)

#pragma region USER
	
void FAirbridgeUnreal::SetUserID(const FString& Id)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->SetUserID(Id);
#endif
}

void FAirbridgeUnreal::SetUserEmail(const FString& Email)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->SetUserEmail(Email);
#endif
}

void FAirbridgeUnreal::SetUserPhone(const FString& PhoneNumber)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->SetUserPhone(PhoneNumber);
#endif
}

void FAirbridgeUnreal::SetUserAttribute(const FString& Key, const int32 Value)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->SetUserAttribute(Key, Value);
#endif
}

void FAirbridgeUnreal::SetUserAttribute(const FString& Key, const int64 Value)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->SetUserAttribute(Key, Value);
#endif
}

void FAirbridgeUnreal::SetUserAttribute(const FString& Key, const float Value)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->SetUserAttribute(Key, Value);
#endif
}

void FAirbridgeUnreal::SetUserAttribute(const FString& Key, const bool Value)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->SetUserAttribute(Key, Value);
#endif
}

void FAirbridgeUnreal::SetUserAttribute(const FString& Key, const FString& Value)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->SetUserAttribute(Key, Value);
#endif
}

void FAirbridgeUnreal::SetUserAttribute(const FString& Key, const char* Value)
{
	FAirbridgeUnreal::SetUserAttribute(Key, FString(Value));
}

#if PLATFORM_TCHAR_IS_CHAR16
void FAirbridgeUnreal::SetUserAttribute(const FString& Key, const char16_t* Value)
{
	FAirbridgeUnreal::SetUserAttribute(Key, FString(Value));
}
#else
void FAirbridgeUnreal::SetUserAttribute(const FString& Key, const wchar_t* Value)
{
	FAirbridgeUnreal::SetUserAttribute(Key, FString(Value));
}
#endif

void FAirbridgeUnreal::RemoveUserAttribute(const FString& Key)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->RemoveUserAttribute(Key);
#endif
}

void FAirbridgeUnreal::ClearUserAttributes()
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->ClearUserAttributes();
#endif
}

void FAirbridgeUnreal::SetUserAlias(const FString& Key, const FString& Value)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->SetUserAlias(Key, Value);
#endif
}

void FAirbridgeUnreal::RemoveUserAlias(const FString& Key)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->RemoveUserAlias(Key);
#endif
}

void FAirbridgeUnreal::ClearUserAlias()
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->ClearUserAlias();
#endif
}

void FAirbridgeUnreal::ClearUser()
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->ClearUser();
#endif
}
	
#pragma endregion USER

#pragma region EVENT

void FAirbridgeUnreal::TrackEvent(const FString& Category, const UAirbridgeEventOption* EventOption)
{
#if SUPPORTED_PLATFORM
	if (EventOption == nullptr)
	{
		FAirbridgeUnrealModule::Get().GetAirbridge()->TrackEvent(Category);
	}
	else
	{
		FAirbridgeUnrealModule::Get().GetAirbridge()->TrackEvent(Category, *EventOption);
	}
#endif
}

#pragma endregion EVENT

#pragma region PLACEMENT

void FAirbridgeUnreal::Click(const FString& TrackingLink)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->Click(TrackingLink);
#endif
}

void FAirbridgeUnreal::Impression(const FString& TrackingLink)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->Impression(TrackingLink);
#endif
}

#pragma endregion PLACEMENT

#pragma region CALLBACK

void FAirbridgeUnreal::SetDeeplinkCallback()
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->SetDeeplinkCallback();
#endif
}

void FAirbridgeUnreal::SetAttributionCallback()
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->SetAttributionCallback();
#endif
}

#pragma endregion CALLBACK

#pragma region DEVICE
	
void FAirbridgeUnreal::SetDeviceAlias(const FString& Key, const FString& Value)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->SetDeviceAlias(Key, Value);
#endif 
}

void FAirbridgeUnreal::RemoveDeviceAlias(const FString& Key)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->RemoveDeviceAlias(Key);
#endif
}

void FAirbridgeUnreal::ClearDeviceAlias()
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->ClearDeviceAlias();
#endif
}

#pragma endregion DEVICE

#pragma region ADVANCED
	
void FAirbridgeUnreal::StartTracking()
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->StartTracking();
#endif
}

void FAirbridgeUnreal::RegisterPushToken(const FString& Token)
{
#if SUPPORTED_PLATFORM
	FAirbridgeUnrealModule::Get().GetAirbridge()->RegisterPushToken(Token);
#endif
}

IAirbridgeWebInterface* FAirbridgeUnreal::CreateWebInterface(const FString& WebToken, const AirbridgePostCommandFunction& PostCommandFunction)
{
#if SUPPORTED_PLATFORM
	return (new AirbridgeWebInterfaceImpl())->Init(WebToken, PostCommandFunction);
#endif
	return new AirbridgeWebInterfaceDefault();
}	

#pragma endregion ADVANCED