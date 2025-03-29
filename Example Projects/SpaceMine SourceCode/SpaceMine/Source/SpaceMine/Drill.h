// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "Drill.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMINE_API ADrill : public ATowerBase
{
	GENERATED_BODY()

	ADrill();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float _deltatime) override;

	virtual void InitStructure(AResourceManager* _manager, class AResourcePoint* _resoucePoint ) override;

	virtual void CleanAfterDeath();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UAnimMontage* EnvyMontage;
};
