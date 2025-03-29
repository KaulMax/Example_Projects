// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy_Controller.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMINE_API AEnemy_Controller : public AAIController
{
	GENERATED_BODY()

public:
		AEnemy_Controller(const FObjectInitializer& ObjectInitializer);
};
