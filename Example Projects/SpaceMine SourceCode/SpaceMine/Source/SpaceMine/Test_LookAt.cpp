// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_LookAt.h"

// Sets default values for this component's properties
UTest_LookAt::UTest_LookAt()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTest_LookAt::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTest_LookAt::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

