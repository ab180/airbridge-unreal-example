// Copyright © 2023 ab180. All rights reserved.

using System.IO;
using UnrealBuildTool;

public class SampleGame : ModuleRules
{
	public SampleGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "SlateCore",
			"AirbridgeUnreal",
			"IOSAppTrackingTransparency"
		});

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
			
			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "SampleGame_UPL.xml"));
		}
		else if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			PrivateIncludePaths.Add("SampleGame/Private/iOS");
		}
	}
}
