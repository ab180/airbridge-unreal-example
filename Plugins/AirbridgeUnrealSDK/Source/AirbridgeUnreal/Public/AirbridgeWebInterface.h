// Copyright © 2023 ab180. All rights reserved.

#pragma once

#include "CoreMinimal.h"

typedef TFunction<FString(const FString&)> AirbridgePostCommandFunction;

//////////////////////////////////////////////////////////////////////////
// IAirbridgeWebInterface

class IAirbridgeWebInterface
{
public:
	virtual ~IAirbridgeWebInterface() = default;
	
	virtual const FString GetScript() = 0;
	virtual void Handle(const FString& Message) = 0;
};

//////////////////////////////////////////////////////////////////////////
// AirbridgeWebInterfaceDefault

class AirbridgeWebInterfaceDefault : public IAirbridgeWebInterface
{
public:
	virtual const FString GetScript() override;
	virtual void Handle(const FString& Message) override;
};

//////////////////////////////////////////////////////////////////////////
// AirbridgeWebInterfaceImpl

class AirbridgeWebInterfaceImpl : public IAirbridgeWebInterface
{
public:
	AirbridgeWebInterfaceImpl* Init(const FString& WebToken, const AirbridgePostCommandFunction& InPostCommandFunction);

private:
	FString WebToken;
	AirbridgePostCommandFunction PostCommandFunction;

public:
	virtual const FString GetScript() override;
	virtual void Handle(const FString& Message) override;
};