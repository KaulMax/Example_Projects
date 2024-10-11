// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Find_And_Use_SO.h"

#include "AIController.h"
#include "BlackboardKeyType_SOClaimHandle.h"
#include "GameplayTagContainer.h"
#include "SmartObjectComponent.h"
#include "SO_BlueprintBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


/*
* BTT to Find and Use/Claim (different than UBTT_Use_SO_Distance) a smart object, the AI distinguishes between smart object types and only filters for the one specified for its use, 
* it also checks whether or not the smart object is infront and in line of sight of the enemy to be considered.
* Once a Smart Object is selected, the enemy will walk up to it to use/claim it.
*/
UBTT_Find_And_Use_SO::UBTT_Find_And_Use_SO(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "BTT_FindAndUseSmartObject_Own";

	INIT_TASK_NODE_NOTIFY_FLAGS();

	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;

	sOName = EKeyRegister_Names::KRN_SO_ClaimHandle;
	searchExtend = 2000.f;

	bFindOnly = false;
	bUseOnly = false;
	bTaskDistanced = false;
}


EBTNodeResult::Type UBTT_Find_And_Use_SO::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type noderesult = EBTNodeResult::Failed;

	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AAIController* controller = OwnerComp.GetAIOwner();
	
	if (!blackboard)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_Find_And_Use_SO, !blackboard"));
		noderesult = EBTNodeResult::Failed;
	}
	else if (!controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_Find_And_Use_SO, !controller"));
		noderesult = EBTNodeResult::Failed;
	}

	if(bUseOnly && !bFindOnly)
		noderesult = Task_UseSmartObject(OwnerComp, NodeMemory, controller, blackboard);
	else if(bFindOnly && !bUseOnly)
		noderesult = Task_FindSmartObject(blackboard, OwnerComp.GetAIOwner()->K2_GetActorLocation(), controller->GetCharacter());
	else if(!bFindOnly && !bUseOnly || bFindOnly && bUseOnly)
	{
		EBTNodeResult::Type status = Task_FindSmartObject(blackboard, OwnerComp.GetAIOwner()->K2_GetActorLocation(), controller->GetCharacter());

		if(status != EBTNodeResult::Failed)
			noderesult = Task_UseSmartObject(OwnerComp, NodeMemory, controller, blackboard);

		if (noderesult == EBTNodeResult::InProgress && bTaskDistanced)
			noderesult = EBTNodeResult::Succeeded;
	}

	return noderesult;
}

EBTNodeResult::Type UBTT_Find_And_Use_SO::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}

void UBTT_Find_And_Use_SO::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}


EBTNodeResult::Type UBTT_Find_And_Use_SO::Task_UseSmartObject(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, AAIController* _controller, UBlackboardComponent* _blackboard)
{
	EBTNodeResult::Type noderesult = EBTNodeResult::Failed;

	USmartObjectSubsystem* sosubsystem = USmartObjectSubsystem::GetCurrent(GetWorld());

	AActor& owneravatar = *_controller->GetPawn();
	const FVector ownerLocation = owneravatar.GetActorLocation();

	FSmartObjectClaimHandle soclaimhandle;
	soclaimhandle = _blackboard->GetValue<UBlackboardKeyType_SOClaimHandle>(IInterface_KeyRegister::GetKeyName(sOName));

	if (USmartObjectSubsystem::GetCurrent(GetWorld())->IsClaimedSmartObjectValid(soclaimhandle))
	{
		UAITask_UseGameplayBehaviorSmartObject* usesotask = NewBTAITask<UAITask_UseGameplayBehaviorSmartObject>(OwnerComp);
		usesotask->SetClaimHandle(soclaimhandle);
		usesotask->ReadyForActivation();

		noderesult = EBTNodeResult::InProgress;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_Find_And_Use_SO, !soclaimhandle"));
		noderesult = EBTNodeResult::Failed;
	}

	return noderesult;
}

EBTNodeResult::Type UBTT_Find_And_Use_SO::Task_FindSmartObject(UBlackboardComponent* _blackboard, FVector _ownerloc, ACharacter* _owner)
{
	EBTNodeResult::Type noderesult = EBTNodeResult::Type::Failed;

	FBox searchbox = UKismetMathLibrary::MakeBox(FVector(_ownerloc.X - searchExtend, _ownerloc.Y - searchExtend, _ownerloc.Z - searchExtend),
		FVector(_ownerloc.X + searchExtend, _ownerloc.Y + searchExtend, _ownerloc.Z + searchExtend));

	 USmartObjectSubsystem* sosubsystem;

	 UWorld* world = GetWorld();

	sosubsystem = USmartObjectSubsystem::GetCurrent(GetWorld());

	if (sosubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Stage 1"));

		FSmartObjectRequestFilter sofilter;
		FSmartObjectRequest sorequest;

		if(!sODefinition || !soTag.IsValid())
		{
			noderesult = EBTNodeResult::Failed;

			UE_LOG(LogTemp, Warning, TEXT("BTT_Find_And_Use_SO, !sODefinition || !soTag"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Stage 2"));

			sofilter.BehaviorDefinitionClasses = { sODefinition };
			sofilter.UserTags = soTag;
		}

		if (searchExtend <= 0 || !searchbox.IsValid)
		{
			noderesult = EBTNodeResult::Failed;
			UE_LOG(LogTemp, Warning, TEXT("BTT_Find_And_Use_SO, !searchExtend || !searchbox"));
		}


		sorequest.QueryBox = searchbox;
		sorequest.Filter = sofilter;
		TArray<FSmartObjectRequestResult> requestresults;

		if (requestresults.IsEmpty())
		{
			UE_LOG(LogTemp, Warning, TEXT("Stage 3"));

			sosubsystem->FindSmartObjects(sorequest, requestresults);

			TArray<FSmartObjectRequestResult> availableobjects;
			
			for (size_t i = 0; i < requestresults.Num(); i++)
			{
				FEnvQueryRequest jumpPosReq;
			
				TOptional<FVector> slotloc = sosubsystem->GetSlotLocation(requestresults[i].SlotHandle);

				FVector dir = slotloc.GetValue() - _owner->GetActorLocation();
				dir.Normalize();
			
				float dot = FVector::DotProduct(_owner->GetActorForwardVector(), dir);

				if (dot >= 0.f)
				{
					FHitResult hit;
					const TArray<AActor*> toIgnore = {_owner};

					UKismetSystemLibrary::LineTraceSingleByProfile(world, _owner->K2_GetActorLocation(), slotloc.GetValue(), "BlockAll",
						false, toIgnore, EDrawDebugTrace::None, hit, true, FColor::Red, FColor::Transparent, 1.f);
				
					if(hit.bBlockingHit && Cast<ASO_BlueprintBase>(hit.GetActor()))
						availableobjects.Add(requestresults[i]);
				}
			}


			requestresults = availableobjects;
		}

		if (requestresults.Num() <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Stage 4"));

			noderesult = EBTNodeResult::Failed;
			requestresults.Reset();
		}
		else if (requestresults.Num() > 0)
		{
			int idx = FMath::RandRange(0, requestresults.Num() - 1);
			UE_LOG(LogTemp, Warning, TEXT("Stage 5"));

			if(requestresults.IsValidIndex(idx))
			{
				UE_LOG(LogTemp, Warning, TEXT("Stage 6"));

				FSmartObjectClaimHandle soclaimhandle;

				soclaimhandle = sosubsystem->Claim(requestresults[idx]);

				_blackboard->SetValue<UBlackboardKeyType_SOClaimHandle>(IInterface_KeyRegister::GetKeyName(sOName), soclaimhandle);
				requestresults.Reset();

				noderesult = EBTNodeResult::Succeeded;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Stage 7"));

				noderesult = EBTNodeResult::Failed;
				requestresults.Reset();
			}
		}
	}
	else
	{
		noderesult = EBTNodeResult::Failed;
		UE_LOG(LogTemp, Warning, TEXT("BTT_Find_And_Use_SO, !sosubsystem"));
	}

	return noderesult;
}