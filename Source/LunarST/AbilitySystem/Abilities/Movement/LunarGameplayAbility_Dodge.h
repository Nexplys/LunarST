#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LunarGameplayAbility_Dodge.generated.h"

class UAnimMontage;

UCLASS()

class LUNARST_API ULunarGameplayAbility_Dodge
	: public UGameplayAbility
{
	GENERATED_BODY()

public:
	ULunarGameplayAbility_Dodge();

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
	Category = "Dodge",
	meta = (ClampMin = "0.0")
)
	float DodgeDistance = 500.0f;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Dodge",
		meta = (ClampMin = "0.01")
	)
	float DodgeDuration = 0.25f;

	UPROPERTY(
	EditDefaultsOnly,
	BlueprintReadOnly,
	Category = "Dodge|Animation"
)
	TObjectPtr<UAnimMontage> DodgeMontage;

	UFUNCTION()
	void OnDodgeFinished();
};