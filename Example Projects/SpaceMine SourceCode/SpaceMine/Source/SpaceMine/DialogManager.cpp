// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogManager.h"

#include "SpaceMineCharacter.h"

// Sets default values
ADialogManager::ADialogManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADialogManager::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ADialogManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADialogManager::InitDialogManager(ASpaceMineCharacter* _mainCharacter, AWaveManager* _waveManager, AGameManager* _gameManager, AMainDrill* _mainDrill)
{
	WaveManager = _waveManager;
	GameManager = _gameManager;
	MainDrill = _mainDrill;
	MainCharacter = _mainCharacter;
}