// Copyright © 2023 ab180. All rights reserved.

#include "AirbridgeSettings.h"

// Sets default values
UAirbridgeSettings::UAirbridgeSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, AppName("")
	, AppToken("")
	, LogLevel(EAirbridgeLogLevel::Warning)
	, AndroidURIScheme("")
	, IOSURIScheme("")
	, CustomDomain("")
	, SessionTimeoutSeconds(300)
	, UserInfoHashEnabled(true)
	, LocationCollectionEnabled(false)
	, TrackAirbridgeLinkOnly(false)
	, AutoStartTrackingEnabled(true)
	, IOSTrackingAuthorizeTimeoutSeconds(30)
	,SdkSignatureSecretID("")
	,SdkSignatureSecret("")
{
}