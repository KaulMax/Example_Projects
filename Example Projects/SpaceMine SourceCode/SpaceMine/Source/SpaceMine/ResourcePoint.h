// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourcePoint.generated.h"

UCLASS()
class SPACEMINE_API AResourcePoint : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status, meta = (AllowPrivateAccess="true"))
	USkeletalMeshComponent* skeletalMesh;

	virtual void BeginPlay() override;

public:	
	AResourcePoint();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Status)
	bool bIsEmpty;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Infos)
	FVector Position;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Infos)
	FRotator Rotation;
};
