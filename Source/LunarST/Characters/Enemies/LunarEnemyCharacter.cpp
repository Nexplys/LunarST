#include "Characters/Enemies/LunarEnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/LunarAttributeSet.h"
#include "GameplayEffectTypes.h"

ALunarEnemyCharacter::ALunarEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent =
		CreateDefaultSubobject<UAbilitySystemComponent>(
			TEXT("AbilitySystemComponent")
		);

	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(
		EGameplayEffectReplicationMode::Full
	);

	AttributeSet =
		CreateDefaultSubobject<ULunarAttributeSet>(
			TEXT("AttributeSet")
		);
}

void ALunarEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(
		this,
		this
	);

	AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(
			ULunarAttributeSet::GetHealthAttribute()
		)
		.AddUObject(
			this,
			&ALunarEnemyCharacter::HandleHealthChanged
		);

	OnHealthChanged(
		AttributeSet->GetHealth(),
		AttributeSet->GetHealth(),
		AttributeSet->GetMaxHealth()
	);
}

UAbilitySystemComponent*
ALunarEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

const ULunarAttributeSet*
ALunarEnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

bool ALunarEnemyCharacter::IsDead() const
{
	return bIsDead;
}

void ALunarEnemyCharacter::HandleHealthChanged(
	const FOnAttributeChangeData& Data
)
{
	OnHealthChanged(
		Data.OldValue,
		Data.NewValue,
		AttributeSet->GetMaxHealth()
	);

	if (!bIsDead && Data.NewValue <= 0.0f)
	{
		bIsDead = true;

		AbilitySystemComponent->CancelAllAbilities();

		OnDeath();
	}
}
