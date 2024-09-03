// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/AirbridgeCore.h"

/**
 *
 */
class AirbridgeAndroidCore : public IAirbridgeCore
{
public:
	AirbridgeAndroidCore();
	virtual ~AirbridgeAndroidCore();

#pragma region USER
	
	virtual void SetUserID(const FString& Id) override;
	virtual void SetUserEmail(const FString& Email) override;
	virtual void SetUserPhone(const FString& PhoneNumber) override;
	virtual void SetUserAttribute(const FString& Key, const int32 Value) override;
	virtual void SetUserAttribute(const FString& Key, const int64 Value) override;
	virtual void SetUserAttribute(const FString& Key, const float Value) override;
	virtual void SetUserAttribute(const FString& Key, const bool Value) override;
	virtual void SetUserAttribute(const FString& Key, const FString& Value) override;
	virtual void RemoveUserAttribute(const FString& Key) override;
	virtual void ClearUserAttributes() override;
	virtual void SetUserAlias(const FString& Key, const FString& Value) override;
	virtual void RemoveUserAlias(const FString& Key) override;
	virtual void ClearUserAlias() override;
	virtual void ClearUser() override;

#pragma endregion USER
	
#pragma region EVENT

	virtual void TrackEvent(const FString& Category) override;
	virtual void TrackEvent(const FString& Category, const UAirbridgeEventOption& EventOption) override;

#pragma endregion EVENT

#pragma region PLACEMENT

	virtual void Click(const FString& TrackingLink) override;
	virtual void Impression(const FString& TrackingLink) override;

#pragma endregion PLACEMENT

#pragma region CALLBACK

	virtual void SetDeeplinkCallback() override;
	virtual void SetAttributionCallback() override;

#pragma endregion CALLBACK

#pragma region DEVICE

	virtual void SetDeviceAlias(const FString& Key, const FString& Value) override;
	virtual void RemoveDeviceAlias(const FString& Key) override;
	virtual void ClearDeviceAlias() override;

#pragma endregion DEVICE

#pragma region ADVANCED
	
	virtual void StartTracking() override;
	virtual void RegisterPushToken(const FString& Token) override;

#pragma endregion ADVANCED

private:
	void CallVoidMethod(const ANSICHAR* MethodName);	// "()V"
	void CallStringParamMethod(const ANSICHAR* MethodName, const FString& Param);	// "(Ljava/lang/String;)V"

public:
	// Deep Link Callback
	FThreadSafeBool DidSetDeeplinkCallback = false;
	FString StartDeeplink;
	void UnrealBroadcastDeeplink();

	// Attribution Callback
	FThreadSafeBool DidSetAttributionCallback = false;
	TMap<FString, FString> ReceivedAttribution;
	void UnrealBroadcastAttribution();
};