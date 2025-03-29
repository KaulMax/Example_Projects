// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerStart.h"

#include "GameManager.h"
#include "PlayerSpectator.h"
#include "SpaceMineCharacter.h"
#include "Kismet/GameplayStatics.h"


void ACustomPlayerStart::RespawnPlayer()
{
	if (!bCanRespawn)
		return;

	bSpawnedSpectator = false;
	bCanRespawn = false;

	MainCharacter = GetWorld()->SpawnActor<ASpaceMineCharacter>(PlayerClass, this->GetActorLocation(), this->GetActorRotation());

	if (MainCharacter)
		MainCharacter->ReceivePossessed(GetWorld()->GetFirstPlayerController());

	if (GameManager)
		GameManager->SetPlayerIsDead(false);

	if(PlayerSpectator)
		PlayerSpectator->Destroy();
}

void ACustomPlayerStart::SpawnSpectator(bool _canRespawn)
{
	if (bSpawnedSpectator)
		return;

	if (MainCharacter)
		MainCharacter->CleanAfterDeath();

	if (!_canRespawn)
		return;

	bSpawnedSpectator = true;

	PlayerSpectator = GetWorld()->SpawnActor<APlayerSpectator>(PlayerSpectatorClass, MainCharacter->GetActorLocation() + SpectatorPosOffset,	MainCharacter->GetActorRotation() + SpectatorRotOffset);
	if(PlayerSpectator)
	{
		PlayerSpectator->ReceivePossessed(GetWorld()->GetFirstPlayerController());
		PlayerSpectator->InitPlayerSpectator(GameManager);
	}

	if(GameManager)
		GameManager->SetPlayerIsDead(true);

	bCanRespawn = _canRespawn;
}

void ACustomPlayerStart::BeginPlay()
{
	Super::BeginPlay();

	bSpawnedSpectator = false;

	PrimaryActorTick.bCanEverTick = true;

	PlayerRespawnTime = 5.f;

	MainCharacter = Cast<ASpaceMineCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}