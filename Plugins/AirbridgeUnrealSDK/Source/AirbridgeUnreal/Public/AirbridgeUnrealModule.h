// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "EngineMinimal.h"
#include "Interfaces/AirbridgeCore.h"

typedef TSharedPtr<IAirbridgeCore, ESPMode::ThreadSafe> FAirbridgeCorePointer;

class FAirbridgeUnrealModule : public IModuleInterface
{
public:
	static inline FAirbridgeUnrealModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FAirbridgeUnrealModule>("AirbridgeUnreal");
	}

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	inline FAirbridgeCorePointer GetAirbridge() const
	{
		return AirbridgeCorePointer;
	}

protected:
	FAirbridgeCorePointer AirbridgeCorePointer;
};
