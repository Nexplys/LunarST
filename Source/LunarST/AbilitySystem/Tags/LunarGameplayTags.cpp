#include "AbilitySystem/Tags/LunarGameplayTags.h"

namespace LunarGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		Input_Dodge,
		"Input.Dodge",
		"Input used to trigger the directional dodge."
	);

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		Ability_Movement_Dodge,
		"Ability.Movement.Dodge",
		"Identifies the directional dodge ability."
	);

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		State_Movement_Dodging,
		"State.Movement.Dodging",
		"Applied while the character is dodging."
	);

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		Cooldown_Movement_Dodge,
		"Cooldown.Movement.Dodge",
		"Prevents the dodge ability from being activated repeatedly."
	);

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		State_Combat_Invulnerable,
		"State.Combat.Invulnerable",
		"Prevents the character from receiving damage."
	);

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		Input_PrimarySpell,
		"Input.PrimarySpell",
		"Input used to cast the currently equipped primary spell."
	);

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		Input_SecondarySpell,
		"Input.SecondarySpell",
		"Input used to cast the currently equipped secondary spell."
	);

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		Ability_Astromancy_AstralBolt,
		"Ability.Astromancy.AstralBolt",
		"Identifies the basic astral bolt ability."
	);

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		Cooldown_Astromancy_AstralBolt,
		"Cooldown.Astromancy.AstralBolt",
		"Prevents the astral bolt from being cast repeatedly."
	);

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		Ability_Astromancy_SiderealBlade,
		"Ability.Astromancy.SiderealBlade",
		"Identifies the basic sidereal blade ability."
	);

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		State_Astromancy_SiderealBlade_Active,
		"State.Astromancy.SiderealBlade.Active",
		"Allows the player to attack with their sidereal blade."
	);

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		Cooldown_Astromancy_SiderealBlade_Attack,
		"Cooldown.Astromancy.SiderealBlade.Attack",
		"Prevents the sidereal blade from being used repeatedly."
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		Event_Astromancy_SiderealBlade_Hit,
		"Event.Astromancy.SiderealBlade.Hit",
		"Identifies the moment the sidereal blade could hit an enemy."
	);
	
}
