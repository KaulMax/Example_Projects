// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Fly_To_Location.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"


/*
* BTT to make the AI fly from its current position to a target position, to simulate flight turbulence the Z-axis navigation path is adjusted by a random small margin 
* in both up and down directions per nav point. In retrospect, it would have been a much better idea to just use a curve for this, especially considering that I already 
* use a curve delta to interpolate the position, but at least now I know better.
*/
UBTT_Fly_To_Location::UBTT_Fly_To_Location()
{
	NodeName = "BTT_FlyToLocation";

	INIT_TASK_NODE_NOTIFY_FLAGS();

	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = true;

	flySpeed = 890.f;
	maxFlightHeight = 600.f;
	minFlightHeight = 400.f;
}

EBTNodeResult::Type UBTT_Fly_To_Location::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type noderesult = EBTNodeResult::Failed;

	FFlyToLocationMemory* memory = CastInstanceNodeMemory<FFlyToLocationMemory>(NodeMemory);

	UBlackboardComponent* ownerblackboard = OwnerComp.GetBlackboardComponent();
	const UNavigationSystemV1* ownernavySystem = UNavigationSystemV1::GetCurrent(GetWorld());

	memory->CurrCharacter = OwnerComp.GetAIOwner()->GetCharacter();
	memory->MoveIdx = 0;

	world = GetWorld();

	if (!OwnerComp.GetAIOwner())
		UE_LOG(LogTemp, Warning, TEXT("UBTT_Fly_To_Location, !ownercontroller"))
	else if(!ownernavySystem)
		UE_LOG(LogTemp, Warning, TEXT("UBTT_Fly_To_Location, !ownernavySystem"))
	else if(!world)
		UE_LOG(LogTemp, Warning, TEXT("UBTT_Fly_To_Location, !world"))
	else
		noderesult = Task_FlyToLocation(ownerblackboard, OwnerComp.GetAIOwner(),ownernavySystem, NodeMemory);

	return noderesult;
}

void UBTT_Fly_To_Location::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FFlyToLocationMemory* memory = CastInstanceNodeMemory<FFlyToLocationMemory>(NodeMemory);

	if (memory->NavPathPoints.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTT_Fly_To_Location, !memory.NavPathPoints.IsSet()"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	else if (!memory->CurrCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTT_Fly_To_Location, !memory->OwnerCharacter"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	else if (!memory->CurveTimeline.IsPlaying())
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTT_Fly_To_Location, !CurveTimeline.IsPlaying()"));
		return;
	}
	else if (!curveFloat)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTT_Fly_To_Location, !curveFloat"));
		return;
	}
	else if (!memory->NavPathPoints.IsValidIndex(memory->MoveIdx))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	else
		ManageTimeline(NodeMemory, DeltaSeconds);
}

void UBTT_Fly_To_Location::ManageTimeline(uint8* _nodeMemory, float _dt)
{
	FFlyToLocationMemory* memory = CastInstanceNodeMemory<FFlyToLocationMemory>(_nodeMemory);

	memory->CurveTimeline.TickTimeline(_dt);

	float timelineprogress = memory->CurveTimeline.GetPlaybackPosition();

	FVector newloc = FMath::Lerp(memory->StartLoc, memory->EndLoc, timelineprogress);
	memory->CurrCharacter->SetActorLocation(newloc);

	if (memory->CurveTimeline.GetPlaybackPosition() >= memory->CurveTimeline.GetTimelineLength())
		BeginTimeline(_nodeMemory);

	FRotator lookrot = UKismetMathLibrary::FindLookAtRotation(memory->CurrCharacter->GetActorLocation(), memory->EndLoc);
	lookrot = FRotator(0, lookrot.Yaw, 0);

	if (lookrot.Yaw == 0)
		return;

	float lerplook = FMath::Lerp(memory->CurrCharacter->K2_GetActorRotation().Yaw, lookrot.Yaw, timelineprogress);
	lookrot.Yaw = lerplook;

	memory->CurrCharacter->SetActorRotation(lookrot);
}

EBTNodeResult::Type UBTT_Fly_To_Location::Task_FlyToLocation(UBlackboardComponent* _ownerblackboard, const AAIController* _ownercontroller, const UNavigationSystemV1* _ownerNavySystem, uint8* NodeMemory)
{
	EBTNodeResult::Type noderesult = EBTNodeResult::Failed;

	FFlyToLocationMemory* memory = CastInstanceNodeMemory<FFlyToLocationMemory>(NodeMemory);

	FVector flytoloc = _ownerblackboard->GetValueAsVector(IInterface_KeyRegister::GetKeyName(EKeyRegister_Names::KRN_V_MoveToLocation));

	if(flytoloc == FVector(0))
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTT_Fly_To_Location, flytoloc(0)"));
	}
	else
	{
		FVector ownerloc = FVector(_ownercontroller->K2_GetActorLocation().X, _ownercontroller->K2_GetActorLocation().Y, 0);
		UNavigationPath* navpath = _ownerNavySystem->FindPathToLocationSynchronously(world, ownerloc, flytoloc);

		memory->NavPathPoints.Reset();

		for(FVector navpoint : navpath->PathPoints)
		{
			float zpos = navpoint.Z + FMath::FRandRange(minFlightHeight, maxFlightHeight);

			memory->NavPathPoints.Add(FVector(navpoint.X, navpoint.Y, zpos));
		}

		BeginTimeline(NodeMemory);
		noderesult = EBTNodeResult::InProgress;
	}

	return noderesult;
}

void UBTT_Fly_To_Location::BeginTimeline(uint8* NodeMemory)
{
	if (curveFloat)
	{
		FFlyToLocationMemory* memory = CastInstanceNodeMemory<FFlyToLocationMemory>(NodeMemory);

		SetupEndLoc(NodeMemory);

		FOnTimelineFloat timelineprogress;

		timelineprogress.BindUFunction(this, FName("TimelineProgress"));

		memory->CurveTimeline.SetTimelineLengthMode(TL_LastKeyFrame);
		memory->CurveTimeline.SetLooping(false);
		memory->CurveTimeline.SetTimelineLength(5.f);
		memory->CurveTimeline.SetPropertySetObject(nullptr);
		memory->CurveTimeline.SetPlayRate(flySpeed / (memory->StartLoc - memory->EndLoc).Length());

		memory->CurveTimeline.AddInterpFloat(curveFloat, timelineprogress);

		memory->CurveTimeline.PlayFromStart();
	}
}


void UBTT_Fly_To_Location::SetupEndLoc(uint8* _nodeMemory)
{
	FFlyToLocationMemory* memory = CastInstanceNodeMemory<FFlyToLocationMemory>(_nodeMemory);

	memory->MoveIdx++;

	if (memory->MoveIdx > memory->NavPathPoints.Num())
		memory->MoveIdx = 1;

	memory->StartLoc = memory->CurrCharacter->GetActorLocation();

	if (memory->NavPathPoints.IsValidIndex(memory->MoveIdx))
		memory->EndLoc = memory->NavPathPoints[memory->MoveIdx];
}


void UBTT_Fly_To_Location::TimelineProgress(float _value)
{
	// Jump over timeline will be called from Tick since FOnTimelineFloat is needed as delegate in a UFunction which does not support uint8* which is needed for the Instanced Node Memory
}

uint16 UBTT_Fly_To_Location::GetInstanceMemorySize() const
{
	return sizeof(FFlyToLocationMemory);
}
