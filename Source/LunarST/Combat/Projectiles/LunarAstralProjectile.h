// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LunarAstralProjectile.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class UPrimitiveComponent;

UCLASS()
class LUNARST_API ALunarAstralProjectile : public AActor
{
	GENERATED_BODY()

public:
	ALunarAstralProjectile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Projectile|Components"
	)
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Projectile|Components"
	)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Projectile|Components"
	)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Projectile|Damage",
		meta = (ClampMin = "0.0")
	)
	float Damage = 1.0f;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Projectile|Damage",
		meta = (ClampMin = "0.0")
	)
	float KnockbackImpulse = 250.0f;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Projectile|Damage",
		meta = (ClampMin = "0.0")
	)
	float LaunchImpulse = 100.0f;

	UFUNCTION()
	void HandleProjectileHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse,
		const FHitResult& Hit
	);
};
