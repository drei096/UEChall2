// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool.h"

#include "ActorPoolable.h"

// Sets default values for this component's properties
UObjectPool::UObjectPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectPool::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UObjectPool::BeginDestroy()
{
	Super::BeginDestroy(); //IMPORTANT: Any lifecycle events must have super function. Or else Unreal Engine will crash.
	for(int i = 0; i < this->availableObjects.Num(); i++)
	{
		this->availableObjects[i]->Destroy();
	}

	for(int i = 0; i < this->usedObjects.Num(); i++)
	{
		this->usedObjects[i]->Destroy();
	}

	this->availableObjects.Empty();
	this->usedObjects.Empty();
}


// Called every frame
void UObjectPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectPool::Initialize()
{
	if(this->actorCopies.Num() <= 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Actor is null. Object pool not initialized."));
		return;
	}

	//create a copies for each collectible type
	for(int x = 0; x < this->actorCopies.Num(); x++)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Template = this->actorCopies[x];
		spawnParams.Owner = this->GetOwner();
		ECollectibles collection = this->spawnOrder[x];

		const FTransform transform = this->actorCopies[x]->GetTransform();

		//create a copies of the collectible type
		for (int i = 0; i < this->maxPoolSize - 1; i++)
		{
			AActorPoolable* poolableObject = this->GetWorld()->SpawnActor<AActorPoolable>(this->actorCopies[x]->GetClass(), spawnParams);
			poolableObject->collectibleType = collection;
			poolableObject->SetIndex(i);
			poolableObject->OnInitialize();
			this->availableObjects.Push(poolableObject);
		}

		//after using the original / model, destroys it to remove it from the world
		this->actorCopies[x]->Destroy();
	}
}

bool UObjectPool::HasObjectAvailable(int requestSize)
{
	return this->availableObjects.Num() > 0;
}

int UObjectPool::GetMaxPoolSize()
{
	return this->maxPoolSize;
}

//spawns the object and place it on the passed location
AActorPoolable* UObjectPool::RequestPoolable(FVector loc)
{
	if(this->HasObjectAvailable(1))
	{
		AActorPoolable* object = this->availableObjects.Pop();
		object->SetIndex(this->usedObjects.Num());
		this->usedObjects.Push(object);
		object->OnActive();
		object->SetActorTransform(this->GetOwner()->GetActorTransform());
		object->SetActorLocation(loc);
		UE_LOG(LogTemp, Display, TEXT("Finished spawning %s"), *object->GetName());
		return object;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No more available objects."));
		return nullptr;
	}
}

//spawns the object and place it on the passed location; chooses a specific collectible type and assigns its parent's actor reference
AActorPoolable* UObjectPool::RequestPoolable(ECollectibles collectType, FVector loc, AActor* parentShape)
{
	if(this->HasObjectAvailable(1))
	{
		for (int i = 0; i < availableObjects.Num(); i++)
		{
			if(availableObjects[i]->collectibleType == collectType)
			{
				AActorPoolable* object = availableObjects[i];

				object->parentShape = parentShape;

				availableObjects.RemoveAt(i);
				usedObjects.Push(object);

				object->SetIndex(this->usedObjects.Num());
				object->OnActive();
				object->SetActorTransform(this->GetOwner()->GetActorTransform());
				object->SetActorLocation(loc);
				UE_LOG(LogTemp, Display, TEXT("Finished spawning %s"), *object->GetName());
				return object;
			}
		}
		return nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No more available objects."));
		return nullptr;
	}
}

TArray<AActorPoolable*> UObjectPool::RequestPoolabeBatch(int size)
{
	TArray<AActorPoolable*> objects;
	for (int i = 0; i < size && availableObjects.Num() > 0; i++)
	{
		objects.Push(this->RequestPoolable(this->GetOwner()->GetActorLocation()));
	}

	return objects;
}

//releases the actorPoolable object by passing in the poolableObject reference
void UObjectPool::ReleasePoolable(AActorPoolable* poolableObject)
{
	poolableObject->OnRelease();
	this->usedObjects.Remove(poolableObject);
	this->availableObjects.Push(poolableObject);
}

void UObjectPool::ReleasePoolableBatch(TArray<AActorPoolable*> objectList)
{
	for (int i = 0; i < objectList.Num(); i++)
	{
		this->ReleasePoolable(objectList[i]);
	}
}

void UObjectPool::ReleasePoolableBatch(int count)
{
	for (int i = 0; i < count && usedObjects.Num() > 0 ; i++)
	{
		this->ReleasePoolable(this->usedObjects[0]);
	}
}

