// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FP_Cpp : ModuleRules
{
	public FP_Cpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"FP_Cpp",
			"FP_Cpp/Variant_Horror",
			"FP_Cpp/Variant_Horror/UI",
			"FP_Cpp/Variant_Shooter",
			"FP_Cpp/Variant_Shooter/AI",
			"FP_Cpp/Variant_Shooter/UI",
			"FP_Cpp/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
