// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "CustomPlayerStart.h"
#include "SpaceMineCharacter.h"
#include "WaveManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bGameOver = false;
	bEnoughResources = false;
}

void AGameManager::GameWon(bool _status)
{
	bEnoughResources = _status;
}

bool AGameManager::GetMainDrillDead()
{
	return bGameOver;
}

void AGameManager::SetPlayerIsDead(bool _status)
{
	if(_status)
		bTotalDeathCount++;

	bPlayerIsDead = _status;
}

void AGameManager::SetGameWon()
{
	if (CustomPlayerStart && !CustomPlayerStart->GetSpectatorSpawned())
		CustomPlayerStart->SpawnSpectator(false);
}

void AGameManager::SetGameLost()
{
	if (CustomPlayerStart && !CustomPlayerStart->GetSpectatorSpawned())
		CustomPlayerStart->SpawnSpectator(false);


	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);
	bGameOver = true;
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerStart)
		CustomPlayerStart = Cast<ACustomPlayerStart>(PlayerStart);

	MainCharacter = Cast<ASpaceMineCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bGameOver)
		return;

	if(MainCharacter && !WaveManager)
		WaveManager = MainCharacter->WaveManager;

	if (WaveManager && MainDrill && MainDrill->bHasDied || WaveManager->CurrentWave > WaveManager->MaxWaveCount &&
		WaveManager->CurrentGamePhase == ECurrentGamePhase::CGP_Fight || WaveManager->RanOutOfEndTime)
		SetGameLost();

	else if(bEnoughResources)
		SetGameWon();
}

