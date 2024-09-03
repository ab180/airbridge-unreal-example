// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AirbridgeType.h"
#include "Container/AirbridgeContainer.h"
#include "AirbridgeEventOption.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AIRBRIDGEUNREAL_API UAirbridgeEventOption : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Airbridge Event Option", meta = (DisplayName = "Create Airbridge Event Option"))
	static UPARAM(DisplayName = "Airbridge Event") UAirbridgeEventOption* CreateObject();
	
	UFUNCTION(BlueprintCallable, Category = "Airbridge Event Option")
	UPARAM(DisplayName = "Return Target") UAirbridgeEventOption* SetAction(const FString& Action);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Event Option")
	UPARAM(DisplayName = "Return Target") UAirbridgeEventOption* SetLabel(const FString& Label);

	// support double type for c++, support float type for blueprint
	UAirbridgeEventOption* SetValue(const double Value);
protected:
	UFUNCTION(BlueprintCallable, Category = "Airbridge Event Option")
	UPARAM(DisplayName = "Return Target") UAirbridgeEventOption* SetValue(const float Value);

public:
	UFUNCTION(BlueprintCallable, Category = "Airbridge Event Option")
	UPARAM(DisplayName = "Return Target") UAirbridgeEventOption* SetCustomAttributes(UAirbridgeMap* CustomAttributes);

	UFUNCTION(BlueprintCallable, Category = "Airbridge Event Option")
	UPARAM(DisplayName = "Return Target") UAirbridgeEventOption* SetSemanticAttributes(UAirbridgeMap* SemanticAttributes);
	
	FAirbridgeType<FString> Action;
	FAirbridgeType<FString> Label;
	FAirbridgeType<double> Value;

	UPROPERTY()
	UAirbridgeMap* CustomAttributes = nullptr;

	UPROPERTY()
	UAirbridgeMap* SemanticAttributes = nullptr;

#if PLATFORM_ANDROID
	/**
	 * Create Airbridge Event Object
	 */
	void* CreateJavaObject(const FString& Category) const;
#endif
};
