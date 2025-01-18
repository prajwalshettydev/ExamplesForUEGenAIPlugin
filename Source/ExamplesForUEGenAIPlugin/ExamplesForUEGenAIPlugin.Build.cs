// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ExamplesForUEGenAIPlugin : ModuleRules
{
	public ExamplesForUEGenAIPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "GenerativeAISupport" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
