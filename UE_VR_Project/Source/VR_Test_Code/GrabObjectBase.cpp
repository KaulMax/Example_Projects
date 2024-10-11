// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabObjectBase.h"

#include "GrabComponent.h"

// Unused
AGrabObjectBase::AGrabObjectBase()
{
	PrimaryActorTick.bCanEverTick = true;

	objectMesh = CreateDefaultSubobject<UStaticMeshComponent>("ObjectMesh");
	RootComponent = objectMesh;

	grabComponent = CreateDefaultSubobject<UGrabComponent>("GrabComponent");
	grabComponent->SetupAttachment(GetRootComponent());
}

void AGrabObjectBase::BeginPlay()
{
	Super::BeginPlay();

	grabComponent->InitGrabComponent(this);
}

void AGrabObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

