// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"

#include "MainEnemy.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	if (!Pawn)
		Pawn = TryGetPawnOwner();

	if (!Pawn)
		return;

	Enemy = Cast<AMainEnemy>(Pawn);
}

void UEnemyAnimInstance::UpdateAnimationProperties()
{
	if (!Pawn)
		Pawn = TryGetPawnOwner();

	if (!Pawn)
		return;

	FVector speed = Pawn->GetVelocity();
	FVector lateralSpeed = FVector(speed.X, speed.Y, 0.f);
	MovementSpeed = lateralSpeed.Size();

	Enemy = Cast<AMainEnemy>(Pawn);
}