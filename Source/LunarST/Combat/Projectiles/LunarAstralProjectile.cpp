// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/Projectiles/LunarAstralProjectile.h"
#include "CombatDamageable.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ALunarAstralProjectile::ALunarAstralProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	InitialLifeSpan = 3.0f;

	CollisionComponent =
		CreateDefaultSubobject<USphereComponent>(
			TEXT("CollisionComponent")
		);

	SetRootComponent(CollisionComponent);

	CollisionComponent->InitSphereRadius(16.0f);
	CollisionComponent->SetCollisionEnabled(
		ECollisionEnabled::QueryAndPhysics
	);
	CollisionComponent->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionComponent->SetCollisionResponseToAllChannels(
		ECR_Ignore
	);
	CollisionComponent->SetCollisionResponseToChannel(
		ECC_WorldStatic,
		ECR_Block
	);
	CollisionComponent->SetCollisionResponseToChannel(
		ECC_WorldDynamic,
		ECR_Block
	);
	CollisionComponent->SetCollisionResponseToChannel(
		ECC_Pawn,
		ECR_Block
	);

	CollisionComponent->OnComponentHit.AddDynamic(
		this,
		&ALunarAstralProjectile::HandleProjectileHit
	);

	MeshComponent =
		CreateDefaultSubobject<UStaticMeshComponent>(
			TEXT("MeshComponent")
		);

	MeshComponent->SetupAttachment(CollisionComponent);
	MeshComponent->SetCollisionEnabled(
		ECollisionEnabled::NoCollision
	);

	ProjectileMovementComponent =
		CreateDefaultSubobject<UProjectileMovementComponent>(
			TEXT("ProjectileMovementComponent")
		);

	ProjectileMovementComponent->SetUpdatedComponent(
		CollisionComponent
	);
	ProjectileMovementComponent->InitialSpeed = 1200.0f;
	ProjectileMovementComponent->MaxSpeed = 1200.0f;
	ProjectileMovementComponent->Velocity =
		FVector::ForwardVector * 1200.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

void ALunarAstralProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* OwnerActor = GetOwner())
	{
		CollisionComponent->IgnoreActorWhenMoving(
			OwnerActor,
			true
		);
	}

	if (APawn* InstigatorPawn = GetInstigator())
	{
		CollisionComponent->IgnoreActorWhenMoving(
			InstigatorPawn,
			true
		);
	}
}

void ALunarAstralProjectile::HandleProjectileHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse,
	const FHitResult& Hit
)
{
	if (
		!OtherActor ||
		OtherActor == this ||
		OtherActor == GetOwner() ||
		OtherActor == GetInstigator()
	)
	{
		return;
	}

	if (ICombatDamageable* Damageable =
		Cast<ICombatDamageable>(OtherActor))
	{
		FVector DamageDirection =
			ProjectileMovementComponent->Velocity.GetSafeNormal();

		if (DamageDirection.IsNearlyZero())
		{
			DamageDirection = -Hit.ImpactNormal;
		}

		const FVector DamageImpulse =
			DamageDirection * KnockbackImpulse +
			FVector::UpVector * LaunchImpulse;

		AActor* DamageCauser = GetInstigator();

		if (!DamageCauser)
		{
			DamageCauser = GetOwner();
		}

		Damageable->ApplyDamage(
			Damage,
			DamageCauser ? DamageCauser : this,
			Hit.ImpactPoint,
			DamageImpulse
		);
	}

	Destroy();
}