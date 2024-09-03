// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AirbridgeWebInterface.h"
#include "Airbridge/AirbridgeEventOption.h"

/**
 * 
 */
class AIRBRIDGEUNREAL_API FAirbridgeUnreal
{
public:

#pragma region USER
	
	static void SetUserID(const FString& Id);
	static void SetUserEmail(const FString& Email);
	static void SetUserPhone(const FString& PhoneNumber);
	static void SetUserAttribute(const FString& Key, const int32 Value);
	static void SetUserAttribute(const FString& Key, const int64 Value);
	static void SetUserAttribute(const FString& Key, const float Value);
	static void SetUserAttribute(const FString& Key, const bool Value);
	// static void SetUserAttribute(const FString& Key, {String} Value);
#pragma region STRING_HANDLING

	/*
	 * 문자열 처리:
	 *
	 *		1. 기본적으로 Unreal에서는 FString 클래스를 사용하여 문자열을 처리한다.
	 *		
	 *		2. C-style 문자열 (e.g. "") 을 인자로 전달받는 경우 아래와 같은 함수를 통하여 처리한다.
	 *			:
	 *				static void SetUserAttribute(const FString& Key, const char* Value);
	 *				
	 *		3. TEXT 매크로를 사용하는 인자를 전달받은 경우 아래와 같은 함수를 통하여 처리한다.
	 *			:
	 *				#if PLATFORM_TCHAR_IS_CHAR16
	 *					static void SetUserAttribute(const FString& Key, const char16_t* Value);
	 *				#else
	 *					static void SetUserAttribute(const FString& Key, const wchar_t* Value);
	 *
	 *			===================================================================================
	 *			TEXT Macro
	 *			(/Users/Shared/Epic Games/UE_4.26/Engine/Source/Runtime/Core/Public/HAL/Platform.h)
	 *			===================================================================================
	 *			#if !defined(TEXT) && !UE_BUILD_DOCS
	 *				#if PLATFORM_TCHAR_IS_CHAR16
	 *					#define TEXT_PASTE(x) u ## x
	 *				#else
	 *					#define TEXT_PASTE(x) L ## x
	 *				#endif
	 *					#define TEXT(x) TEXT_PASTE(x)
	 *			#endif
	 *			===================================================================================
	 *
	 *		ps. 추가로 문제가 발생할 경우 가장 간단하게 해결할 수 있는 방법은 메서드 오버로드를 해제하는 것이다.
	 *///
	static void SetUserAttribute(const FString& Key, const FString& Value);
	static void SetUserAttribute(const FString& Key, const char* Value);		// A single 8-bit character
#if PLATFORM_TCHAR_IS_CHAR16
	static void SetUserAttribute(const FString& Key, const char16_t* Value);	// A single 16-bit character
#else
	static void SetUserAttribute(const FString& Key, const wchar_t* Value);		// A single wide-character; size depends on compiler
#endif

#pragma endregion STRING_HANDLING

	static void RemoveUserAttribute(const FString& Key);
	static void ClearUserAttributes();
	static void SetUserAlias(const FString& Key, const FString& Value);
	static void RemoveUserAlias(const FString& Key);
	static void ClearUserAlias();
	static void ClearUser();
	
#pragma endregion USER

#pragma region EVENT

	static void TrackEvent(const FString& Category, const UAirbridgeEventOption* EventOption = nullptr);

#pragma endregion EVENT

#pragma region PLACEMENT

	static void Click(const FString& TrackingLink);
	static void Impression(const FString& TrackingLink);

#pragma endregion PLACEMENT

#pragma region CALLBACK

	static void SetDeeplinkCallback();
	static void SetAttributionCallback();

#pragma endregion CALLBACK

#pragma region DEVICE
	
	static void SetDeviceAlias(const FString& Key, const FString& Value);
	static void RemoveDeviceAlias(const FString& Key);
	static void ClearDeviceAlias();

#pragma endregion DEVICE

#pragma region ADVANCED
	
	static void StartTracking();
	static void RegisterPushToken(const FString& Token);
	static IAirbridgeWebInterface* CreateWebInterface(const FString& WebToken, const AirbridgePostCommandFunction& PostCommandFunction);

#pragma endregion ADVANCED
};