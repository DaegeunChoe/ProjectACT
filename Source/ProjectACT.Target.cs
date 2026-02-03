// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectACTTarget : TargetRules
{
	public ProjectACTTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("ProjectACT");

		// Get git commit hash
		PreBuildSteps.Add("cd $(ProjectDir)");
		PreBuildSteps.Add("for /f \"tokens=*\" %%i in ('git rev-parse --short HEAD') do set COMMIT_HASH=%%i");
		PreBuildSteps.Add("echo %COMMIT_HASH%");
		PreBuildSteps.Add("echo #define COMMIT_HASH \"%COMMIT_HASH%\" > $(ProjectDir)\\Source\\ProjectACT\\git.h");
	}
}
