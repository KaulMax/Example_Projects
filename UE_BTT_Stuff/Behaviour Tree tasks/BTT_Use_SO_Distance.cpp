// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Use_SO_Distance.h"

#include "AIController.h"
#include "BlackboardKeyType_SOClaimHandle.h"
#include "GameplayTagContainer.h"
#include "SmartObjectComponent.h"
#include "SmartObjectSubsystem.h"
#include "SO_BlueprintBase.h"
#include "AI/AITask_UseGameplayBehaviorSmartObject.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


/*
* This BTT should not actually exist, its purpose is to find and use smart objects just like UBTT_Find_And_Use_SO, but instead of Search->Find->Filter->Move->Claim it should be Search->Find->Filter->Claim, 
* without the whole movement part. But since the behaviour of Unreal Engines smart objects (at least up to the latest version at the time of writing (5.1) and to my knowledge) has to be triggered 
* by an actual overlap between the nav agent (while on the nav mesh) and the smart object, this class is used as an intermediate step for smart objects whose behaviour should be executed at a distance.
* But maybe I missed something, because that really doesn't feel right :D
*/
UBTT_Use_SO_Distance::UBTT_Use_SO_Distance()
{
	NodeName = "BTT_Use_SO_Distance_Own";

	INIT_TASK_NODE_NOTIFY_FLAGS();

	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = true;

	sOName = EKeyRegister_Names::KRN_SO_ClaimHandle;
}

EBTNodeResult::Type UBTT_Use_SO_Distance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type noderesult = EBTNodeResult::InProgress;

	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();


	FSmartObjectClaimHandle soclaimhandle;
	soclaimhandle = blackboard->GetValue<UBlackboardKeyType_SOClaimHandle>(IInterface_KeyRegister::GetKeyName(sOName));

	USmartObjectSubsystem* sosubsystem = USmartObjectSubsystem::GetCurrent(GetWorld());
	TOptional<FVector> slotloc = sosubsystem->GetSlotLocation(soclaimhandle);

	UCharacterMovementComponent* charmovement = OwnerComp.GetAIOwner()->GetCharacter()->GetCharacterMovement();

	if (!charmovement)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_Use_SO_Distance, !charmovement"))
		noderesult = EBTNodeResult::Failed;
	}
	else if (sosubsystem->IsClaimedSmartObjectValid(soclaimhandle) && sosubsystem->IsSmartObjectSlotValid(soclaimhandle.SlotHandle) && sosubsystem->IsSmartObjectValid(soclaimhandle.SmartObjectHandle))
	{
		if(!blackboard)
		{
			noderesult = EBTNodeResult::Failed;
			UE_LOG(LogTemp, Warning, TEXT("BTT_Use_SO_Distance, !blackboard"))
		}
		else if(!slotloc.IsSet())
		{
			noderesult = EBTNodeResult::Failed;
			UE_LOG(LogTemp, Warning, TEXT("BTT_Use_SO_Distance, !slotloc"))
		}
		else
		{
			FBTUseSODistanceMemory* taskmemory = CastInstanceNodeMemory<FBTUseSODistanceMemory>(NodeMemory);

			taskmemory->SlotLoc = slotloc;
			taskmemory->SoClaimHandle = soclaimhandle;
			taskmemory->SoSubsystem = sosubsystem;

			taskmemory->CurrCharacter = OwnerComp.GetAIOwner()->GetCharacter();
			taskmemory->EndLoc = slotloc.GetValue();
			taskmemory->StartLoc = taskmemory->CurrCharacter->K2_GetActorLocation();

			if (bCanFly)
			{
				BeginTimeline(NodeMemory);
				blackboard->SetValue<UBlackboardKeyType_Bool>(IInterface_KeyRegister::GetKeyName(EKeyRegister_Names::KRN_B_IsGrounded), false);
				FRotator lookrot = UKismetMathLibrary::FindLookAtRotation(OwnerComp.GetAIOwner()->K2_GetActorLocation(), slotloc.GetValue());
				lookrot = FRotator(0, lookrot.Yaw, 0);
				OwnerComp.GetAIOwner()->GetCharacter()->K2_SetActorRotation(lookrot, false);
				blackboard->SetValue<UBlackboardKeyType_Bool>(IInterface_KeyRegister::GetKeyName(EKeyRegister_Names::KRN_B_HasEnviAction), false);
				charmovement->SetMovementMode(EMovementMode::MOVE_Flying);
			}
			else
				charmovement->SetMovementMode(EMovementMode::MOVE_Walking);


			noderesult = EBTNodeResult::InProgress;
		}
	}
	else
	{
		charmovement->SetMovementMode(EMovementMode::MOVE_Walking);
		blackboard->SetValue<UBlackboardKeyType_Bool>(IInterface_KeyRegister::GetKeyName(EKeyRegister_Names::KRN_B_IsGrounded), true);

		UE_LOG(LogTemp,Warning,TEXT("BTT_Use_SO_Distance, !soclaimhandle"))

		noderesult = EBTNodeResult::Failed;
	}

	return noderesult;
}

void UBTT_Use_SO_Distance::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UCharacterMovementComponent* charmovement = OwnerComp.GetAIOwner()->GetCharacter()->GetCharacterMovement();

	FBTUseSODistanceMemory* taskmemory = CastInstanceNodeMemory<FBTUseSODistanceMemory>(NodeMemory);

	taskmemory->CurveTimeline.TickTimeline(DeltaSeconds);

	if(taskmemory->CurveTimeline.IsPlaying())
	{
		float timelineprogress = taskmemory->CurveTimeline.GetPlaybackPosition();

		FVector newloc = FMath::Lerp(taskmemory->StartLoc, taskmemory->EndLoc, timelineprogress);
		taskmemory->CurrCharacter->SetActorLocation(newloc);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_Use_SO_Distance, !CurveTimeline.IsPlaying()"))
		return;
	}

	if(ASO_BlueprintBase* asobb = Cast<ASO_BlueprintBase>(taskmemory->SoSubsystem->GetSmartObjectComponent(taskmemory->SoClaimHandle)->GetOwner()))
	{
		if(asobb->GetCurrOverlapStatus())
		{
			UE_LOG(LogTemp, Warning, TEXT("9"))

			taskmemory->TaskPtr.Reset();

			taskmemory->TaskPtr = NewBTAITask<UAITask_UseGameplayBehaviorSmartObject>(OwnerComp);
			taskmemory->TaskPtr->SetClaimHandle(taskmemory->SoClaimHandle);
			taskmemory->TaskPtr->ReadyForActivation();

			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

uint16 UBTT_Use_SO_Distance::GetInstanceMemorySize() const
{
	return sizeof(FBTUseSODistanceMemory);
}

EBTNodeResult::Type UBTT_Use_SO_Distance::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}

void UBTT_Use_SO_Distance::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}


void UBTT_Use_SO_Distance::BeginTimeline(uint8* NodeMemory)
{
	if(curveFloat)
	{
		FBTUseSODistanceMemory* taskmemory = CastInstanceNodeMemory<FBTUseSODistanceMemory>(NodeMemory);
		
		FOnTimelineFloat timelineprogress;

		timelineprogress.BindUFunction(this, FName("TimelineProgress"));

		taskmemory->CurveTimeline.SetTimelineLengthMode(TL_LastKeyFrame);
		taskmemory->CurveTimeline.SetLooping(false);
		taskmemory->CurveTimeline.SetTimelineLength(5.f);
		taskmemory->CurveTimeline.SetPlayRate(1.f);
		taskmemory->CurveTimeline.SetPropertySetObject(nullptr);

		taskmemory->CurveTimeline.AddInterpFloat(curveFloat, timelineprogress);
								 
		taskmemory->CurveTimeline.PlayFromStart();
	}
}

void UBTT_Use_SO_Distance::TimelineProgress(float _alpha)
{
	// Jump over timeline will be called from Tick since FOnTimelineFloat is needed as delegate in a UFunction which does not support uint8* which is needed for the Instanced Node Memory
}