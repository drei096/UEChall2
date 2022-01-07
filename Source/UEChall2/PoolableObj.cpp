// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolableObj.h"

// Sets default values for this component's properties
UPoolableObj::UPoolableObj()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPoolableObj::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPoolableObj::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPoolableObj::initialize()
{
}

void UPoolableObj::onRelease()
{
}

void UPoolableObj::onActivate()
{
}

AActor* UPoolableObj::createCopy(ObjPools* pool)
{
	FActorSpawnParameters spawnParams;
	spawnParams.Template = this->GetOwner();
	spawnParams.Owner = this->GetOwner();

	AActor* myActor =  this->GetWorld()->SpawnActor<AActor>(this->GetClass(), spawnParams);
	//copy = objs[k]->FindComponentByClass<UPoolableObj>();
	//UPoolableObj* actorSc = Cast<UPoolableObj>(myActor);
	if(myActor->FindComponentByClass<UPoolableObj>() != nullptr)
	{
		UPoolableObj* actorSc = myActor->FindComponentByClass<UPoolableObj>();
		actorSc->poolRef = pool;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing UPoolableObj!"));
	}

	return myActor;
}

