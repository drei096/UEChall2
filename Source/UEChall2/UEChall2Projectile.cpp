// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEChall2Projectile.h"

#include "CollectibleSpawner.h"
#include "ObjectPool.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

//executed after the projectile is spawned when gun is fired
void AUEChall2Projectile::BeginPlay()
{
	Super::BeginPlay();

	//gets the player controller in the level
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC != nullptr)
    {
		//assign the "AUEChall2Character" reference of our pawn
        Character =  Cast<AUEChall2Character >(PC->GetPawn());
        if (Character != nullptr)
        {
			this->collectibleSpawner = Character->collectibleSpawner;
        }
    }

	//a collectible list that will be use for getting a random spawn
	this->collectibleOrder = {ECollectibles::CAPSULE, ECollectibles::CONE, ECollectibles::CUBE, ECollectibles::CYLINDER};
	//assign an OnHit function for the static mesh when it detects a collision; USED DURING DEVELOPMENT
	this->FindComponentByClass<UStaticMeshComponent>()->OnComponentHit.AddDynamic(this, &AUEChall2Projectile::OnHit);

	//responsible for getting the static mesh component of the projectile and scaling it to the appropriate size acc to the obtained collectible
	switch (Character->projectileSizeID)
	{
	case 1:
		this->SetActorScale3D(FVector(0.05f, 0.05f, 0.05f));
		this->FindComponentByClass<UStaticMeshComponent>()->SetMassOverrideInKg(NAME_None, 500 * 2);
		break;
	case 2: 
		this->SetActorScale3D(FVector(0.15f, 0.15f, 0.15f));
		this->FindComponentByClass<UStaticMeshComponent>()->SetMassOverrideInKg(NAME_None, 500 * 1);
		break;
	case 3:
		this->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
		this->FindComponentByClass<UStaticMeshComponent>()->SetMassOverrideInKg(NAME_None, 500 * 2);
		break;
	case 4:
		this->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
		this->FindComponentByClass<UStaticMeshComponent>()->SetMassOverrideInKg(NAME_None, 500 * 3);
		break;
	default:
		break;
	}
}

AUEChall2Projectile::AUEChall2Projectile()
{
	// Use a sphere as a simple collision representation

	/*
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AUEChall2Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;
	*/

	


	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = this->FindComponentByClass<UStaticMeshComponent>();
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

//used to add functionality when the static mesh detects a collision; USED DURING DEVELOPMENT
void AUEChall2Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//CollisionComp->SetSimulatePhysics(true);
	//radForceComp = this->FindComponentByClass<URadialForceComponent>();

	if(OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_Destructible) 
	{
		//radForceComp->FireImpulse();
		DestructibleComponent = OtherActor->FindComponentByClass<UDestructibleComponent>();

		// Only add impulse and destroy projectile if we hit a physics
		if (OtherComp->IsSimulatingPhysics())
		{

			
			//radForceComp->FireImpulse();

			//UE_LOG(LogTemp, Warning, TEXT("SPEED: %.2f, %.2f"), radForceComp);
			//UE_LOG(LogTemp, Warning, TEXT("NAME HIT: %s"), *OtherActor->GetName());

			//OtherComp->AddImpulse(GetVelocity().GetAbs() * 50.0f);
			//OtherComp->AddForce(GetVelocity().GetAbs() * 5000.0f);
			//OtherComp->AddForceAtLocation(GetVelocity() * 100000.0f , GetActorLocation());

			//OtherComp->AddImpulseAtLocation(GetVelocity(), GetActorLocation(), NAME_None);

			//OtherComp->AddRadialImpulse(GetActorLocation(), 2000, 500000.0, ERadialImpulseFalloff::RIF_Linear, false);
			//OtherComp->AddRadialForce(GetActorLocation(), 2000, 100000.0, ERadialImpulseFalloff::RIF_Linear, false);

			//UE_LOG(LogTemp, Warning, TEXT("SPEED: %.2f"), GetVelocity().Size());
			
			//DestructibleComponent->OnComponentFracture.AddUniqueDynamic(this, &AUEChall2Projectile::OnComponentFracture);
			

			//spawnCollectible(OtherComp->GetOwner()->GetActorLocation(), OtherActor);

			UE_LOG(LogTemp, Warning, TEXT("IS HIT!!!!"));

			
			//Destroy();
		}
	}
	
	//this->FindComponentByClass<UStaticMeshComponent>()->SetNotifyRigidBodyCollision(false);

}

void AUEChall2Projectile::spawnCollectible(FVector loc, AActor* parentShape)
{
	this->collectibleSpawner->collectiblePool->RequestPoolable(this->collectibleOrder[FMath::RandRange(0,this->collectibleOrder.Num()-1)],loc, parentShape);
}

void AUEChall2Projectile::OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection)
{
	UE_LOG(LogTemp, Warning, TEXT("COMPONENT FRACTURE"));
}
