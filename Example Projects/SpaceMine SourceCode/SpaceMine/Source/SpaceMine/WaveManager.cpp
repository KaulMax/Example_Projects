// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"
#include "DialogManager.h"
#include "EnemySpawner.h"
#include "GameManager.h"
#include "MainDrill.h"
#include "SpaceMineCharacter.h"
#include "SpaceMineGameInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWaveManager::AWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WaveSpawnModifier = 2.5f;
	CurrentWave = 0;

	//WaveCounterText = CreateDefaultSubobject<UTextRenderComponent>("WaveCounterText");
	//WaveCounterText->SetupAttachment(RootComponent);

	//DialogManager->SetupAttachment(RootComponent);

	CurrentGamePhase = ECurrentGamePhase::CGP_Build;

	PhaseTime = 60.f;
	MaxWaveCount = 6;
	EndOfGameTime = 30.f;
}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	MainCharacter = Cast<ASpaceMineCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	SpaceMineGameInstance = Cast<USpaceMineGameInstance>(GetGameInstance());

	if (SpaceMineGameInstance)
		CurrentWave = SpaceMineGameInstance->StartWave - 1;
	else
		UE_LOG(LogTemp,Warning,TEXT("AWaveManager, !GameInstance"))

	if(DialogManagerSub)
	{
		DialogManager = GetWorld()->SpawnActor<ADialogManager>(DialogManagerSub, FVector(0), FRotator(0));
		if(GameManager)
			DialogManager->InitDialogManager(MainCharacter,this, GameManager, Cast<AMainDrill>(GameManager->MainDrill));
	}

	if (AllSpawner.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Spawner Assigned to the Wave Manager"));
		return;
	}


	for (size_t i = 0; i < AllSpawner.Num(); i++)
	{
		AllSpawner[i]->SetManager(this, GameManager, MainCharacter);
		RegisterEmptySpawn();
	}
}

// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWaveManager::SpawnWave()
{
	if (CurrentWave > MaxWaveCount)
		return;

	if (CurrentGamePhase != ECurrentGamePhase::CGP_Fight)
		CurrentGamePhase = ECurrentGamePhase::CGP_Fight;

	bAllSpawnerEmpty = false;
	bIsSpawning = true;

	if (CurrentWave == 1)
	{
		AllSpawner[0]->bClearedForSpawning = true;
	}
	else if(CurrentWave == 2)
	{
		AllSpawner[0]->bClearedForSpawning = true;
		AllSpawner[1]->bClearedForSpawning = true;
	}
	else if (CurrentWave == 3)
	{
		AllSpawner[0]->bClearedForSpawning = true;
		AllSpawner[1]->bClearedForSpawning = true;
		AllSpawner[2]->bClearedForSpawning = true;
	}
	else
	{
		for (size_t i = 0; i < AllSpawner.Num(); i++)
		{
			AllSpawner[i]->bClearedForSpawning = true;
		}
	}
}

void AWaveManager::SetupWave()
{
	if(CurrentWave < MaxWaveCount)
		PhaseTime = SpawnTypeAmountTimePair.Find(CurrentWave)->spawnTime;

	if(SpaceMineGameInstance->GameDifficulty == EGameDifficulty::GD_Easy)
	{
		SpawnTypeAmountTimePair.FindOrAdd(CurrentWave).typeAmountPair.Emplace(EEnemyType::ET_Normal) = SpawnTypeAmountTimePair.FindOrAdd(CurrentWave).typeAmountPair.FindRef(EEnemyType::ET_Normal) / 2.5f;
		SpawnTypeAmountTimePair.FindOrAdd(CurrentWave).typeAmountPair.Emplace(EEnemyType::ET_Crystal) = SpawnTypeAmountTimePair.FindOrAdd(CurrentWave).typeAmountPair.FindRef(EEnemyType::ET_Crystal) / 2.5f;
	}

	if (CurrentWave == 1)
	{
		if(SpaceMineGameInstance && SpaceMineGameInstance->FirstPhaseMod)
			PhaseTime *= 2;

		EmptySpawner -= 1;
		AllSpawner[0]->bClearedForSpawning = false;
		AllSpawner[0]->SetSpawnAmount(SpawnTypeAmountTimePair.FindOrAdd(CurrentWave).typeAmountPair);
	}
	else if (CurrentWave == 2)
	{
		EmptySpawner -= 2;
		AllSpawner[0]->bClearedForSpawning = false;
		AllSpawner[1]->bClearedForSpawning = false;
		AllSpawner[0]->SetSpawnAmount(SpawnTypeAmountTimePair.FindOrAdd(CurrentWave).typeAmountPair);
		AllSpawner[1]->SetSpawnAmount(SpawnTypeAmountTimePair.FindOrAdd(CurrentWave).typeAmountPair);
	}
	else if (CurrentWave == 3)
	{
		EmptySpawner -= 3;
		AllSpawner[0]->bClearedForSpawning = false;
		AllSpawner[1]->bClearedForSpawning = false;
		AllSpawner[2]->bClearedForSpawning = false;
		AllSpawner[0]->SetSpawnAmount(SpawnTypeAmountTimePair.FindOrAdd(CurrentWave).typeAmountPair);
		AllSpawner[1]->SetSpawnAmount(SpawnTypeAmountTimePair.FindOrAdd(CurrentWave).typeAmountPair);
		AllSpawner[2]->SetSpawnAmount(SpawnTypeAmountTimePair.FindOrAdd(CurrentWave).typeAmountPair);
	}
	else
	{
		EmptySpawner = 0;

		for (size_t i = 0; i < AllSpawner.Num(); i++)
		{
			AllSpawner[i]->bClearedForSpawning = false;
			AllSpawner[i]->SetSpawnAmount(SpawnTypeAmountTimePair.FindOrAdd(CurrentWave).typeAmountPair);
		}
	}
}

void AWaveManager::RegisterEmptySpawn()
{
	EmptySpawner++;

	if (EmptySpawner >= AllSpawner.Num())
	{
		bAllSpawnerEmpty = true;
		bIsSpawning = false;

		if (CurrentGamePhase != ECurrentGamePhase::CGP_Build)
			CurrentGamePhase = ECurrentGamePhase::CGP_Build;

		CurrentWave++;

		if(CurrentWave < MaxWaveCount)
			SetupWave();
		else if (CurrentWave >= MaxWaveCount)
			PhaseTime = EndOfGameTime;
	}
}

void AWaveManager::SetEnemyAmountInfo(int _enemyOne, int _enemyTwo)
{
	CurrentEnemyCount_One = _enemyOne;
	CurrentEnemyCount_Two = _enemyTwo;
}
