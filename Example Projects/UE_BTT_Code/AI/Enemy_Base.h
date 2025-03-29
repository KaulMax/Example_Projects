// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDamageable.h"
#include "Interface_KeyRegister.h"
#include "Interface_SmartObject.h"
#include "GameFramework/Character.h"
#include "Enemy_Base.generated.h"

UCLASS()
class AEnemy_Base : public ACharacter, public IInterface_SmartObject_Caller, public IIDamageable, public IInterface_KeyRegister
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Base();

	UFUNCTION()
		void Attack();

	UFUNCTION()
	void SetBlackboardValueTimer_Bool(EKeyRegister_Names _bbKey, float _time, bool _resetValue);
	void SetMovementModeTimer(EMovementMode _moveMode, float _timer);

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
		virtual void OnTargetBeginOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);

	UFUNCTION()
		virtual	void OnTargetEndOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex);

private:
	UPROPERTY()
		class AEnemy_AIController* aiController;
	UPROPERTY()
		class UBlackboardComponent* blackboard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess))
	UStaticMeshComponent* attackColission;

	float flightHeight;

	UFUNCTION()
	void Reset_BlackboardValue(EKeyRegister_Names _bbKey, bool _value);
	UFUNCTION()
	void Reset_MovementMode(EMovementMode _mmKey);

	TMap<EKeyRegister_Names, FTimerHandle> bbTimerHandles;
	TMap<EKeyRegister_Names, FTimerDelegate> bbTimerDelegates;

	TMap<EMovementMode, FTimerDelegate> mmTimerDelegates;
	TMap<EMovementMode, FTimerHandle> mmTimerHandles;
};