// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AirbridgeList.generated.h"

class UAirbridgeMap;

/**
 * 
 */
UCLASS()
class AIRBRIDGEUNREAL_API UAirbridgeList : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Airbridge Container|List", meta = (DisplayName = "Create Airbridge List"))
	static UPARAM(DisplayName = "Airbridge List") UAirbridgeList* CreateObject();

	/**
	 * @brief Convert JsonArray to AirbridgeList
	 */
	static UAirbridgeList* CreateObject(const TArray<TSharedPtr<FJsonValue>>& JsonArray);

#pragma region STRING_HANDLING

	/*
	 * 문자열 처리:
	 *
	 *		1. 기본적으로 Unreal에서는 FString 클래스를 사용하여 문자열을 처리한다.
	 *		
	 *		2. C-style 문자열 (e.g. "") 을 인자로 전달받는 경우 아래와 같은 함수를 통하여 처리한다.
	 *			:
	 *				UAirbridgeList* Add(const char* Value);
	 *				
	 *		3. TEXT 매크로를 사용하는 인자를 전달받은 경우 아래와 같은 함수를 통하여 처리한다.
	 *			:
	 *				#if PLATFORM_TCHAR_IS_CHAR16
	 *					UAirbridgeList* Add(const char16_t* Value);
	 *				#else
	 *					UAirbridgeList* Add(const wchar_t* Value);
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
	UAirbridgeList* Add(const FString& Value);
	UAirbridgeList* Add(const char* Value);			// A single 8-bit character
#if PLATFORM_TCHAR_IS_CHAR16
	UAirbridgeList* Add(const char16_t* Value);		// A single 16-bit character
#else
	UAirbridgeList* Add(const wchar_t* Value);		// A single wide-character; size depends on compiler
#endif

#pragma endregion STRING_HANDLING
	// 	UAirbridgeList* Add({String} Value);
	UAirbridgeList* Add(const int32 Value);
	UAirbridgeList* Add(const double Value);
	UAirbridgeList* Add(const bool Value);
	UAirbridgeList* Add(UAirbridgeList* Value);
	UAirbridgeList* Add(UAirbridgeMap* Value);
	UAirbridgeList* Add(TSharedPtr<FJsonValue> Value);
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Airbridge Container|List")
	UPARAM(DisplayName = "Return Target") UAirbridgeList* AddString(const FString& Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Container|List")
	UPARAM(DisplayName = "Return Target") UAirbridgeList* AddInteger(const int32 Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Container|List")
	UPARAM(DisplayName = "Return Target") UAirbridgeList* AddFloat(const float Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Container|List")
	UPARAM(DisplayName = "Return Target") UAirbridgeList* AddBoolean(const bool Value);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Container|List")
	UPARAM(DisplayName = "Return Target") UAirbridgeList* AddList(UAirbridgeList* Value);
	
	UFUNCTION(BlueprintCallable, Category = "Airbridge Container|List")
	UPARAM(DisplayName = "Return Target") UAirbridgeList* AddMap(UAirbridgeMap* Value);
	
private:
	UPROPERTY()
	TArray<FString> ArrayOfString;
	
	UPROPERTY()
	TArray<int32> ArrayOfInteger;
	
	UPROPERTY()
	TArray<double> ArrayOfNumber;	// support double type for c++, support float type for blueprint
	
	UPROPERTY()
	TArray<bool> ArrayOfBoolean;
	
	UPROPERTY()
	TArray<UAirbridgeList*> ArrayOfList;

	UPROPERTY()
	TArray<UAirbridgeMap*> ArrayOfMap;

public:
#if PLATFORM_ANDROID
	void* CreateJavaObject() const;
#elif PLATFORM_IOS
	NSArray * ConvertToNSArray() const;
#endif
};