#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LunarGameplayAbility_SiderealBlade.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UCLASS()
class LUNARST_API ULunarGameplayAbility_SiderealBlade
	: public UGameplayAbility
{
	GENERATED_BODY()

public:
	ULunarGameplayAbility_SiderealBlade();

protected:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;

	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled
	) override;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Sidereal Blade|Effects"
	)
	TSubclassOf<UGameplayEffect> ConjurationCostEffectClass;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Sidereal Blade|Attack",
		meta = (ClampMin = "0.0")
	)
	float AttackRange = 160.0f;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Sidereal Blade|Attack",
		meta = (ClampMin = "0.0")
	)
	float AttackRadius = 70.0f;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Sidereal Blade|Attack"
	)
	float AttackHeightOffset = 50.0f;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Sidereal Blade|Attack"
	)
	float AttackStartOffset = 40.0f;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Sidereal Blade|Debug"
	)
	bool bDrawDebugAttack = true;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Sidereal Blade|Attack",
		meta = (ClampMin = "0.01")
	)
	float AttackHitDelay = 0.20f;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Sidereal Blade|Effects"
	)
	TSubclassOf<UGameplayEffect> BladeStateEffectClass;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Sidereal Blade|Effects"
	)
	TSubclassOf<UGameplayEffect> AttackCooldownEffectClass;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Sidereal Blade|Effects"
	)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Sidereal Blade|Cost",
		meta = (ClampMin = "0.0")
	)
	float ConjurationEnergyCost = 20.0f;

	UFUNCTION(
		BlueprintImplementableEvent,
		Category = "Sidereal Blade"
	)
	void OnBladeConjured();

	UFUNCTION(
		BlueprintImplementableEvent,
		Category = "Sidereal Blade"
	)
	void OnBladeAttackRequested(
		bool bWasJustConjured
	);

private:
	void HandleBladeHitTimer();

	FTimerHandle BladeHitTimerHandle;

	bool bBladeHitProcessed = false;

	void PerformBladeAttack(
		const FGameplayAbilityActorInfo* ActorInfo
	) const;

	bool ApplyConfiguredEffectToSelf(
		UAbilitySystemComponent* AbilitySystemComponent,
		TSubclassOf<UGameplayEffect> EffectClass
	) const;

	void CancelAbilityActivation(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo
	);
};