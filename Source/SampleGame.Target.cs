// Copyright © 2023 ab180. All rights reserved.

using UnrealBuildTool;

public class SampleGameTarget : TargetRules
{
	public SampleGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new string[] { "SampleGame" });

		if (Target.Platform == UnrealTargetPlatform.Mac ||
		    Target.Platform == UnrealTargetPlatform.IOS)
		{
			bOverrideBuildEnvironment = true;

			string additionalCompilerArguments =
				" -Wno-bitwise-instead-of-logical" +
				" -Wno-unused-but-set-variable" +
				" -Wno-deprecated-builtins" +
				" -Wno-bitfield-constant-conversion" +
				" -Wno-unknown-warning-option";

			if (Target.Platform == UnrealTargetPlatform.IOS)
			{
				additionalCompilerArguments +=
					" -Wno-objc-property-no-attribute" +
					" -Wno-nullability-completeness";
			}

			AdditionalCompilerArguments = additionalCompilerArguments;
		}
	}
}