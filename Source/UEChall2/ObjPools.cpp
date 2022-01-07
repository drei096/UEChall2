// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjPools.h"
#include "PoolableObj.h"

ObjPools::ObjPools(int maxPoolSize, bool fixedAllocation)
{
	this->maxPoolSize = maxPoolSize;
	this->fixedAllocation = fixedAllocation;
}

ObjPools::~ObjPools()
{
}

void ObjPools::Initialize(TArray<AActor*> objs, FVector poolLocation)
{
	this->poolableLocation = poolLocation;
	int count = 0;
	for (int k = 0; k < objs.Num(); k++)
	{
		UPoolableObj* copy = nullptr;
		copy = objs[k]->FindComponentByClass<UPoolableObj>();
		for (int i = 0; i < this->maxPoolSize; i++)
		{
			this->availableObjects.Add(copy->createCopy(this));
			this->availableObjects[count++]->SetActorHiddenInGame(true);
		}
	}
}

void ObjPools::increaseMaxPoolSize(int addSize)
{
	if(!fixedAllocation)
	{
		maxPoolSize += addSize;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Fixed Allocation is set to True!"));
	}
}

bool ObjPools::HasObjectAvailable(int size)
{
	if (this->availableObjects.Num() >= size && size > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ObjPools::RequestPoolable()
{
	this->usedObjects.Add(availableObjects[0]);
	this->availableObjects.RemoveAt(0);
	//poolable now exist in the game
	this->usedObjects[usedObjects.Num() - 1]->SetActorHiddenInGame(false);
	//sets the onActivate func of the poolable
	this->onRequestGo();
}

void ObjPools::RequestPoolable(ECollectibles collect_type)
{
	for (int i = 0; i < availableObjects.Num(); i++)
	{
		UPoolableObj* objSc = Cast<UPoolableObj>(availableObjects[i]);
		if (objSc->collectible_type == collect_type)
		{
			usedObjects.Add(availableObjects[i]);
			availableObjects.RemoveAt(i);
			//poolable now exist in the game
			usedObjects[usedObjects.Num() - 1]->SetActorHiddenInGame(false);
			//sets the onActivate func of the poolable
			this->onRequestGo();
			UE_LOG(LogTemp, Warning, TEXT("Collectible is found!"));
		}
	}
}

void ObjPools::ReleasePoolable(int index)
{
	this->availableObjects.Add(usedObjects[index]);
	this->usedObjects.RemoveAt(index);
	this->availableObjects[availableObjects.Num() - 1]->SetActorHiddenInGame(true);
	//availableObjects[availableObjects.Num() - 1].transform.SetParent(this.poolableLocation);
	this->onReleaseGo();
}

void ObjPools::ReleasePoolable(AActor* go)
{
	if(usedObjects.Contains(go) || go != nullptr)
	{
		this->availableObjects.Add(go);
		this->usedObjects.Remove(go);
		this->availableObjects[availableObjects.Num() - 1]->SetActorHiddenInGame(true);
		//this->availableObjects[availableObjects.Num() - 1].transform.SetParent(this.poolableLocation);
		this->onReleaseGo();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Object doesn't exist in the list."));
	}
}

void ObjPools::onRequestGo()
{
	//Debug.LogError($"spawnLocations count: {spawnLocations.Count}");
	//int randIndex = Random.Range(0, this.spawnLocations.Count); //FMath::RandRange(0,100);
	//Debug.LogError($"random index: {randIndex}");
	//random spawn location
	//this.enemyPool.usedObjects[this.enemyPool.usedObjects.Count - 1].transform.position = this.spawnLocations[randIndex].position;
	//this.enemyPool.usedObjects[this.enemyPool.usedObjects.Count - 1].transform.SetParent(this.spawnLocations[randIndex]);
	
}

void ObjPools::onReleaseGo()
{
}
