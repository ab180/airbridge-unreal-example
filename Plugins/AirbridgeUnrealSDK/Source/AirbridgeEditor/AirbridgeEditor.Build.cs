// Copyright © 2023 ab180. All rights reserved.

using UnrealBuildTool;

public class AirbridgeEditor : ModuleRules
{
	public AirbridgeEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		ShadowVariableWarningLevel = WarningLevel.Off;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "EditorStyle" });
	}
}