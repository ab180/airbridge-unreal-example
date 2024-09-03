// Copyright © 2023 ab180. All rights reserved.

using UnrealBuildTool;
using System.IO;

public class AirbridgeUnreal : ModuleRules
{
	public AirbridgeUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		ShadowVariableWarningLevel = WarningLevel.Off;
		
		PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Json", });
		
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateIncludePaths.Add("AirbridgeUnreal/Private/Platforms/Android");

			PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });

			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "Airbridge_UPL_Android.xml"));
		}
		else if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			PrivateIncludePaths.Add("AirbridgeUnreal/Private/Platforms/iOS");
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"AirBridge",
					"../ThirdParty/iOS/AirBridge.embeddedframework.zip"
				)
			);
			
			PublicFrameworks.AddRange(
				new string[]
				{
					// ... add other public dependencies that you statically link with here ...
				}
			);
			
			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(PluginPath, "Airbridge_UPL_iOS.xml"));
		}
	}
}
