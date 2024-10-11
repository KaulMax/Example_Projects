// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface_KeyRegister.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Components/TimelineComponent.h"
#include "BTT_Fly_To_Location.generated.h"

struct FFlyToLocationMemory
{
	TArray<FVector> NavPathPoints;
	FTimeline CurveTimeline;
	ACharacter* CurrCharacter;

	FVector StartLoc;
	FVector EndLoc;

	int MoveIdx;
};

/**
 * 
 */
UCLASS()
class UBTT_Fly_To_Location : public UBTTaskNode, public IInterface_KeyRegister
{
	GENERATED_BODY()

	UBTT_Fly_To_Location();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	EBTNodeResult::Type Task_FlyToLocation(UBlackboardComponent* _ownerblackboard, const AAIController* _ownercontroller, const class UNavigationSystemV1* _ownernavySystem, uint8* NodeMemory);

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual uint16 GetInstanceMemorySize() const override;

	UFUNCTION()
	void TimelineProgress(float _alpha);
	virtual void BeginTimeline(uint8* NodeMemory);

	void ManageTimeline(uint8* _nodeMemory, float _dt);
	void SetupEndLoc(uint8* _nodeMemory);

private:
	UPROPERTY()
		UWorld* world;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess))
		float flySpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess))
		float maxFlightHeight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess))
		float minFlightHeight;

	UPROPERTY(EditAnywhere, Category = Timeline, meta = (AllowPrivateAccess))
	UCurveFloat* curveFloat;
};