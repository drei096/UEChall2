// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEChall2Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

void AUEChall2Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

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

	/*
	radForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	radForceComp->SetMobility(EComponentMobility::Movable);
	radForceComp->SetupAttachment(RootComponent);
	radForceComp->ForceStrength = 100000.0f;
	radForceComp->ImpulseStrength = 100000.0f;
	radForceComp->DestructibleDamage = 100000.0f;
	*/

	// Die after 3 seconds by default
	//InitialLifeSpan = 3.0f;
}

void AUEChall2Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	radForceComp = this->FindComponentByClass<URadialForceComponent>();
	radForceComp->FireImpulse();

	// Only add impulse and destroy projectile if we hit a physics
	if (OtherComp->IsSimulatingPhysics())
	{


		//radForceComp->FireImpulse();

		//UE_LOG(LogTemp, Warning, TEXT("SPEED: %.2f, %.2f"), radForceComp);
		//UE_LOG(LogTemp, Warning, TEXT("NAME HIT: %s"), *OtherActor->GetName());

		//OtherComp->AddImpulse(GetVelocity().GetAbs() * 50.0f);
		//OtherComp->AddForce(GetVelocity().GetAbs() * 5000.0f);
		//OtherComp->AddForceAtLocation(GetVelocity() * 100000.0f , GetActorLocation());

		OtherComp->AddImpulseAtLocation(GetVelocity(), GetActorLocation(), NAME_None);
		//OtherComp->AddRadialImpulse(GetActorLocation(), 2000, 500000.0, ERadialImpulseFalloff::RIF_Linear, false);
		//OtherComp->AddRadialForce(GetActorLocation(), 2000, 100000.0, ERadialImpulseFalloff::RIF_Linear, false);



		UE_LOG(LogTemp, Warning, TEXT("IS HIT!!!!"));
		//Destroy();
	}

}

void AUEChall2Projectile::spawnCollectible()
{
	//Spawn random collectibles here
}
