// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraLerp.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ACameraLerp::ACameraLerp()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACameraLerp::BeginPlay()
{
	Super::BeginPlay();


	if (MovePoints.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACameraLerp, MovePoints.Num() <= 0"));
		return;
	}

	TArray<AActor*> actors;

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Player", actors);

	menuActor = actors[0];

	currMovePos = MovePoints[0];

	if(menuActor)
	{
		menuActor->SetActorLocation(currMovePos->GetActorLocation());
		menuActor->SetActorRotation(currMovePos->GetActorRotation());
	}
}

void ACameraLerp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurveTimeline.IsPlaying())
		CurveTimeline.TickTimeline(DeltaTime);
}

void ACameraLerp::MoveCameraToNewPosition()
{
	if(MovePoints.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACameraLerp, MovePoints.Num() <= 0"));
		return;
	}

	BeginTimeLine();
}

void ACameraLerp::MoveCameraToGameStartPos()
{
	bGameStarted = true;
	MoveCameraToNewPosition();
}

void ACameraLerp::BeginTimeLine()
{
	if (MovePoints.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACameraLerp, MovePoints.Num() <= 0"));
		return;
	}

	if(!bGameStarted)
	{
		for (size_t i = 0; i < 100; i++)
		{
			int rnd = FMath::RandRange(0, MovePoints.Num() - 1);

			if (rnd != currmoveIdx)
			{
				currmoveIdx = FMath::RandRange(0, MovePoints.Num() - 1);
				break;
			}
			else if (i >= 100)
				currmoveIdx = 0;
		}

		currMovePos = MovePoints[FMath::RandRange(0, MovePoints.Num() - 1)];
	}
	else if(bGameStarted)
	{
		if (!gameStartMovePos)
		{
			UE_LOG(LogTemp, Warning, TEXT("ACameraLerp, !gameStartMovePos"));
			return;
		}

		currMovePos = gameStartMovePos;
	}

	startPos = menuActor->GetActorLocation();
	startRot = menuActor->GetActorRotation();

	FOnTimelineFloat timelineprogress;

	timelineprogress.BindUFunction(this, FName("TickTimeline"));

	CurveTimeline.SetTimelineLengthMode(TL_LastKeyFrame);
	CurveTimeline.SetPlayRate(.25f);
	CurveTimeline.SetLooping(false);

	CurveTimeline.AddInterpFloat(curveFloat, timelineprogress);

	CurveTimeline.PlayFromStart();
}

void ACameraLerp::TickTimeline(float _alpha)
{
	if (!menuActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACameraLerp, !menuCamera"));
		return;
	}

	menuActor->SetActorLocation(FMath::Lerp(startPos, currMovePos->GetActorLocation(), _alpha));
	menuActor->SetActorRotation(FMath::Lerp(startRot, currMovePos->GetActorRotation(), _alpha));
}
