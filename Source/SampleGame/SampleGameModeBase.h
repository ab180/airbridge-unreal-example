// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AirbridgeCallbacks.h"
#include "GameFramework/GameModeBase.h"
#include "SampleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEGAME_API ASampleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASampleGameModeBase();
	
	UFUNCTION()
	void OnDeeplinkReceived(const FString& Url);

	UFUNCTION()
	void OnAttributionReceived(const FAirbridgeAttribution& Attribution);
	
	UPROPERTY()
	UAirbridgeCallbacks* AirbridgeCallbacks;

protected:
	virtual void BeginPlay() override;
};
