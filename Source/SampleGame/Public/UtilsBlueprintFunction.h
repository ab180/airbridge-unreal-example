// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilsBlueprintFunction.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEGAME_API UUtilsBlueprintFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SampleGame")
	static void ShowToast(const FString& Msg);

	UFUNCTION(BlueprintCallable, Category = "SampleGame")
	static void LogVerbose(const FString& Tag, const FString& Msg);

	UFUNCTION(BlueprintCallable, Category = "SampleGame")
	static void LogDebug(const FString& Tag, const FString& Msg);

	UFUNCTION(BlueprintCallable, Category = "SampleGame")
	static void LogInfo(const FString& Tag, const FString& Msg);

	UFUNCTION(BlueprintCallable, Category = "SampleGame")
	static void LogWarn(const FString& Tag, const FString& Msg);

	UFUNCTION(BlueprintCallable, Category = "SampleGame")
	static void LogError(const FString& Tag, const FString& Msg);

	UFUNCTION(BlueprintCallable, Category = "SampleGame")
	static void LogAssert(const FString& Tag, const FString& Msg);

	UFUNCTION(BlueprintCallable, Category = "SampleGame")
	static FString MapToString(const TMap<FString, FString>& Map);
};
