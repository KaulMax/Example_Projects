// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VRPlayer.generated.h"

UCLASS()
class VR_TEST_CODE_API AVRPlayer : public APawn
{
	GENERATED_BODY()

public:
	AVRPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	UFUNCTION()
	void SetupVRDepends();

	UFUNCTION()
	void Grab_RightHand();
	UFUNCTION()
	void Release_RightHand();
	UFUNCTION()
	void Walk();


	UFUNCTION()
	virtual void OnOverlapBegin_GrabRight(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()
	virtual void OnOverlapEnd_GrabRight(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess))
		class UInputMappingContext* defaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess))
		class UInputAction* grabAction_RightHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* firstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UWorld* world;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = VR, meta = (AllowPrivateAccess))
	USceneComponent* VRRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = VR, meta = (AllowPrivateAccess))
	class UMotionControllerComponent* motionController_RightHand;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = VR, meta = (AllowPrivateAccess))
	UMotionControllerComponent* motionController_LeftHand;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = VR, meta = (AllowPrivateAccess))
	UStaticMeshComponent* mesh_RightHand;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = VR, meta = (AllowPrivateAccess))
	UStaticMeshComponent* mesh_LeftHand;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess))
	class AGrabObjectBase* currOverlapActor;
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess))
	AGrabObjectBase* currGrabActor;

	UPROPERTY()
	class UHeadMountedDisplayFunctionLibrary* displayLib;
};
