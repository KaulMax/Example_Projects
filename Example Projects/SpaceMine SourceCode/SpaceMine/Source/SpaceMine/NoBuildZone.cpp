// Fill out your copyright notice in the Description page of Project Settings.


#include "NoBuildZone.h"

// Sets default values
ANoBuildZone::ANoBuildZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("SkeletalMesh");
	RootComponent = StaticMeshComponent;
}

// Called when the game starts or when spawned
void ANoBuildZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANoBuildZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

