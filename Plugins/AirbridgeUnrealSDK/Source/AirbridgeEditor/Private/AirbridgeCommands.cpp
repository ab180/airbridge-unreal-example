// Copyright © 2023 ab180. All rights reserved.

#include "AirbridgeCommands.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "FAirbridgeEditorModule"

FAirbridgeCommands::FAirbridgeCommands() : TCommands<FAirbridgeCommands>(
	TEXT("Airbridge SDK"),
	NSLOCTEXT("Contexts", "Airbridge SDK", "Airbridge SDK"),
	NAME_None,
	FEditorStyle::GetStyleSetName())
{
		
}

void FAirbridgeCommands::RegisterCommands()
{
	//"Open Assets or Folders", "Opens the selected assets or folders, depending on the selection",
	UI_COMMAND(
		AirbridgeCommand,
		"Airbridge Command",
		"Airbridge Command",
		EUserInterfaceActionType::Button,
		FInputChord()
	);
}

#undef LOCTEXT_NAMESPACE