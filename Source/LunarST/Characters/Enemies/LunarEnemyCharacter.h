#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "LunarEnemyCharacter.generated.h"

class UAbilitySystemComponent;
class ULunarAttributeSet;
struct FOnAttributeChangeData;

UCLASS()
class LUNARST_API ALunarEnemyCharacter
	: public ACharacter,
	  public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ALunarEnemyCharacter();

	virtual UAbilitySystemComponent*
	GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure, Category = "Abilities")
	const ULunarAttributeSet* GetAttributeSet() const;

	UFUNCTION(BlueprintPure, Category = "Enemy")
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

	void HandleHealthChanged(
		const FOnAttributeChangeData& Data
	);

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
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Enemy"
	)
	bool bIsDead = false;

	UFUNCTION(
		BlueprintImplementableEvent,
		Category = "Enemy|Health"
	)
	void OnHealthChanged(
		float OldHealth,
		float NewHealth,
		float MaxHealth
	);

	UFUNCTION(
		BlueprintImplementableEvent,
		Category = "Enemy|Health"
	)
	void OnDeath();
};
