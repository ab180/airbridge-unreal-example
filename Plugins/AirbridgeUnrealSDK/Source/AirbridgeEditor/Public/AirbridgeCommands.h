// Copyright © 2023 ab180. All rights reserved.

#pragma once

class FAirbridgeCommands : public TCommands<FAirbridgeCommands>
{
public:
	FAirbridgeCommands();
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> AirbridgeCommand;
};