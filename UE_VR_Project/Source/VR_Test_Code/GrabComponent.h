// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GrabComponent.generated.h"


UENUM(BlueprintType, Blueprintable)
enum class EGrabType
{
	GT_DEFAULT,
	GT_Free,
	GT_Snap,
	GT_ENTRY_AMOUNT
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR_TEST_CODE_API UGrabComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UGrabComponent();

	UFUNCTION()
	void InitGrabComponent(AActor* _compParent);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION()
	bool TryGrabObject(AActor* _grabHolder, class UMotionControllerComponent* _grabController);
	UFUNCTION()
	bool TryReleaseObject();

	FORCEINLINE
		bool GetIsBeignHeld() { return bIsBeingHeld; }

private:
	UPROPERTY(EditAnywhere, Category = ObjectInfo, meta = (AllowPrivateAccess))
		EGrabType grabType;

	UPROPERTY(EditAnywhere, Category = ObjectInfo, meta = (AllowPrivateAccess))
		bool bIsBeingHeld;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess))
	AActor* currHolder;
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess))
	UMotionControllerComponent* currController;
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess))
	AActor* compParent;
};
