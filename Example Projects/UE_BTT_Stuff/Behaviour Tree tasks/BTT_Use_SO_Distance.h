// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface_KeyRegister.h"
#include "SmartObjectRuntime.h"
#include "AI/AITask_UseGameplayBehaviorSmartObject.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Components/TimelineComponent.h"
#include "BTT_Use_SO_Distance.generated.h"

struct FBTUseSODistanceMemory
{
	TWeakObjectPtr<UAITask_UseGameplayBehaviorSmartObject> TaskPtr;

	TOptional<FVector> SlotLoc;
	FSmartObjectClaimHandle SoClaimHandle;
	USmartObjectSubsystem* SoSubsystem;

	FVector StartLoc;
	FVector EndLoc;
	ACharacter* CurrCharacter;
	FTimeline CurveTimeline;
};


/**
 * 
 */
UCLASS()
class UBTT_Use_SO_Distance : public UBTTaskNode, public IInterface_KeyRegister
{
	GENERATED_BODY()

public:
	UBTT_Use_SO_Distance();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual uint16 GetInstanceMemorySize() const override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	UFUNCTION()
	virtual void TimelineProgress(float _alpha);
	virtual void BeginTimeline(uint8* NodeMemory);

private:
	UPROPERTY(EditAnywhere, Category = Node, meta = (AllowPrivateAccess))
		EKeyRegister_Names sOName;

	UPROPERTY(EditAnywhere, Category = Node, meta = (AllowPrivateAccess))
		bool bCanFly;

	UPROPERTY(EditAnywhere, Category = Node, meta = (AllowPrivateAccess))
		bool bIsEnviAction;

	UPROPERTY(EditAnywhere, Category = Node, meta = (AllowPrivateAccess))
		TSubclassOf<USmartObjectBehaviorDefinition> definitionClass;

	UPROPERTY(EditAnywhere, Category = Timeline, meta = (AllowPrivateAccess))
		UCurveFloat* curveFloat;

};