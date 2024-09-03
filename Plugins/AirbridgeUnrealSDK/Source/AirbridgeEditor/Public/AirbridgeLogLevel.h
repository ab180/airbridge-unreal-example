// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * +------------------+---------------+---------------+
 * | Unreal Log Level | Andoid Level  | iOS Level     |
 * +------------------+---------------+---------------+
 * | Fault            | Assert        | Crash         |
 * | Error            | Error         | Critical      |
 * | Warning          | Warn          | Warning       |
 * | Info             | Info          | Info          |
 * | Debug            | Verbose       | Debug         |
 * +------------------+---------------+---------------+
 */
UENUM(BlueprintType)
enum class EAirbridgeLogLevel : uint8
{
	Debug UMETA(DisplayName = "Debug"),
	Info UMETA(DisplayName = "Info"),
	Warning UMETA(DisplayName = "Warning"),
	Error UMETA(DisplayName = "Error"),
	Fault UMETA(DisplayName = "Fault"),
};

class EAirbridgeLogLevelHelper
{
public:
	static int32 GetAndroidLogLevel(EAirbridgeLogLevel Level)
	{
		switch (Level)
		{
		case EAirbridgeLogLevel::Debug:
			return 2;	// VERBOSE
		case EAirbridgeLogLevel::Info:
			return 4;	// INFO
		case EAirbridgeLogLevel::Warning:
			return 5;	// WARN
		case EAirbridgeLogLevel::Error:
			return 6;	// ERROR
		default:		// EAirbridgeLogLevel::Fault
			return 7;	// ASSERT
		}
	}
	
	static int32 GetIOSLogLevel(EAirbridgeLogLevel Level)
	{
		switch (Level)
		{
		case EAirbridgeLogLevel::Debug:
			return 5;	// AB_LOG_DEBUG
		case EAirbridgeLogLevel::Info:
			return 4;	// AB_LOG_INFO
		case EAirbridgeLogLevel::Warning:
			return 3;	// AB_LOG_WARNING
		case EAirbridgeLogLevel::Error:
			return 2;	// AB_LOG_CRITICAL
		default:		// EAirbridgeLogLevel::Fault
			return 1;	// AB_LOG_CRASH
		}
	}
};