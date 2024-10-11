// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayBehavior.h"
#include "Interface_KeyRegister.h"
#include "SO_Behavior_FlyPoint.generated.h"


/**
 * 
 */
UCLASS()
class USO_Behavior_FlyPoint : public UGameplayBehavior, public IInterface_KeyRegister
{
	GENERATED_BODY()

	USO_Behavior_FlyPoint();

public:
	virtual bool Trigger(AActor& Avatar, const UGameplayBehaviorConfig* Config, AActor* SmartObjectOwner) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void EndBehavior(AActor& Avatar, const bool bInterrupted) override;
	virtual void OnGameplayTaskInitialized(UGameplayTask& Task) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess))
		float airTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess))
		float flyCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess))
		float initialFlyForce;

	UPROPERTY()
		class UBlackboardComponent* blackboard;

	UPROPERTY()
		class AEnemy_Base* enemy;
};