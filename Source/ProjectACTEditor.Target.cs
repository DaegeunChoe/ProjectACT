// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectACTEditorTarget : TargetRules
{
	public ProjectACTEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("ProjectACT");

		// Get git hash
		PreBuildSteps.Add("cd $(ProjectDir)");
		PreBuildSteps.Add("for /f \"tokens=*\" %%i in ('git rev-parse --short HEAD') do set COMMIT_HASH=%%i");
		PreBuildSteps.Add("echo %COMMIT_HASH%");
		PreBuildSteps.Add("echo #define COMMIT_HASH \"%COMMIT_HASH%\" > $(ProjectDir)\\Source\\ProjectACT\\git.h");
	}
}
