// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "CustomPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMINE_API ACustomPlayerStart : public APlayerStart
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	void RespawnPlayer();
	UFUNCTION(BlueprintCallable)
	void SpawnSpectator(bool _canRespawn);

	FORCEINLINE
	bool GetSpectatorSpawned() { return bSpawnedSpectator; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	bool bRespawnTicks;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	float PlayerRespawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	bool bCanRespawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	FVector SpectatorPosOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	FRotator SpectatorRotOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	bool bSpawnedSpectator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	class ASpaceMineCharacter* MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	class APlayerSpectator* PlayerSpectator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	class AGameManager* GameManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	TSubclassOf<ASpaceMineCharacter> PlayerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	TSubclassOf<APlayerSpectator> PlayerSpectatorClass;
};
