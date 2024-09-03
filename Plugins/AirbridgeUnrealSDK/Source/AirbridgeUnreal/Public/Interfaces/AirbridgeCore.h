// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "EngineMinimal.h"
#include "Airbridge/AirbridgeEventOption.h"

class IAirbridgeCore
{
public:

#pragma region USER
	
	virtual void SetUserID(const FString& Id) = 0;
	virtual void SetUserEmail(const FString& Email) = 0;
	virtual void SetUserPhone(const FString& PhoneNumber) = 0;
	virtual void SetUserAttribute(const FString& Key, const int32 Value) = 0;
	virtual void SetUserAttribute(const FString& Key, const int64 Value) = 0;
	virtual void SetUserAttribute(const FString& Key, const float Value) = 0;
	virtual void SetUserAttribute(const FString& Key, const bool Value) = 0;
	virtual void SetUserAttribute(const FString& Key, const FString& Value) = 0;
	virtual void RemoveUserAttribute(const FString& Key) = 0;
	virtual void ClearUserAttributes() = 0;
	virtual void SetUserAlias(const FString& Key, const FString& Value) = 0;
	virtual void RemoveUserAlias(const FString& Key) = 0;
	virtual void ClearUserAlias() = 0;
	virtual void ClearUser() = 0;

#pragma endregion USER

#pragma region EVENT

	virtual void TrackEvent(const FString& Category) = 0;
	virtual void TrackEvent(const FString& Category, const UAirbridgeEventOption& EventOption) = 0;

#pragma endregion EVENT

#pragma region PLACEMENT

	virtual void Click(const FString& TrackingLink) = 0;
	virtual void Impression(const FString& TrackingLink) = 0;

#pragma endregion PLACEMENT

#pragma region CALLBACK

	/**
	 * @brief When you register your deeplink callback,
	 * 'Airbridge' will call "void <CallbackFuncName>(const FString& Url)" method
	 */
	virtual void SetDeeplinkCallback() = 0;

	/**
	 * @brief When you register your attribution callback,
	 * 'Airbridge' will call "void <CallbackFuncName>(const FAirbridgeAttribution& Attribution)" method
	 */
	virtual void SetAttributionCallback() = 0;

#pragma endregion CALLBACK

#pragma region DEVICE

	virtual void SetDeviceAlias(const FString& Key, const FString& Value) = 0;
	virtual void RemoveDeviceAlias(const FString& Key) = 0;
	virtual void ClearDeviceAlias() = 0;
	
#pragma endregion DEVICE

#pragma region ADVANCED
	
	virtual void StartTracking() = 0;
	virtual void RegisterPushToken(const FString& Token) = 0;

#pragma endregion ADVANCED
};
