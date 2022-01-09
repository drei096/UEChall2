// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "engine/StaticMeshActor.h"
#include "CustomEnums.h"
#include "ActorPoolable.generated.h"

UCLASS()
class UECHALL2_API AActorPoolable : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorPoolable();
	virtual void OnInitialize(); //initializes the property of this object.
	virtual void OnRelease(); //throw this event when this object has been released back to the pool.
	virtual void OnActive(); //throws this event when this object has been activated from the pool.

	void SetIndex(int i);
	int GetIndex();
	ECollectibles collectibleType = ECollectibles::NONE;
	AActor* parentShape = nullptr;

private:
	int index = -1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
