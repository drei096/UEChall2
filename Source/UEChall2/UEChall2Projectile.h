// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "UEChall2Character.h"
#include "CustomEnums.h"
#include "DestructibleComponent.h"
#include "DrawDebugHelpers.h"
#include "UEChall2Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class ACollectibleSpawner;

UCLASS(config=Game)
class AUEChall2Projectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

protected:
	//Called when the game starts
	virtual void BeginPlay() override;

public:
	AUEChall2Projectile();
	

	/** called when projectile hits something */
	//UFUNCTION(BlueprintImplementableEvent)
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	void spawnCollectible(FVector loc, AActor* parentShape);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	/** Radial force component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Projectile, meta = (AllowPrivateAccess = "true"))
	URadialForceComponent* radForceComp = nullptr;

	URadialForceComponent* GetRadForceComponent() const { return radForceComp; }

	AUEChall2Character* Character = nullptr;

private:
	ACollectibleSpawner* collectibleSpawner = nullptr;
	TArray<ECollectibles> collectibleOrder;
	UDestructibleComponent* DestructibleComponent = nullptr;

	UFUNCTION()
	void OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection);
	
};

