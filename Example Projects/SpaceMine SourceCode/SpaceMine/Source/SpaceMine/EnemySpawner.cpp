// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include <string>
#include "MainEnemy.h"
#include "WaveManager.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/BillboardComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	thisSpawner = this;
	SpawnDelay = 2.f;

	Amount_1 = 0;
	Amount_2 = 0;

	//bVolumeIsFree = true;
	//OverlapNum = 0;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;


	EnemyOneBillboard = CreateDefaultSubobject<UBillboardComponent>("EnemyOneBillboard");
	EnemyOneBillboard->SetupAttachment(RootComponent);

	EnemyTwoBillboard = CreateDefaultSubobject<UBillboardComponent>("EnemyTwoBillboard");
	EnemyTwoBillboard->SetupAttachment(RootComponent);

	EnemyOneAmountText = CreateDefaultSubobject<UTextRenderComponent>("EnemyOneAmountText");
	EnemyOneAmountText->SetupAttachment(RootComponent);
	
	EnemyTwoAmountText = CreateDefaultSubobject<UTextRenderComponent>("EnemyTwoAmountText");
	EnemyTwoAmountText->SetupAttachment(RootComponent);
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnPos = GetActorLocation();
	SpawnRot = GetActorRotation();
	World = GetWorld();

	FLatentActionInfo lInfo;

	UKismetSystemLibrary::Delay(World, 0.5f, lInfo);
}


// Called every frame
void AEnemySpawner::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (Amount_1 + Amount_2 <= 0 || EnemiesToSpawn == SpawnedAmount)
		bClearedForSpawning = false;

	ManageText();
}

void AEnemySpawner::SpawnEnemyByType(TSubclassOf<AMainEnemy> _currentSpawnEnemy, bool _bridgeDebug)
{
	AMainEnemy* spawnEnemy = NewObject<AMainEnemy>(_currentSpawnEnemy);
	spawnEnemy->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	spawnEnemy = World->SpawnActor<AMainEnemy>(_currentSpawnEnemy, SpawnPos, SpawnRot);

	if(spawnEnemy)
		spawnEnemy->SetSpawnStats(GameManager, this, _bridgeDebug);
	else if (!spawnEnemy)
		return;

	if (spawnEnemy->EnemyType == EEnemyType::ET_Normal)
		Amount_1--;
	else if(spawnEnemy->EnemyType == EEnemyType::ET_Crystal)
		Amount_2--;

	SpawnedAmount++;

	if (Amount_1 + Amount_2 <= 0 || EnemiesToSpawn == SpawnedAmount)
		bClearedForSpawning = false;
}

void AEnemySpawner::ManageText()
{
	FRotator textRot = UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraRotation();

	textRot.Pitch *= -1.f;

	if(Amount_1 <= 0)
	{
		EnemyOneAmountText->SetHiddenInGame(true);
		EnemyOneBillboard->SetHiddenInGame(true);
	}
	else if(Amount_1 > 0)
	{
		EnemyOneAmountText->SetHiddenInGame(false);
		EnemyOneBillboard->SetHiddenInGame(false);

		EnemyOneAmountText->SetRelativeRotation(textRot);
		FText amountInfoOne = FText::FromString(FString::FromInt(Amount_1));
		EnemyOneAmountText->SetText(amountInfoOne);
	}

	if(Amount_2 <= 0)
	{
		EnemyTwoBillboard->SetHiddenInGame(true);
		EnemyTwoAmountText->SetHiddenInGame(true);
	}
	else if (Amount_2 > 0)
	{
		EnemyTwoBillboard->SetHiddenInGame(false);
		EnemyTwoAmountText->SetHiddenInGame(false);

		EnemyTwoAmountText->SetRelativeRotation(textRot);
		FText amountInfoTwo = FText::FromString(FString::FromInt(Amount_2));
		EnemyTwoAmountText->SetText(amountInfoTwo);
	}
}

void AEnemySpawner::SetManager(AWaveManager* _waveManager, AGameManager* _gameManager, ASpaceMineCharacter* _character)
{
	if (!_waveManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawner has not Wave Manager!"));
		return;
	}
	if (!_gameManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawner has not Wave GameManager!"));
		return;
	}
	if (!_character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawner has not Wave Character!"));
		return;
	}

	WaveManager = _waveManager;
	GameManager = _gameManager;
}

void AEnemySpawner::SetSpawnAmount(TMap<EEnemyType, int> _spawnTypeAmountPair)
{
	SpawnedAmount = 0;

	SpawnTypeAmountPair = _spawnTypeAmountPair;

	for(TTuple<EEnemyType, int> key : _spawnTypeAmountPair)
	{
		switch (key.Key)
		{
		case EEnemyType::ET_Normal:
			Amount_1 = key.Value;
				break;

		case EEnemyType::ET_Crystal:
			Amount_2 = key.Value;
			break;
		}
	}

	WaveManager->SetEnemyAmountInfo(Amount_1, Amount_2);

	EnemiesToSpawn = Amount_1 + Amount_2;
}

void AEnemySpawner::AddToClean(AMainEnemy* _toClean)
{
	ToCleanAmount++;

	WaveManager->SetEnemyAmountInfo(Amount_1, Amount_2);

	if (ToCleanAmount >= SpawnedAmount && Amount_1 <= 0 && Amount_2 <= 0) 
	{
		WaveManager->RegisterEmptySpawn();
		ToCleanAmount = 0;
	}
}