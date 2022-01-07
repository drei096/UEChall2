// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "CustomEnums.h"

/**
 * 
 */
class UECHALL2_API ObjPools
{
public:
	ObjPools(int maxPoolSize = 20, bool fixedAllocation = true);
	~ObjPools();
	
    //max size of the pool and if its size isDynamic
    int maxPoolSize = 20; //default
    bool fixedAllocation = true; //default
	FVector poolableLocation;

    //collection of the available and used objects currently in the game
    TArray<AActor*> availableObjects;
    TArray<AActor*> usedObjects;
	void Initialize(TArray <AActor*> objs, FVector poolableLocation);
	void increaseMaxPoolSize(int addSize);
	bool HasObjectAvailable(int size);
	void RequestPoolable();
	void RequestPoolable(ECollectibles collect_type);
	void ReleasePoolable(int index);
	void ReleasePoolable(AActor* go);
	//What will happen to the currentPoolObject after it was spawn in the world?
	void onRequestGo();
    //What will happen to the currentPoolObject after it was release in the world?
    void onReleaseGo();
};
