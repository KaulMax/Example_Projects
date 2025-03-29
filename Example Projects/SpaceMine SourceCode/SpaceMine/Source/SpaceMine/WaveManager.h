// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllEnums.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"


USTRUCT(BlueprintType)
struct FTypeAmountTimePair
{
	GENERATED_BODY()

	FTypeAmountTimePair() {};

	//FTypeAmountPair(EEnemyType _enemyType, int _enemyAmount)
	//{
	//	//typeAmountPair.Add(_enemyType, _enemyAmount);
	//};

	UPROPERTY(EditAnywhere)
	TMap<EEnemyType, int> typeAmountPair;

	UPROPERTY(EditAnywhere)
	float spawnTime;
};

UCLASS()
class SPACEMINE_API AWaveManager : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	/// <summary>
	/// Virtual Public Methods
	/// </summary>

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void RegisterEmptySpawn();

	UFUNCTION(BlueprintCallable)
	void SpawnWave();
	UFUNCTION(BlueprintCallable)
	void SetupWave();

	UFUNCTION(BlueprintCallable)
	void SetEnemyAmountInfo(int _enemyOne, int _enemyTwo);

	AWaveManager();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SpawnManaging)
	ECurrentGamePhase CurrentGamePhase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerDialogInfo)
	class ADialogManager* DialogManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerDialogInfo)
	class USpaceMineGameInstance* SpaceMineGameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerDialogInfo)
	TSubclassOf<ADialogManager> DialogManagerSub;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=SpawnManaging)
	float WaveSpawnModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnManaging)
	bool SpawnWaveManual;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnManaging)
	bool RanOutOfEndTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	int MaxWaveCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnManaging)
	float PhaseTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnManaging)
	float EndOfGameTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnManaging)
	class AGameManager* GameManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnManaging)
	class ASpaceMineCharacter* MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnManaging)
	TMap<int, FTypeAmountTimePair> SpawnTypeAmountTimePair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnManaging)
	int CurrentWave;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpawnManaging)
	int EmptySpawner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpawnInfo)
	int CurrentEnemyCount_One;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SpawnInfo)
	int CurrentEnemyCount_Two;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnManaging)
	bool bAllSpawnerEmpty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnManaging)
	bool bIsSpawning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnManaging)
	bool bBuildSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnManaging)
	bool bSpawnerSetUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnManaging)
	TArray<class AEnemySpawner*> AllSpawner;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemySpawning)
	//class UTextRenderComponent* WaveCounterText;

	/// <summary>
	/// Public Components
	/// </summary>


	/// <summary>
	/// Public SFX and Audio Component Placeholder
	/// </summary>
};
