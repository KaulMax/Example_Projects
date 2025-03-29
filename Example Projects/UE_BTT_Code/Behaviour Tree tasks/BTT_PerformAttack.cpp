// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_PerformAttack.h"

#include "AIController.h"
#include "Enemy_Base.h"
#include "Interface_KeyRegister.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"

/*
* Simple attack task for the opponent when the player is in overlap range
* 
*/
UBTT_PerformAttack::UBTT_PerformAttack()
{
	NodeName = "BTT_Perform_Attack";

	INIT_TASK_NODE_NOTIFY_FLAGS();

	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;

	bCanAttack = true;
	TimeBetweenAttacks = .5f;
	DodgeForce = 1000.f;
	AttackComboLenght = 3;
}

EBTNodeResult::Type UBTT_PerformAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type noderesult = EBTNodeResult::Failed;

	FBTAttackMemory* taskmemory = CastInstanceNodeMemory<FBTAttackMemory>(NodeMemory);
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

	if(blackboard)
	{
		
		taskmemory->attackComboLenght = AttackComboLenght;
		taskmemory->dodgeForce = DodgeForce;
		taskmemory->timeBetweenAttacks = TimeBetweenAttacks;
		taskmemory->EnemyRef = Cast<AEnemy_Base>(OwnerComp.GetAIOwner()->GetCharacter());

		if (!IsValid(taskmemory->EnemyRef))
		{
			GetWorld()->GetTimerManager().SetTimer(attackCooldownHandle, this, &UBTT_PerformAttack::Task_ValidateAttack, taskmemory->timeBetweenAttacks, true);
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("UBTT_PerformAttack, EnemyRef"));

		noderesult = EBTNodeResult::InProgress;
	}
	else
	{
		noderesult = EBTNodeResult::Failed;
		UE_LOG(LogTemp, Warning, TEXT("UBTT_PerformAttack, !blackboard"));
	}

	if(!blackboard->GetValue<UBlackboardKeyType_Bool>(IInterface_KeyRegister::GetKeyName(EKeyRegister_Names::KRN_B_PlayerInAttackRange)))
		noderesult = EBTNodeResult::Failed;

	return noderesult;
}

void UBTT_PerformAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FBTAttackMemory* taskmemory = CastInstanceNodeMemory<FBTAttackMemory>(NodeMemory);

	if(!IsValid(taskmemory->EnemyRef))
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTT_PerformAttack, EnemyRef"));
		return;
	}

	if(bCanAttack)
	{
		bCanAttack = false;
		taskmemory->EnemyRef->Attack();
	}
}

uint16 UBTT_PerformAttack::GetInstanceMemorySize() const
{
	return sizeof(FBTAttackMemory);
}

EBTNodeResult::Type UBTT_PerformAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type noderesult = EBTNodeResult::Failed;

	return noderesult;
}

void UBTT_PerformAttack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{

}

void UBTT_PerformAttack::Task_ValidateAttack()
{
	bCanAttack = true;
}
