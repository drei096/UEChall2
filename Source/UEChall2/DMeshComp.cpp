// Fill out your copyright notice in the Description page of Project Settings.


#include "DMeshComp.h"


// Sets default values for this component's properties
UDMeshComp::UDMeshComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//this->GetOwner()->FindComponentByClass<UDestructibleComponent>()
	// ...

	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ghostMesh"));
}


// Called when the game starts
void UDMeshComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDMeshComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

