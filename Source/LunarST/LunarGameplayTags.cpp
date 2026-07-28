#include "LunarGameplayTags.h"

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
}
