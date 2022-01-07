// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectibleSpawner.generated.h"

class UObjectPool;
UCLASS()
class UECHALL2_API ACollectibleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectibleSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UObjectPool* collectiblePool;
private:
	float ticks = 0.0f;
	float spawnInterval = 1.0f;
};
