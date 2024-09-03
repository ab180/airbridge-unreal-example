// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "UObject/NoExportTypes.h"
#include "AirbridgeMap.generated.h"

class UAirbridgeList;

/**
 * 
 */
UCLASS()
class AIRBRIDGEUNREAL_API UAirbridgeMap : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Airbridge Container|Map", meta = (DisplayName = "Create Airbridge Map"))
	static UPARAM(DisplayName = "Airbridge Map") UAirbridgeMap* CreateObject();

	/**
	 * @brief Convert JsonObject to AirbridgeMap 
	 */
	static UAirbridgeMap* CreateObject(const TSharedPtr<FJsonObject> JsonObject);

#pragma region STRING_HANDLING

	/*
	 * 문자열 처리:
	 *
	 *		1. 기본적으로 Unreal에서는 FString 클래스를 사용하여 문자열을 처리한다.
	 *		
	 *		2. C-style 문자열 (e.g. "") 을 인자로 전달받는 경우 아래와 같은 함수를 통하여 처리한다.
	 *			:
	 *				UAirbridgeMap* Set(const FString& Key, const char* Value);
	 *				
	 *		3. TEXT 매크로를 사용하는 인자를 전달받은 경우 아래와 같은 함수를 통하여 처리한다.
	 *			:
	 *				#if PLATFORM_TCHAR_IS_CHAR16
	 *					UAirbridgeMap* Set(const FString& Key, const char16_t* Value);
	 *				#else
	 *					UAirbridgeMap* Set(const FString& Key, const wchar_t* Value);
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
	UAirbridgeMap* Set(const FString& Key, const FString& Value);
	UAirbridgeMap* Set(const FString& Key, const char* Value);		// A single 8-bit character
#if PLATFORM_TCHAR_IS_CHAR16
	UAirbridgeMap* Set(const FString& Key, const char16_t* Value);	// A single 16-bit character
#else
	UAirbridgeMap* Set(const FString& Key, const wchar_t* Value);	// A single wide-character; size depends on compiler
#endif

#pragma endregion STRING_HANDLING
	// UAirbridgeMap* Set(const FString& Key, {String} Value);
	UAirbridgeMap* Set(const FString& Key, const int32 Value);
	UAirbridgeMap* Set(const FString& Key, const double Value);
	UAirbridgeMap* Set(const FString& Key, const bool Value);
	UAirbridgeMap* Set(const FString& Key, UAirbridgeList* Value);
	UAirbridgeMap* Set(const FString& Key, UAirbridgeMap* Value);
	UAirbridgeMap* Set(const FString& Key, const FJsonValue* Value);

protected:
	UFUNCTION(BlueprintCallable, Category = "Airbridge Container|Map")
	UPARAM(DisplayName = "Return Target") UAirbridgeMap* SetString(const FString& Key, const FString& Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Container|Map")
	UPARAM(DisplayName = "Return Target") UAirbridgeMap* SetInteger(const FString& Key, const int32 Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Container|Map")
	UPARAM(DisplayName = "Return Target") UAirbridgeMap* SetFloat(const FString& Key, const float Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Container|Map")
	UPARAM(DisplayName = "Return Target") UAirbridgeMap* SetBoolean(const FString& Key, const bool Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Container|Map")
	UPARAM(DisplayName = "Return Target") UAirbridgeMap* SetList(const FString& Key, UAirbridgeList* Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Container|Map")
	UPARAM(DisplayName = "Return Target") UAirbridgeMap* SetMap(const FString& Key, UAirbridgeMap* Value);

private:
	UPROPERTY()
	TMap<FString, FString> MapOfString;
	
	UPROPERTY()
	TMap<FString, int32> MapOfInteger;
	
	UPROPERTY()
	TMap<FString, double> MapOfNumber;	// support double type for c++, support float type for blueprint
	
	UPROPERTY()
	TMap<FString, bool> MapOfBoolean;
	
	UPROPERTY()
	TMap<FString, UAirbridgeList*> MapOfList;

	UPROPERTY()
	TMap<FString, UAirbridgeMap*> MapOfMap;

public:
#if PLATFORM_ANDROID
	void* CreateJavaObject() const;
#elif PLATFORM_IOS
	NSDictionary * ConvertToNSDictionary() const;
#endif
};