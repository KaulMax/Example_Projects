// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourcePoint.h"

#include "Engine/SkeletalMeshSocket.h"

// Sets default values
AResourcePoint::AResourcePoint()
{
	PrimaryActorTick.bCanEverTick = true;

	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	RootComponent = skeletalMesh;

	bIsEmpty = true;
}

void AResourcePoint::BeginPlay()
{
	Super::BeginPlay();

	Position = skeletalMesh->GetSocketByName("BuildSocket")->GetSocketLocation(skeletalMesh);
	Rotation = GetActorRotation();
}