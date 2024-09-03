// Copyright © 2023 ab180. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SampleGameEditorTarget : TargetRules
{
	public SampleGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "SampleGame" } );
		
		bOverrideBuildEnvironment = true;
		AdditionalCompilerArguments =
			" -Wno-bitwise-instead-of-logical" +
			" -Wno-unused-but-set-variable" +
			" -Wno-deprecated-builtins" +
			" -Wno-bitfield-constant-conversion" +
			" -Wno-unknown-warning-option";
	}
}
