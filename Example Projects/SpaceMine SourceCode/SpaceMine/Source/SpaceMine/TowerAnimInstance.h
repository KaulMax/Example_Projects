// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TowerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMINE_API UTowerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	const TArray<AActor*> ActorRefference = TArray<AActor*>{ Cast<AActor>(this) };

public:
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Building)
	class ATowerBase* Structure;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	bool bCanMakeDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Building)
	APawn* Pawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Building)
	FVector LookAtPos;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
		bool bCanUpdate;
};
