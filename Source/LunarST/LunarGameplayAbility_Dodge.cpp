#include "LunarGameplayAbility_Dodge.h"

#include "LunarGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"
#include "GameFramework/Character.h"
#include "GameFramework/RootMotionSource.h"

ULunarGameplayAbility_Dodge::ULunarGameplayAbility_Dodge()
{
	InstancingPolicy =
		EGameplayAbilityInstancingPolicy::InstancedPerActor;
    
    NetExecutionPolicy =
    EGameplayAbilityNetExecutionPolicy::LocalPredicted;

	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(
		LunarGameplayTags::Ability_Movement_Dodge
	);

	SetAssetTags(AssetTags);
}

void ULunarGameplayAbility_Dodge::ActivateAbility(
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

    ACharacter* Character = Cast<ACharacter>(
        ActorInfo ? ActorInfo->AvatarActor.Get() : nullptr
    );

    if (!Character || DodgeDuration <= KINDA_SMALL_NUMBER)
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

    FVector DodgeDirection =
        Character->GetLastMovementInputVector();

    if (DodgeDirection.IsNearlyZero())
    {
        DodgeDirection =
            Character->GetPendingMovementInputVector();
    }

    if (DodgeDirection.IsNearlyZero())
    {
        DodgeDirection = Character->GetActorForwardVector();
    }

    DodgeDirection.Z = 0.0f;
    DodgeDirection.Normalize();

    const float DodgeStrength =
        DodgeDistance / DodgeDuration;

    UAbilityTask_ApplyRootMotionConstantForce* DodgeTask =
        UAbilityTask_ApplyRootMotionConstantForce
        ::ApplyRootMotionConstantForce(
            this,
            TEXT("DodgeMovement"),
            DodgeDirection,
            DodgeStrength,
            DodgeDuration,
            false,
            nullptr,
            ERootMotionFinishVelocityMode::SetVelocity,
            FVector::ZeroVector,
            0.0f,
            true
        );

    if (!DodgeTask)
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

    DodgeTask->OnFinish.AddDynamic(
        this,
        &ULunarGameplayAbility_Dodge::OnDodgeFinished
    );

    DodgeTask->ReadyForActivation();
}

void ULunarGameplayAbility_Dodge::OnDodgeFinished()
{
    K2_EndAbility();
}