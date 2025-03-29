// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "PlayerSpectator.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMINE_API APlayerSpectator : public ASpectatorPawn
{
	GENERATED_BODY()



public:
	UFUNCTION()
	void InitPlayerSpectator(class AGameManager* _gameManager);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Game)
	AGameManager* GameManager;
};
