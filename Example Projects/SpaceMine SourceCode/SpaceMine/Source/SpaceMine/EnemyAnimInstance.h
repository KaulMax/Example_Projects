// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMINE_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Movement)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float GetHitAlpha;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	bool bDamagedFinished;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement)
	class AMainEnemy* Enemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement)
	class APawn* Pawn;
};
