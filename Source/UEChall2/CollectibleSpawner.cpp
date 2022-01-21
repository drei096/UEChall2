// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleSpawner.h"

#include "ObjectPool.h"

// Sets default values
ACollectibleSpawner::ACollectibleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACollectibleSpawner::BeginPlay()
{
	Super::BeginPlay();
	//access the "UObjectPool" reference and creates a pool of objects
	this->collectiblePool = this->FindComponentByClass<UObjectPool>();
	this->collectiblePool->Initialize();
}

// Called every frame
void ACollectibleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	if (this->ticks < spawnInterval)
	{
		this->ticks += DeltaTime;
	}
	//checks if the pool storage is not empty and the required existing size still complies
	else if (this->collectiblePool->HasObjectAvailable(1))
	{
		this->ticks = 0.0f;
		this->collectiblePool->RequestPoolable();

		this->spawnInterval = 1.0f;
	}
	*/
}

