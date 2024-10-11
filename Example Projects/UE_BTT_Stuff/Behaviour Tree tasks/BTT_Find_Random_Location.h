// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Interface_KeyRegister.h"
#include "BTT_Find_Random_Location.generated.h"

/**
 * 
 */
UCLASS()
class UBTT_Find_Random_Location : public UBTTaskNode, public IInterface_KeyRegister
{
	GENERATED_BODY()

	UBTT_Find_Random_Location();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


protected:
	EBTNodeResult::Type Task_SampleRandomLocation( UBlackboardComponent* _ownerblackboard, const AAIController* _ownercontroller, const class UNavigationSystemV1* _ownernavySystem);

private:
	UPROPERTY(EditAnywhere, Category = Node, meta = (AllowPrivateAccess))
		float searchRadius;
	UPROPERTY(EditAnywhere, Category = Node, meta = (AllowPrivateAccess))
		float minRadius;

	UPROPERTY(EditAnywhere, Category = Node, meta = (AllowPrivateAccess))
		int searchIterations;
};
