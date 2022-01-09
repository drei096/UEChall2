// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomEnums.h"
#include "ObjectPool.generated.h"


class AActorPoolable;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UECHALL2_API UObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPool();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Initialize();
	bool HasObjectAvailable(int requestSize);
	int GetMaxPoolSize();
	AActorPoolable* RequestPoolable(FVector loc);
	AActorPoolable* RequestPoolable(ECollectibles collectType, FVector loc, AActor* parentShape);
	TArray<AActorPoolable*> RequestPoolabeBatch(int size);

	void ReleasePoolable(AActorPoolable* poolableObject);
	void ReleasePoolableBatch(TArray<AActorPoolable*> List);
	void ReleasePoolableBatch(int count);

public:
	UPROPERTY(EditAnywhere) int maxPoolSize = 20;

	UPROPERTY(EditAnywhere) TArray <AActorPoolable*> actorCopies;
	UPROPERTY(EditAnywhere) TArray <ECollectibles> spawnOrder;
	UPROPERTY(EditAnywhere) AActor* parent = nullptr;

	TArray<AActorPoolable*> availableObjects;
	TArray<AActorPoolable*> usedObjects;
		
};
