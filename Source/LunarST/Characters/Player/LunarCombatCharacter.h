// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Variant_Combat/CombatCharacter.h"
#include "AbilitySystemInterface.h"
#include "LunarCombatCharacter.generated.h"

class UAbilitySystemComponent;
class ULunarAttributeSet;
class UGameplayAbility;

UCLASS()
class LUNARST_API ALunarCombatCharacter : public ACombatCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ALunarCombatCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	const ULunarAttributeSet* GetAttributeSet() const;
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool TryActivatePrimarySpell();
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool TryActivateSecondarySpell();
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool TryActivateDodge();
	virtual float TakeDamage(
		float DamageAmount,
		const FDamageEvent& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Abilities"
	)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Abilities"
	)
	TObjectPtr<ULunarAttributeSet> AttributeSet;
	
	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Abilities|Startup"
	)
	TSubclassOf<UGameplayAbility> DodgeAbilityClass;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Abilities|Startup"
	)
	TSubclassOf<UGameplayAbility> PrimarySpellAbilityClass;
	
	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Abilities|Startup"
	)
	TSubclassOf<UGameplayAbility> SecondarySpellAbilityClass;

	void HandleSiderealBladeStateChanged(
	const FGameplayTag CallbackTag,
	int32 NewCount
);

	UFUNCTION(
		BlueprintImplementableEvent,
		Category = "Astromancy|Sidereal Blade"
	)
	void OnSiderealBladeStateChanged(
		bool bIsActive
	);
	
};