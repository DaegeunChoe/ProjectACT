// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectACT : ModuleRules
{
	public ProjectACT(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[]
		{
			"ProjectACT",
		});

		PublicDependencyModuleNames.AddRange(new string[] 
		{
			// Base
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",

			// Gameplay
			"GameplayTags",
            "GameplayTasks",
            "GameplayAbilities",
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
