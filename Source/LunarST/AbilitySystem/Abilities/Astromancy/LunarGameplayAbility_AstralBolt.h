// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LunarGameplayAbility_AstralBolt.generated.h"

class ALunarAstralProjectile;

UCLASS()
class LUNARST_API ULunarGameplayAbility_AstralBolt
	: public UGameplayAbility
{
	GENERATED_BODY()

public:
	ULunarGameplayAbility_AstralBolt();

protected:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Astral Bolt|Projectile"
	)
	TSubclassOf<ALunarAstralProjectile> ProjectileClass;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Astral Bolt|Projectile",
		meta = (ClampMin = "0.0")
	)
	float SpawnForwardOffset = 80.0f;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Astral Bolt|Projectile"
	)
	float SpawnHeightOffset = 50.0f;
};
