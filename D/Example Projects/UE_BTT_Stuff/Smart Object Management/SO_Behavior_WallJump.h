// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayBehavior.h"
#include "Interface_KeyRegister.h"
#include "SO_Behavior_WallJump.generated.h"


/**
 * 
 */
UCLASS()
class USO_Behavior_WallJump : public UGameplayBehavior, public IInterface_KeyRegister
{
	GENERATED_BODY()

	USO_Behavior_WallJump();

public:
	virtual bool Trigger(AActor& Avatar, const UGameplayBehaviorConfig* Config, AActor* SmartObjectOwner) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void EndBehavior(AActor& Avatar, const bool bInterrupted) override;
	virtual void OnGameplayTaskInitialized(UGameplayTask& Task) override;

private:
	void HandleQueryResult(TSharedPtr<struct FEnvQueryResult> _result);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta=(AllowPrivateAccess))
	float airTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess))
	float wallJumpCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess))
	float initialJumpForce;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = AI, meta = (AllowPrivateAccess))
	class UEnvQuery* jumpQueryPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = AI, meta = (AllowPrivateAccess))
	UEnvQuery* jumpQueryRandom;

	UPROPERTY()
	class UBlackboardComponent* blackboard;


	UPROPERTY()
	FTimerHandle timerHandleMoveMode;
	UPROPERTY()
	FTimerHandle timerHandleEnviMode;
	UPROPERTY()
	FTimerHandle timerHandleDEBUGGROUND;

	UPROPERTY()
	class AEnemy_Base* enemy;
};

