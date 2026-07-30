#pragma once

#include "NativeGameplayTags.h"

namespace LunarGameplayTags
{
	LUNARST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Dodge);

	LUNARST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Ability_Movement_Dodge
	);

	LUNARST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		State_Movement_Dodging
	);

	LUNARST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Cooldown_Movement_Dodge
	);

	LUNARST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		State_Combat_Invulnerable
	);

	LUNARST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Input_PrimarySpell
	);

	LUNARST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Input_SecondarySpell
	);

	LUNARST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Ability_Astromancy_AstralBolt
	);

	LUNARST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Cooldown_Astromancy_AstralBolt
	);

	LUNARST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Ability_Astromancy_SiderealBlade
	);

	LUNARST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		State_Astromancy_SiderealBlade_Active
	);

	LUNARST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Cooldown_Astromancy_SiderealBlade_Attack
	);

	LUNARST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(
		Event_Astromancy_SiderealBlade_Hit
	);
	
}
