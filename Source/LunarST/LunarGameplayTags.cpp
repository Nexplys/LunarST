#include "LunarGameplayTags.h"
#include "C:\Users\nexpl\Desktop\Git\LunarST\Intermediate\Build\Win64\x64\LunarSTEditor\Development\UnrealEd\SharedPCH.UnrealEd.Project.ValApi.ValExpApi.Cpp20.h"

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
}
