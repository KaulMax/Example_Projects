// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Interface_KeyRegister.h"
#include "BTT_PerformAttack.generated.h"

struct FBTAttackMemory
{
	float timeBetweenAttacks = 0.f;
	float dodgeForce = 0.f;

	int attackComboLenght = 0;

	class AEnemy_Base* EnemyRef;
};

/**
 * 
 */
UCLASS()
class UPROOTED_API UBTT_PerformAttack : public UBTTaskNode, public IInterface_KeyRegister
{
	GENERATED_BODY()


public:
	UBTT_PerformAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual uint16 GetInstanceMemorySize() const override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackStats, meta = (AllowPrivateAccess))
	float TimeBetweenAttacks;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackStats, meta = (AllowPrivateAccess))
	float DodgeForce;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackStats, meta = (AllowPrivateAccess))
	int AttackComboLenght;

	UFUNCTION()
	void Task_Attack();
	UFUNCTION()
	void Task_ValidateAttack();

	UPROPERTY()
	bool bCanAttack;

	UPROPERTY()
	FTimerHandle attackCooldownHandle;
};

inline void UBTT_PerformAttack::Task_Attack()
{
}
