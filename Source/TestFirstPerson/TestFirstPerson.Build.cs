// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestFirstPerson : ModuleRules
{
	public TestFirstPerson(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", 
			"Slate", "SlateCore", "HeadMountedDisplay" });
	}
}
