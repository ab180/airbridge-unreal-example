// Copyright © 2023 ab180. All rights reserved.

#include "AirbridgeBlueprint.h"

UAirbridgeBlueprint::UAirbridgeBlueprint(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

#pragma region USER
	
void UAirbridgeBlueprint::SetUserID(const FString& Id)
{
	FAirbridgeUnreal::SetUserID(Id);
}

void UAirbridgeBlueprint::SetUserEmail(const FString& Email)
{
	FAirbridgeUnreal::SetUserEmail(Email);
}

void UAirbridgeBlueprint::SetUserPhone(const FString& PhoneNumber)
{
	FAirbridgeUnreal::SetUserPhone(PhoneNumber);
}

void UAirbridgeBlueprint::SetUserIntAttribute(const FString& Key, const int32 Value)
{
	FAirbridgeUnreal::SetUserAttribute(Key, Value);
}

void UAirbridgeBlueprint::SetUserLongAttribute(const FString& Key, const int64 Value)
{
	FAirbridgeUnreal::SetUserAttribute(Key, Value);
}

void UAirbridgeBlueprint::SetUserFloatAttribute(const FString& Key, const float Value)
{
	FAirbridgeUnreal::SetUserAttribute(Key, Value);
}

void UAirbridgeBlueprint::SetUserBooleanAttribute(const FString& Key, const bool Value)
{
	FAirbridgeUnreal::SetUserAttribute(Key, Value);
}

void UAirbridgeBlueprint::SetUserStringAttribute(const FString& Key, const FString& Value)
{
	FAirbridgeUnreal::SetUserAttribute(Key, Value);
}

void UAirbridgeBlueprint::RemoveUserAttribute(const FString& Key)
{
	FAirbridgeUnreal::RemoveUserAttribute(Key);
}

void UAirbridgeBlueprint::ClearUserAttributes()
{
	FAirbridgeUnreal::ClearUserAttributes();
}

void UAirbridgeBlueprint::SetUserAlias(const FString& Key, const FString& Value)
{
	FAirbridgeUnreal::SetUserAlias(Key, Value);
}

void UAirbridgeBlueprint::RemoveUserAlias(const FString& Key)
{
	FAirbridgeUnreal::RemoveUserAlias(Key);
}

void UAirbridgeBlueprint::ClearUserAlias()
{
	FAirbridgeUnreal::ClearUserAlias();
}

void UAirbridgeBlueprint::ClearUser()
{
	FAirbridgeUnreal::ClearUser();
}
	
#pragma endregion USER

#pragma region EVENT
	
void UAirbridgeBlueprint::TrackEvent(const FString& EventCategory, const UAirbridgeEventOption* EventOption)
{
	FAirbridgeUnreal::TrackEvent(EventCategory, EventOption);
}

#pragma endregion EVENT

#pragma region PLACEMENT

void UAirbridgeBlueprint::Click(const FString& TrackingLink)
{
	FAirbridgeUnreal::Click(TrackingLink);
}

void UAirbridgeBlueprint::Impression(const FString& TrackingLink)
{
	FAirbridgeUnreal::Impression(TrackingLink);
}

#pragma endregion PLACEMENT

#pragma region CALLBACK

void UAirbridgeBlueprint::SetDeeplinkCallback()
{
	FAirbridgeUnreal::SetDeeplinkCallback();
}

void UAirbridgeBlueprint::SetAttributionCallback()
{
	FAirbridgeUnreal::SetAttributionCallback();
}

#pragma endregion CALLBACK

#pragma region DEVICE
	
void UAirbridgeBlueprint::SetDeviceAlias(const FString& Key, const FString& Value)
{
	FAirbridgeUnreal::SetDeviceAlias(Key, Value);
}

void UAirbridgeBlueprint::RemoveDeviceAlias(const FString& Key)
{
	FAirbridgeUnreal::RemoveDeviceAlias(Key);
}

void UAirbridgeBlueprint::ClearDeviceAlias()
{
	FAirbridgeUnreal::ClearDeviceAlias();
}

#pragma endregion DEVICE

#pragma region ADVANCED
	
void UAirbridgeBlueprint::StartTracking()
{
	FAirbridgeUnreal::StartTracking();
}

void UAirbridgeBlueprint::RegisterPushToken(const FString& Token)
{
	FAirbridgeUnreal::RegisterPushToken(Token);
}

#pragma endregion ADVANCED