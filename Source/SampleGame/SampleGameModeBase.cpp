// Copyright © 2023 ab180. All rights reserved.

#include "SampleGameModeBase.h"
#include "AirbridgeUnreal.h"
#include "UtilsBlueprintFunction.h"

ASampleGameModeBase::ASampleGameModeBase()
{
	AirbridgeCallbacks = CreateDefaultSubobject<UAirbridgeCallbacks>(TEXT("AIRBRIDGE_CALLBACKS"));
}

void ASampleGameModeBase::BeginPlay()
{
	AirbridgeCallbacks->OnDeeplinkReceived.AddDynamic(this, &ASampleGameModeBase::OnDeeplinkReceived);
	AirbridgeCallbacks->OnAttributionReceived.AddDynamic(this, &ASampleGameModeBase::OnAttributionReceived);
	
	// Call SetDeeplinkCallback to receive user-clicked deep link data
	FAirbridgeUnreal::SetDeeplinkCallback();
	
	// Call SetAttributionCallback to receive attribution data
	FAirbridgeUnreal::SetAttributionCallback();
}

// Method will be called by Airbridge when deeplink detected
void ASampleGameModeBase::OnDeeplinkReceived(const FString& Url)
{
	UUtilsBlueprintFunction::ShowToast(Url);
}

void ASampleGameModeBase::OnAttributionReceived(const FAirbridgeAttribution& Attribution)
{
	UUtilsBlueprintFunction::ShowToast(UUtilsBlueprintFunction::MapToString(Attribution.Data));
}