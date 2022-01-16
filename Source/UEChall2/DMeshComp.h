// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UEChall2Character.h"
#include "DestructibleComponent.h"
#include "CollectibleSpawner.h"
#include "DMeshComp.generated.h"


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
	AUEChall2Character* Character = nullptr;
	ACollectibleSpawner* collectibleSpawner = nullptr;
	TArray<ECollectibles> collectibleOrder;
	UDestructibleComponent* DestructibleComponent = nullptr;
	
public:
	UFUNCTION()
	void OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection);
	UFUNCTION(BlueprintCallable)
	void spawnCollectible(FVector loc, AActor* parentShape);

};
