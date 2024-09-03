// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AirbridgeCallbacks.generated.h"

USTRUCT(Blueprintable)
struct FAirbridgeAttribution
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> Data;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeeplinkReceived, const FString&, Url);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributionReceived, const FAirbridgeAttribution&, AttributionResult);

UCLASS( ClassGroup=("Airbridge Unreal SDK"), meta=(BlueprintSpawnableComponent) )
class AIRBRIDGEUNREAL_API UAirbridgeCallbacks : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAirbridgeCallbacks(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Airbridge Unreal SDK")
	FOnDeeplinkReceived OnDeeplinkReceived;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Airbridge Unreal SDK")
	FOnAttributionReceived OnAttributionReceived;
};
