// Copyright © 2023 ab180. All rights reserved.

#include "AirbridgeUnrealModule.h"

#if PLATFORM_ANDROID
#include "Platforms/Android/AirbridgeAndroidCore.h"
#elif PLATFORM_IOS
#include "Platforms/iOS/AirbridgeIOSCore.h"
#endif

#define LOCTEXT_NAMESPACE "FAirbridgeUnrealModule"

void FAirbridgeUnrealModule::StartupModule()
{
	// This code will execute after your module is loaded into memory;
	// the exact timing is specified in the .uplugin file per-module

#if PLATFORM_ANDROID
	AirbridgeCorePointer = MakeShareable(new AirbridgeAndroidCore());
#elif PLATFORM_IOS
	AirbridgeCorePointer = MakeShareable(new AirbridgeIOSCore());
#endif
}

void FAirbridgeUnrealModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module. For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAirbridgeUnrealModule, AirbridgeUnreal)