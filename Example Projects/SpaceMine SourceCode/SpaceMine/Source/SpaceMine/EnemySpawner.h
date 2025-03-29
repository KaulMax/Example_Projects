// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllEnums.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class SPACEMINE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
public:

	AEnemySpawner();

	UFUNCTION(BlueprintCallable)
	void SpawnEnemyByType(TSubclassOf<class AMainEnemy> _currentEnemySpawn, bool _bridgeDebug);

	UFUNCTION()
	void ManageText();

	UFUNCTION()
	void SetManager(class AWaveManager* _waveManager, class AGameManager* _gameManager, class ASpaceMineCharacter* _character);

	UFUNCTION()
	void AddToClean(class AMainEnemy* _toClean);

	UFUNCTION()
	void SetSpawnAmount(TMap<EEnemyType, int> _spawnTypeAmountPair);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int RndIdx() { return FMath::RandRange(0, 1); };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemySpawning)
	FVector SpawnPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemySpawning)
	FRotator SpawnRot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemySpawning)
	float SpawnDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemySpawning)
	int EnemiesToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemySpawning)
	int SpawnedAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemySpawning)
	bool bClearedForSpawning;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemySpawning)
	TMap<EEnemyType, int> SpawnTypeAmountPair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemySpawning)
	int Amount_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemySpawning)
	int Amount_2;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = EnemySpawning)
	int ToCleanAmount;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = EnemySpawning)
	class AWaveManager* WaveManager;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = EnemySpawning)
	AEnemySpawner* thisSpawner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemySpawning)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemySpawningInfo)
	class UTextRenderComponent* EnemyOneAmountText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemySpawningInfo)
	UTextRenderComponent* EnemyTwoAmountText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemySpawningInfo)
	class UBillboardComponent* EnemyOneBillboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemySpawningInfo)
	UBillboardComponent* EnemyTwoBillboard;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = EnemySpawning)
	AGameManager* GameManager;

	UPROPERTY(BlueprintReadOnly, Category = EnemySpawning)
	UWorld* World;
};
