// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class SPACEMINE_API AGameManager : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	class ACustomPlayerStart* CustomPlayerStart;

public:	

	virtual void Tick(float DeltaTime) override;

	
	/// <summary>
	/// Normal Public Methods
	/// </summary>
	
	AGameManager();
	
	/// <summary>
	/// Collision Methods
	/// </summary>
	
	
	/// <summary>
	/// FORCEINLINE Public Methods
	/// </summary>


	/// <summary>
	/// Public Variables
	/// </summary>

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MainDrill)
	class AEnemyTarget* MainDrill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	class ASpaceMineCharacter* MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	class APlayerStart* PlayerStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	class AWaveManager* WaveManager;

	UFUNCTION()
	void GameWon(bool _status);
	
	UFUNCTION()
	bool GetMainDrillDead();

	UFUNCTION()
	void SetPlayerIsDead(bool _status);

	UFUNCTION()
	void SetGameWon();

	UFUNCTION()
	void SetGameLost();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerInfo)
		int bTotalDeathCount;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameStatusInfo)
	bool bGameOver;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameStatusInfo)
	bool bStageWon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameStatusInfo)
	bool bPlayerIsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameStatusInfo)
	bool bEnoughResources;

	/// <summary>
	/// Public Components
	/// </summary>
	
	
	/// <summary>
	/// Public SFX and Audio Component Placeholder
	/// </summary>
};
