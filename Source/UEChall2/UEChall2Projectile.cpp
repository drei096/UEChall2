// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEChall2Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AUEChall2Projectile::AUEChall2Projectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AUEChall2Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;


	radForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	radForceComp->ForceStrength = 0.0f;
	radForceComp->ImpulseStrength = 0.0f;
	radForceComp->DestructibleDamage = 100.0f;

	// Die after 3 seconds by default
	//InitialLifeSpan = 3.0f;
}

void AUEChall2Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics() && radForceComp != nullptr)
	{
		radForceComp->FireImpulse();

		UE_LOG(LogTemp, Warning, TEXT("SPEED: %.2f, %.2f"), GetVelocity().X, GetVelocity().Y);
		OtherComp->AddImpulseAtLocation(GetVelocity(), Hit.ImpactPoint);
		//OtherComp->AddForceAtLocation(GetVelocity() * 100000.0f , GetActorLocation());


		//Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MISSING COMPONENT DETECTED"));
	}
}