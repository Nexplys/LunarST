// Fill out your copyright notice in the Description page of Project Settings.

#include "LunarGameplayAbility_AstralBolt.h"
#include "LunarGameplayTags.h"
#include "LunarAstralProjectile.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"

ULunarGameplayAbility_AstralBolt::ULunarGameplayAbility_AstralBolt()
{
	InstancingPolicy =
		EGameplayAbilityInstancingPolicy::InstancedPerActor;

	NetExecutionPolicy =
		EGameplayAbilityNetExecutionPolicy::LocalPredicted;

	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(
		LunarGameplayTags::Ability_Astromancy_AstralBolt
	);

	SetAssetTags(AssetTags);
}

void ULunarGameplayAbility_AstralBolt::ActivateAbility(
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

	ACharacter* Character = Cast<ACharacter>(
		ActorInfo ? ActorInfo->AvatarActor.Get() : nullptr
	);

	if (!Character || !ProjectileClass)
	{
		EndAbility(
			Handle,
			ActorInfo,
			ActivationInfo,
			true,
			true
		);

		return;
	}

	UWorld* World = Character->GetWorld();

	if (!World)
	{
		EndAbility(
			Handle,
			ActorInfo,
			ActivationInfo,
			true,
			true
		);

		return;
	}

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(
			Handle,
			ActorInfo,
			ActivationInfo,
			true,
			true
		);

		return;
	}

	FVector CastDirection =
		Character->GetLastMovementInputVector();

	if (CastDirection.IsNearlyZero())
	{
		CastDirection =
			Character->GetPendingMovementInputVector();
	}

	if (CastDirection.IsNearlyZero())
	{
		CastDirection =
			Character->GetActorForwardVector();
	}

	CastDirection.Z = 0.0f;

	if (!CastDirection.Normalize())
	{
		CastDirection = FVector::ForwardVector;
	}

	const FVector SpawnLocation =
		Character->GetActorLocation() +
		FVector::UpVector * SpawnHeightOffset +
		CastDirection * SpawnForwardOffset;

	const FRotator SpawnRotation =
		CastDirection.Rotation();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Character;
	SpawnParameters.Instigator = Character;
	SpawnParameters.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::
		AdjustIfPossibleButAlwaysSpawn;

	ALunarAstralProjectile* Projectile =
		World->SpawnActor<ALunarAstralProjectile>(
			ProjectileClass,
			SpawnLocation,
			SpawnRotation,
			SpawnParameters
		);

	if (!Projectile)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Astral Bolt projectile could not be spawned.")
		);

		EndAbility(
			Handle,
			ActorInfo,
			ActivationInfo,
			true,
			true
		);

		return;
	}

	EndAbility(
		Handle,
		ActorInfo,
		ActivationInfo,
		false,
		false
	);
}