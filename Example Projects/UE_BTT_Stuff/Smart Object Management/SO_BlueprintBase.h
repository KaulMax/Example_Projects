// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SO_BlueprintBase.generated.h"

UCLASS()
class UPROOTED_API ASO_BlueprintBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASO_BlueprintBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	bool GetCurrOverlapStatus();
	AActor* GetCurrOverlapActor();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SmartObject, meta = (AllowPrivateAccess))
	class USmartObjectComponent* smartObject;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CollisionCheck, meta = (AllowPrivateAccess))
	class USphereComponent* collisionCheck;

	bool bIsOverlapping;
	AActor* overlapActor;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex);

};
