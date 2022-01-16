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

	// ...
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC != nullptr)
	{
		Character = Cast<AUEChall2Character >(PC->GetPawn());
	}

	this->collectibleOrder = { ECollectibles::CAPSULE, ECollectibles::CONE, ECollectibles::CUBE, ECollectibles::CYLINDER };

	DestructibleComponent = this->GetOwner()->FindComponentByClass<UDestructibleComponent>();
	DestructibleComponent->OnComponentFracture.AddUniqueDynamic(this, &UDMeshComp::OnComponentFracture);
}

void UDMeshComp::spawnCollectible(FVector loc, AActor* parentShape)
{
	this->collectibleSpawner->collectiblePool->RequestPoolable(this->collectibleOrder[FMath::RandRange(0, this->collectibleOrder.Num() - 1)], loc, parentShape);
}

void UDMeshComp::OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection)
{
	UE_LOG(LogTemp, Warning, TEXT("COMPONENT FRACTURE"));
	
	spawnCollectible(this->GetOwner()->GetActorLocation(), this->GetOwner());
}

// Called every frame
void UDMeshComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (Character != nullptr && this->collectibleSpawner == nullptr)
	{
		this->collectibleSpawner = Character->collectibleSpawner;
	}
	
}

