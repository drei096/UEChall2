// Fill out your copyright notice in the Description page of Project Settings.


#include "DMeshComp.h"


// Sets default values for this component's properties
UDMeshComp::UDMeshComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//this->GetOwner()->FindComponentByClass<UDestructibleComponent>()
	// ...

	
	
}


// Called when the game starts
void UDMeshComp::BeginPlay()
{
	Super::BeginPlay();

	//gets the playerController in the level
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC != nullptr)
	{
		//assign the "AUEChall2Character" reference of our pawn
		Character = Cast<AUEChall2Character >(PC->GetPawn());
	}

	//a collectible list that will be use for getting a random spawn
	this->collectibleOrder = { ECollectibles::CAPSULE, ECollectibles::CONE, ECollectibles::CUBE, ECollectibles::CYLINDER };

	//assign the "UDestructibleComponent" reference from our actor's component list
	DestructibleComponent = this->GetOwner()->FindComponentByClass<UDestructibleComponent>();
	//add an event for the component; the second param is the function for when the fracture situation occurs
	DestructibleComponent->OnComponentFracture.AddUniqueDynamic(this, &UDMeshComp::OnComponentFracture);
}


void UDMeshComp::spawnCollectible(FVector loc, AActor* parentShape)
{
	//access the "RequestPoolable" function and randomnly chooses a collectibleType and place it in the location of the actor shape
	//pass in the parentShape to be used for destroying actor after the collectible were collected by the player
	this->collectibleSpawner->collectiblePool->RequestPoolable(this->collectibleOrder[FMath::RandRange(0, this->collectibleOrder.Num() - 1)], loc, parentShape);
}

void UDMeshComp::OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection)
{
	UE_LOG(LogTemp, Warning, TEXT("COMPONENT FRACTURE"));
	
	//calls when the actor DestructibleMesh had a fracture status; only called once
	spawnCollectible(this->GetOwner()->GetActorLocation(), this->GetOwner());
}

// Called every frame
void UDMeshComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//since our "collectibleSpawner" attribute that is found in our "AUEChall2Character" is assign in the levelBlueprint,
	//the assignment is done in the tickcomponent since the "LevelBlueprint" goes after the "BeginPlay" function
	if (Character != nullptr && this->collectibleSpawner == nullptr)
	{
		this->collectibleSpawner = Character->collectibleSpawner;
	}
	
}

