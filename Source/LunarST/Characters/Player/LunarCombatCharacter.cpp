// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/LunarCombatCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/LunarAttributeSet.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystem/Tags/LunarGameplayTags.h"
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
	AbilitySystemComponent->RegisterGameplayTagEvent(
		LunarGameplayTags::
			State_Astromancy_SiderealBlade_Active,
		EGameplayTagEventType::NewOrRemoved
	).AddUObject(
		this,
		&ALunarCombatCharacter::HandleSiderealBladeStateChanged
	);

	OnSiderealBladeStateChanged(
		AbilitySystemComponent->HasMatchingGameplayTag(
			LunarGameplayTags::
				State_Astromancy_SiderealBlade_Active
		)
	);
	
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

		if (PrimarySpellAbilityClass)
		{
			const FGameplayAbilitySpec PrimarySpellAbilitySpec(
				PrimarySpellAbilityClass,
				1
			);

			AbilitySystemComponent->GiveAbility(
				PrimarySpellAbilitySpec
			);
		}

		if ( SecondarySpellAbilityClass &&
			SecondarySpellAbilityClass != PrimarySpellAbilityClass
			)
		{
			const FGameplayAbilitySpec SecondarySpellAbilitySpec(
				SecondarySpellAbilityClass,
				1
				);

			AbilitySystemComponent->GiveAbility(
				SecondarySpellAbilitySpec
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

bool ALunarCombatCharacter::TryActivatePrimarySpell()
{
	if (!AbilitySystemComponent || !PrimarySpellAbilityClass)
	{
		return false;
	}

	return AbilitySystemComponent->TryActivateAbilityByClass(
		PrimarySpellAbilityClass
	);
}

bool ALunarCombatCharacter::TryActivateSecondarySpell()
{
	if (!AbilitySystemComponent || !SecondarySpellAbilityClass)
	{
		return false;
	}

	return AbilitySystemComponent->TryActivateAbilityByClass(
		SecondarySpellAbilityClass
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

void ALunarCombatCharacter::
HandleSiderealBladeStateChanged(
	const FGameplayTag CallbackTag,
	const int32 NewCount
)
{
	OnSiderealBladeStateChanged(
		NewCount > 0
	);
}