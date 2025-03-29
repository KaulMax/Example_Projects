// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "CameraLerp.generated.h"

UCLASS()
class SPACEMINE_API ACameraLerp : public AActor
{
	GENERATED_BODY()
	
public:	
	ACameraLerp();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginTimeLine();
	UFUNCTION()
		void TickTimeline(float _alpha);

	UPROPERTY(VisibleAnywhere)
		AActor* currMovePos;
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
		AActor* gameStartMovePos;

	UPROPERTY(VisibleAnywhere)
		AActor* menuActor;

	UPROPERTY()
		bool bGameStarted;

	UPROPERTY()
	FVector startPos;
	UPROPERTY()
	FRotator startRot;

	UPROPERTY()
		int currmoveIdx;

public:	
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
		TArray<AActor*> MovePoints;

	FTimeline CurveTimeline;

	UPROPERTY(EditAnywhere, Category = Timeline, meta = (AllowPrivateAccess))
	UCurveFloat* curveFloat;

	UFUNCTION(BlueprintCallable)
	void MoveCameraToNewPosition();

	UFUNCTION(BlueprintCallable)
		void MoveCameraToGameStartPos();
};
