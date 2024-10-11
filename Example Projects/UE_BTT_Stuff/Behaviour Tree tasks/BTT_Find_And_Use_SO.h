// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface_KeyRegister.h"
#include "SmartObjectSubsystem.h"
#include "AI/AITask_UseGameplayBehaviorSmartObject.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Find_And_Use_SO.generated.h"


/**
 * 
 */
UCLASS()
class UBTT_Find_And_Use_SO : public UBTTaskNode, public IInterface_KeyRegister
{
	GENERATED_BODY()

public:
	UBTT_Find_And_Use_SO(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

private:
	UPROPERTY(EditAnywhere, Category = Node, meta = (AllowPrivateAccess))
		EKeyRegister_Names sOName;

	UPROPERTY(EditAnywhere, Category = Node, meta = (AllowPrivateAccess))
		TSubclassOf<USmartObjectBehaviorDefinition> sODefinition;


	UPROPERTY(EditAnywhere, Category = Node, meta = (AllowPrivateAccess))
		FGameplayTagContainer soTag;

	UPROPERTY(EditAnywhere, Category = Node, meta = (AllowPrivateAccess))
		float searchExtend;

	UPROPERTY(EditAnywhere, Category = Node, meta = (AllowPrivateAccess))
	bool bFindOnly;
	UPROPERTY(EditAnywhere, Category = Node, meta = (AllowPrivateAccess))
	bool bUseOnly;
	UPROPERTY(EditAnywhere, Category = Node, meta = (AllowPrivateAccess))
	bool bTaskDistanced;

	EBTNodeResult::Type Task_UseSmartObject(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, AAIController* controller, UBlackboardComponent* blackboard);
	EBTNodeResult::Type Task_FindSmartObject(UBlackboardComponent* _blackboard, FVector _ownerloc, ACharacter* _owner);
};
