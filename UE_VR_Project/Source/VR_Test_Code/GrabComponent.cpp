// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"

#include "MotionControllerComponent.h"

// Class for all objects that can be picked up by the player.
UGrabComponent::UGrabComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}

void UGrabComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UGrabComponent::InitGrabComponent(AActor* _compParent)
{
	compParent = _compParent;
}

void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UGrabComponent::TryGrabObject(AActor* _grabHolder, UMotionControllerComponent* _grabController)
{
	bool status = true;

	if (!compParent)
		return false;

	currHolder = _grabHolder;
	currController = _grabController;

	if(!currHolder || !currController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGrabComponent, !currHolder || !currController"))
		return false;
	}

	compParent->AttachToComponent(currController, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	return status;
}

bool UGrabComponent::TryReleaseObject()
{
	bool status = true;

	compParent->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	currHolder = nullptr;
	currController = nullptr;

	return status;
}
