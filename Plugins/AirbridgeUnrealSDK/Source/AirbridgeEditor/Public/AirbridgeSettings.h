// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AirbridgeLogLevel.h"
#include "UObject/NoExportTypes.h"
#include "AirbridgeSettings.generated.h"

UCLASS(config = Airbridge)
class UAirbridgeSettings : public UObject
{
	GENERATED_BODY()

public:
	UAirbridgeSettings(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Config, EditAnywhere, Category = "Airbridge Configure", meta = (DisplayName = "App Name"))
	FString AppName;

	UPROPERTY(Config, EditAnywhere, Category = "Airbridge Configure", meta = (DisplayName = "App Token"))
	FString AppToken;
	
	UPROPERTY(Config, EditAnywhere, Category = "Airbridge Configure", meta = (DisplayName = "Log Level"))
	EAirbridgeLogLevel LogLevel;
	
	UPROPERTY(Config, EditAnywhere, Category = "Airbridge Configure", meta = (DisplayName = "Android URI Scheme"))
	FString AndroidURIScheme;
	
	UPROPERTY(Config, EditAnywhere, Category = "Airbridge Configure", meta = (DisplayName = "iOS URI Scheme"))
	FString IOSURIScheme;

	UPROPERTY(Config, EditAnywhere, Category = "Airbridge Configure", meta = (DisplayName = "Custom Domain"))
	FString CustomDomain;

	UPROPERTY(Config, EditAnywhere, Category = "Airbridge Configure", meta = (DisplayName = "Session Timeout Seconds"))
	int32 SessionTimeoutSeconds;

	UPROPERTY(Config, EditAnywhere, Category = "Airbridge Configure", meta = (DisplayName = "User Info Hash Enabled"))
	bool UserInfoHashEnabled;

	UPROPERTY(Config, EditAnywhere, Category = "Airbridge Configure", meta = (DisplayName = "Location Collection Enabled"))
	bool LocationCollectionEnabled;

	UPROPERTY(Config, EditAnywhere, Category = "Airbridge Configure", meta = (DisplayName = "Track Airbridge Link Only"))
	bool TrackAirbridgeLinkOnly;

	UPROPERTY(Config, EditAnywhere, Category = "Airbridge Configure", meta = (DisplayName = "Auto Start Tracking Enabled"))
	bool AutoStartTrackingEnabled;

	UPROPERTY(Config, EditAnywhere, Category = "Airbridge Configure", meta = (DisplayName = "iOS Tracking Authorize Timeout Seconds"))
	int32 IOSTrackingAuthorizeTimeoutSeconds;

	UPROPERTY(Config, EditAnywhere, Category = "Airbridge Configure", meta = (DisplayName = "SDK Signature Secret ID"))
	FString SdkSignatureSecretID;

	UPROPERTY(Config, EditAnywhere, Category = "Airbridge Configure", meta = (DisplayName = "SDK Signature Secret"))
	FString SdkSignatureSecret;
};