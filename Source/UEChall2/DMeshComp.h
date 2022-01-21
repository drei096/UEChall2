// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UEChall2Character.h"
#include "DestructibleComponent.h"
#include "CollectibleSpawner.h"
#include "DMeshComp.generated.h"

//This actor component should be included in every destructible mesh
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UECHALL2_API UDMeshComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDMeshComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	//reference for the FPS character in our level
	AUEChall2Character* Character = nullptr;
	//reference for the main CollectibleSpawner class in our level
	ACollectibleSpawner* collectibleSpawner = nullptr;
	//creates an order list of the collectibles; use for choosing a randomize spawn of collectible
	TArray<ECollectibles> collectibleOrder;
	//reference of the actor's destructible component
	UDestructibleComponent* DestructibleComponent = nullptr;
	
public:
	//this function gets called when the actor mesh gets fractured for the first time
	UFUNCTION()
	void OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection);
	//this is a composition function where it executes when the "OnComponentFracture" gets called
	UFUNCTION(BlueprintCallable)
	void spawnCollectible(FVector loc, AActor* parentShape);

};
