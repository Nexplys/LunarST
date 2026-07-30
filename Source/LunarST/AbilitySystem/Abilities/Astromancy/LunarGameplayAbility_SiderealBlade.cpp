#include "AbilitySystem/Abilities/Astromancy/LunarGameplayAbility_SiderealBlade.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystem/Attributes/LunarAttributeSet.h"
#include "AbilitySystem/Tags/LunarGameplayTags.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "TimerManager.h"

ULunarGameplayAbility_SiderealBlade::
ULunarGameplayAbility_SiderealBlade()
{
	InstancingPolicy =
		EGameplayAbilityInstancingPolicy::InstancedPerActor;

	NetExecutionPolicy =
		EGameplayAbilityNetExecutionPolicy::LocalPredicted;

	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(
		LunarGameplayTags::
		Ability_Astromancy_SiderealBlade
	);

	SetAssetTags(AssetTags);
}

void ULunarGameplayAbility_SiderealBlade::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData
)
{
	Super::ActivateAbility(
		Handle,
		ActorInfo,
		ActivationInfo,
		TriggerEventData
	);

	UAbilitySystemComponent* AbilitySystemComponent =
		ActorInfo
			? ActorInfo->AbilitySystemComponent.Get()
			: nullptr;

	if (!AbilitySystemComponent)
	{
		CancelAbilityActivation(
			Handle,
			ActorInfo,
			ActivationInfo
		);

		return;
	}

	if (
		AbilitySystemComponent->HasMatchingGameplayTag(
			LunarGameplayTags::
			Cooldown_Astromancy_SiderealBlade_Attack
		)
	)
	{
		CancelAbilityActivation(
			Handle,
			ActorInfo,
			ActivationInfo
		);

		return;
	}

	const bool bBladeAlreadyActive =
		AbilitySystemComponent->HasMatchingGameplayTag(
			LunarGameplayTags::
			State_Astromancy_SiderealBlade_Active
		);

	bool bWasJustConjured = false;

	if (!bBladeAlreadyActive)
	{
		if (
			!ConjurationCostEffectClass ||
			!BladeStateEffectClass
		)
		{
			UE_LOG(
				LogTemp,
				Warning,
				TEXT(
					"Sidereal Blade is missing its "
					"cost or state Gameplay Effect."
				)
			);

			CancelAbilityActivation(
				Handle,
				ActorInfo,
				ActivationInfo
			);

			return;
		}

		const float CurrentAstralEnergy =
			AbilitySystemComponent->GetNumericAttribute(
				ULunarAttributeSet::
				GetAstralEnergyAttribute()
			);

		if (CurrentAstralEnergy < ConjurationEnergyCost)
		{
			CancelAbilityActivation(
				Handle,
				ActorInfo,
				ActivationInfo
			);

			return;
		}

		if (
			!ApplyConfiguredEffectToSelf(
				AbilitySystemComponent,
				ConjurationCostEffectClass
			)
		)
		{
			CancelAbilityActivation(
				Handle,
				ActorInfo,
				ActivationInfo
			);

			return;
		}

		if (
			!ApplyConfiguredEffectToSelf(
				AbilitySystemComponent,
				BladeStateEffectClass
			)
		)
		{
			CancelAbilityActivation(
				Handle,
				ActorInfo,
				ActivationInfo
			);

			return;
		}

		bWasJustConjured = true;

		OnBladeConjured();
	}

	if (!AttackCooldownEffectClass)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT(
				"Sidereal Blade is missing its "
				"attack cooldown Gameplay Effect."
			)
		);

		CancelAbilityActivation(
			Handle,
			ActorInfo,
			ActivationInfo
		);

		return;
	}

	if (!DamageEffectClass)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT(
				"Sidereal Blade is missing its "
				"damage Gameplay Effect."
			)
		);

		CancelAbilityActivation(
			Handle,
			ActorInfo,
			ActivationInfo
		);

		return;
	}

	if (
		!ApplyConfiguredEffectToSelf(
			AbilitySystemComponent,
			AttackCooldownEffectClass
		)
	)
	{
		CancelAbilityActivation(
			Handle,
			ActorInfo,
			ActivationInfo
		);

		return;
	}

	bBladeHitProcessed = false;

	UWorld* World =
		ActorInfo && ActorInfo->AvatarActor.IsValid()
			? ActorInfo->AvatarActor->GetWorld()
			: nullptr;

	if (!World)
	{
		CancelAbilityActivation(
			Handle,
			ActorInfo,
			ActivationInfo
		);

		return;
	}

	World->GetTimerManager().SetTimer(
		BladeHitTimerHandle,
		this,
		&ULunarGameplayAbility_SiderealBlade::
			HandleBladeHitTimer,
		FMath::Max(AttackHitDelay, 0.01f),
		false
	);

	OnBladeAttackRequested(
		bWasJustConjured
	);
}

void ULunarGameplayAbility_SiderealBlade::
HandleBladeHitTimer()
{
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Sidereal Blade timed hit.")
	);

	if (bBladeHitProcessed)
	{
		return;
	}

	bBladeHitProcessed = true;

	PerformBladeAttack(
		CurrentActorInfo
	);

	EndAbility(
		CurrentSpecHandle,
		CurrentActorInfo,
		CurrentActivationInfo,
		false,
		false
	);
}

void ULunarGameplayAbility_SiderealBlade::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled
)
{
	UWorld* World =
		ActorInfo && ActorInfo->AvatarActor.IsValid()
			? ActorInfo->AvatarActor->GetWorld()
			: nullptr;

	if (World)
	{
		World->GetTimerManager().ClearTimer(
			BladeHitTimerHandle
		);
	}

	Super::EndAbility(
		Handle,
		ActorInfo,
		ActivationInfo,
		bReplicateEndAbility,
		bWasCancelled
	);
}

void ULunarGameplayAbility_SiderealBlade::
PerformBladeAttack(
	const FGameplayAbilityActorInfo* ActorInfo
) const
{
	ACharacter* Character = Cast<ACharacter>(
		ActorInfo
			? ActorInfo->AvatarActor.Get()
			: nullptr
	);

	UAbilitySystemComponent* SourceAbilitySystem =
		ActorInfo
			? ActorInfo->AbilitySystemComponent.Get()
			: nullptr;

	if (
		!Character ||
		!SourceAbilitySystem ||
		!DamageEffectClass
	)
	{
		return;
	}

	UWorld* World = Character->GetWorld();

	if (!World)
	{
		return;
	}

	FVector AttackDirection =
		Character->GetLastMovementInputVector();

	if (AttackDirection.IsNearlyZero())
	{
		AttackDirection =
			Character->GetPendingMovementInputVector();
	}

	if (AttackDirection.IsNearlyZero())
	{
		AttackDirection =
			Character->GetActorForwardVector();
	}

	AttackDirection.Z = 0.0f;

	if (!AttackDirection.Normalize())
	{
		AttackDirection = FVector::ForwardVector;
	}

	const FVector AttackStart =
		Character->GetActorLocation() +
		FVector::UpVector * AttackHeightOffset +
		AttackDirection * AttackStartOffset;

	const FVector AttackEnd =
		AttackStart +
		AttackDirection * AttackRange;

	FCollisionQueryParams QueryParameters(
		SCENE_QUERY_STAT(SiderealBladeAttack),
		false,
		Character
	);

	QueryParameters.AddIgnoredActor(Character);

	FCollisionObjectQueryParams ObjectQueryParameters;
	ObjectQueryParameters.AddObjectTypesToQuery(
		ECC_Pawn
	);

	TArray<FHitResult> HitResults;

	const bool bSweepHit =
		World->SweepMultiByObjectType(
			HitResults,
			AttackStart,
			AttackEnd,
			FQuat::Identity,
			ObjectQueryParameters,
			FCollisionShape::MakeSphere(
				AttackRadius
			),
			QueryParameters
		);

	TSet<AActor*> DamagedActors;

	for (const FHitResult& HitResult : HitResults)
	{
		AActor* HitActor = HitResult.GetActor();

		if (
			!HitActor ||
			HitActor == Character ||
			DamagedActors.Contains(HitActor)
		)
		{
			continue;
		}

		UAbilitySystemComponent* TargetAbilitySystem =
			UAbilitySystemGlobals::
			GetAbilitySystemComponentFromActor(
				HitActor
			);

		if (!TargetAbilitySystem)
		{
			continue;
		}

		FGameplayEffectContextHandle EffectContext =
			SourceAbilitySystem->MakeEffectContext();

		EffectContext.AddSourceObject(this);
		EffectContext.AddHitResult(HitResult);

		FGameplayEffectSpecHandle EffectSpec =
			SourceAbilitySystem->MakeOutgoingSpec(
				DamageEffectClass,
				1.0f,
				EffectContext
			);

		if (!EffectSpec.IsValid())
		{
			continue;
		}

		SourceAbilitySystem
			->ApplyGameplayEffectSpecToTarget(
				*EffectSpec.Data.Get(),
				TargetAbilitySystem
			);

		DamagedActors.Add(HitActor);
	}

	if (bDrawDebugAttack)
	{
		const FColor DebugColor =
			bSweepHit
				? FColor::Green
				: FColor::Red;

		DrawDebugLine(
			World,
			AttackStart,
			AttackEnd,
			DebugColor,
			false,
			1.0f,
			0,
			2.0f
		);

		DrawDebugSphere(
			World,
			AttackStart,
			AttackRadius,
			16,
			DebugColor,
			false,
			1.0f
		);

		DrawDebugSphere(
			World,
			AttackEnd,
			AttackRadius,
			16,
			DebugColor,
			false,
			1.0f
		);
	}
}

bool ULunarGameplayAbility_SiderealBlade::
ApplyConfiguredEffectToSelf(
	UAbilitySystemComponent* AbilitySystemComponent,
	TSubclassOf<UGameplayEffect> EffectClass
) const
{
	if (
		!AbilitySystemComponent ||
		!EffectClass
	)
	{
		return false;
	}

	FGameplayEffectContextHandle EffectContext =
		AbilitySystemComponent->MakeEffectContext();

	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle EffectSpec =
		AbilitySystemComponent->MakeOutgoingSpec(
			EffectClass,
			1.0f,
			EffectContext
		);

	if (!EffectSpec.IsValid())
	{
		return false;
	}

	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(
		*EffectSpec.Data.Get()
	);

	return true;
}

void ULunarGameplayAbility_SiderealBlade::
CancelAbilityActivation(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo
)
{
	EndAbility(
		Handle,
		ActorInfo,
		ActivationInfo,
		true,
		true
	);
}