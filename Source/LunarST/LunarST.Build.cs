// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LunarST : ModuleRules
{
	public LunarST(ReadOnlyTargetRules Target) : base(Target)
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
			"LunarST",
			"LunarST/Variant_Platforming",
			"LunarST/Variant_Platforming/Animation",
			"LunarST/Variant_Combat",
			"LunarST/Variant_Combat/AI",
			"LunarST/Variant_Combat/Animation",
			"LunarST/Variant_Combat/Gameplay",
			"LunarST/Variant_Combat/Interfaces",
			"LunarST/Variant_Combat/UI",
			"LunarST/Variant_SideScrolling",
			"LunarST/Variant_SideScrolling/AI",
			"LunarST/Variant_SideScrolling/Gameplay",
			"LunarST/Variant_SideScrolling/Interfaces",
			"LunarST/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
