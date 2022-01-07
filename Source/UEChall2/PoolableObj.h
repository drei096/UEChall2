// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjPools.h"
#include "Components/ActorComponent.h"
#include "CustomEnums.h"
#include "PoolableObj.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UECHALL2_API UPoolableObj : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPoolableObj();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void initialize();
	void onRelease();
	void onActivate();
	AActor* createCopy(ObjPools* pool);
	ObjPools* poolRef;
	UPROPERTY(EditAnywhere)
	ECollectibles collectible_type = ECollectibles::NONE;

};
