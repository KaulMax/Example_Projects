// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerAnimInstance.h"

#include "TowerBase.h"

void UTowerAnimInstance::NativeInitializeAnimation()
{
	if (!Pawn)
		Pawn = TryGetPawnOwner();

	if (!Pawn)
		return;

	Structure = Cast<ATowerBase>(Pawn);

	bCanUpdate = true;
}

void UTowerAnimInstance::UpdateAnimationProperties()
{
	if (!Pawn)
		Pawn = TryGetPawnOwner();

	if (!Pawn)
		return;

	if(!Structure)
		Structure = Cast<ATowerBase>(Pawn);
}