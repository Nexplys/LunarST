// Fill out your copyright notice in the Description page of Project Settings.


#include "LunarCombatCharacter.h"
#include "AbilitySystemComponent.h"
#include "LunarAttributeSet.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilitySpec.h"
#include "LunarGameplayTags.h"
#include "Engine/DamageEvents.h"

ALunarCombatCharacter::ALunarCombatCharacter()
{
	AbilitySystemComponent =
		CreateDefaultSubobject<UAbilitySystemComponent>(
			TEXT("AbilitySystemComponent")
		);

	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(
		EGameplayEffectReplicationMode::Full
	);

	AttributeSet = CreateDefaultSubobject<ULunarAttributeSet>(
	TEXT("AttributeSet")
	);
}

void ALunarCombatCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	if (HasAuthority())
	{
		if (DodgeAbilityClass)
		{
			const FGameplayAbilitySpec DodgeAbilitySpec(
				DodgeAbilityClass,
				1
			);

			AbilitySystemComponent->GiveAbility(
				DodgeAbilitySpec
			);
		}

		if (AstralBoltAbilityClass)
		{
			const FGameplayAbilitySpec AstralBoltAbilitySpec(
				AstralBoltAbilityClass,
				1
			);

			AbilitySystemComponent->GiveAbility(
				AstralBoltAbilitySpec
			);
		}
	}
}

UAbilitySystemComponent*
ALunarCombatCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

const ULunarAttributeSet*
ALunarCombatCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

bool ALunarCombatCharacter::TryActivateDodge()
{
	if (!AbilitySystemComponent || !DodgeAbilityClass)
	{
		return false;
	}

	return AbilitySystemComponent->TryActivateAbilityByClass(
		DodgeAbilityClass
	);
}

bool ALunarCombatCharacter::TryActivateAstralBolt()
{
	if (!AbilitySystemComponent || !AstralBoltAbilityClass)
	{
		return false;
	}

	return AbilitySystemComponent->TryActivateAbilityByClass(
		AstralBoltAbilityClass
	);
}

float ALunarCombatCharacter::TakeDamage(
	float DamageAmount,
	const FDamageEvent& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser
)
{
	if (
		AbilitySystemComponent &&
		AbilitySystemComponent->HasMatchingGameplayTag(
			LunarGameplayTags::State_Combat_Invulnerable
		)
	)
	{
		return 0.0f;
	}

	return Super::TakeDamage(
		DamageAmount,
		DamageEvent,
		EventInstigator,
		DamageCauser
	);
}