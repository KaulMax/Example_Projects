// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrabObjectBase.generated.h"

UCLASS()
class VR_TEST_CODE_API AGrabObjectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AGrabObjectBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = GrabInfo, meta =(AllowPrivateAccess))
	class UGrabComponent* grabComponent;

	UPROPERTY(EditAnywhere, Category = GrabInfo, meta =(AllowPrivateAccess))
	UStaticMeshComponent* objectMesh;

public:
	FORCEINLINE
		class UGrabComponent* GetGrabComponent() { return grabComponent; };
};
