﻿// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SimpleFlowFacts : ModuleRules
{
	public SimpleFlowFacts(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"SimpleFacts",
				"Flow",
				"GameplayTags",
				"FilteredGameplayTags",
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
			}
		);

		if (Target.bCompileAgainstEditor)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"FlowEditor"
				}
			);
		}
	}
}
