#include "AbilitySystem/Attributes/LunarAttributeSet.h"
#include "GameplayEffectExtension.h"

ULunarAttributeSet::ULunarAttributeSet()
{
	InitMaxHealth(100.0f);
	InitHealth(100.0f);

	InitDamage(0.0f);

	InitMaxAstralEnergy(100.0f);
	InitAstralEnergy(100.0f);
}

void ULunarAttributeSet::PreAttributeChange(
	const FGameplayAttribute& Attribute,
	float& NewValue
)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(
			NewValue,
			0.0f,
			GetMaxHealth()
		);
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
	else if (Attribute == GetAstralEnergyAttribute())
	{
		NewValue = FMath::Clamp(
			NewValue,
			0.0f,
			GetMaxAstralEnergy()
		);
	}
	else if (Attribute == GetMaxAstralEnergyAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
}

void ULunarAttributeSet::PostGameplayEffectExecute(
	const FGameplayEffectModCallbackData& Data
)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute& ModifiedAttribute =
		Data.EvaluatedData.Attribute;

	if (ModifiedAttribute == GetDamageAttribute())
	{
		const float ReceivedDamage =
			FMath::Max(GetDamage(), 0.0f);

		SetDamage(0.0f);

		if (ReceivedDamage > 0.0f)
		{
			SetHealth(
				FMath::Clamp(
					GetHealth() - ReceivedDamage,
					0.0f,
					GetMaxHealth()
				)
			);
		}
	}
	else if (ModifiedAttribute == GetHealthAttribute())
	{
		SetHealth(
			FMath::Clamp(
				GetHealth(),
				0.0f,
				GetMaxHealth()
			)
		);
	}
	else if (
		ModifiedAttribute == GetAstralEnergyAttribute()
	)
	{
		SetAstralEnergy(
			FMath::Clamp(
				GetAstralEnergy(),
				0.0f,
				GetMaxAstralEnergy()
			)
		);
	}
}