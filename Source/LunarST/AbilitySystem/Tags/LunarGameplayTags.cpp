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
		Ability_Astromancy_AstralBolt,
		"Ability.Astromancy.AstralBolt",
		"Identifies the basic astral bolt ability."
	);

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		Cooldown_Astromancy_AstralBolt,
		"Cooldown.Astromancy.AstralBolt",
		"Prevents the astral bolt from being cast repeatedly."
	);
}
