// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Find_Random_Location.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


/*
* BTT to find a randomly accessible location for the AI to patrol.
*/
UBTT_Find_Random_Location::UBTT_Find_Random_Location()
{
	NodeName = "BTT_FindRandomLocation";

	searchRadius = 10000.f;
	minRadius = 500.f;
	searchIterations = 50.f;
}

EBTNodeResult::Type UBTT_Find_Random_Location::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type noderesult = EBTNodeResult::Failed;

	UBlackboardComponent* ownerblackboard = OwnerComp.GetBlackboardComponent();

	const UNavigationSystemV1* ownernavySystem = UNavigationSystemV1::GetCurrent(GetWorld());
	const AAIController* ownercontroller = OwnerComp.GetAIOwner();

	if (!ownercontroller)
		UE_LOG(LogTemp, Warning, TEXT("BTT_FindRandomLocation, !ownercontroller"))
	else if (!ownernavySystem)
		UE_LOG(LogTemp, Warning, TEXT("BTT_FindRandomLocation, !ownernavySystem"))
	else
		noderesult = Task_SampleRandomLocation(ownerblackboard, ownercontroller, ownernavySystem);

	return noderesult;
}

EBTNodeResult::Type UBTT_Find_Random_Location::Task_SampleRandomLocation( UBlackboardComponent* _ownerblackboard, const AAIController* _ownercontroller, const UNavigationSystemV1* _ownernavySystem)
{
	EBTNodeResult::Type noderesult = EBTNodeResult::Failed;

	FVector ownerLocation = _ownercontroller->K2_GetActorLocation();
	UCharacterMovementComponent* charmovement = _ownercontroller->GetCharacter()->GetCharacterMovement();
	FNavLocation goallocation;

	if(!charmovement)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_FindRandomLocation, !charmovement"))
		noderesult =  EBTNodeResult::Succeeded;
	}
	else
	{
		FVector rndpoint;

		for (size_t i = 0; i < searchIterations; i++)
		{
			if(_ownernavySystem->GetRandomReachablePointInRadius(ownerLocation, searchRadius, goallocation, 0, 0))
			{
				if((ownerLocation - goallocation).Length() >= minRadius)
				{
					_ownerblackboard->SetValueAsVector(IInterface_KeyRegister::GetKeyName(EKeyRegister_Names::KRN_V_MoveToLocation), goallocation);
					break;
				}
			}
			else if( i >= searchIterations)
			{
				if (_ownernavySystem->GetRandomReachablePointInRadius(ownerLocation, searchRadius, goallocation, 0, 0))
					_ownerblackboard->SetValueAsVector(IInterface_KeyRegister::GetKeyName(EKeyRegister_Names::KRN_V_MoveToLocation), goallocation);
				else
					_ownerblackboard->SetValueAsVector(IInterface_KeyRegister::GetKeyName(EKeyRegister_Names::KRN_V_MoveToLocation), ownerLocation);
			}
		}

		noderesult = EBTNodeResult::Succeeded;
	}

	return noderesult;
}
