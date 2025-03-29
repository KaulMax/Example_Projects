// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceManager.h"

#include "Generator.h"
#include "MainDrill.h"
#include "WaveManager.h"
#include "TowerBase.h"
#include "Kismet/GameplayStatics.h"
#include <SpaceMine/Drill.h>

#include "SpaceMineGameInstance.h"
#include "WaveManager.h"

// Sets default values
AResourceManager::AResourceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mainDrillActive = true;

	CurrentNormalMineral = 250.f;
	TotalMinerals = CurrentNormalMineral;
	CurrentSpecialMineral = 150.f;

	NormalResourceWeight = 3.f;
	SpecialResourceWeight = 3.f;

	NormalResourceTickRate = 3.5f;
	SpecialResourceTickRate = 2.5f;

	CurrNormalTickRate = NormalResourceTickRate;
	CurrSpecialTickRate = SpecialResourceTickRate;
}

// Called when the game starts or when spawned
void AResourceManager::BeginPlay()
{
	Super::BeginPlay();

	AActor* drill = UGameplayStatics::GetActorOfClass(GetWorld(), Drill);
	WaveManager = Cast<AWaveManager>(UGameplayStatics::GetActorOfClass(GetWorld(), WaveSub));

	SpaceMineGameInstance = Cast<USpaceMineGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(drill)
	{
		MainDrill = Cast<AMainDrill>(drill);
		MainDrill->SubscribeManager(this);
	}
}

// Called every frame
void AResourceManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SpaceMineGameInstance)
		UE_LOG(LogTemp, Warning, TEXT("AResourceManager ,!GameInstance"));
	if (!WaveManager)
		UE_LOG(LogTemp, Warning, TEXT("AResourceManager ,!WaveManager"));

	switch (SpaceMineGameInstance->GameDifficulty)
	{
	case EGameDifficulty::GD_Easy:
		TickResources_Normal(DeltaTime);
		TickResources_Special(DeltaTime);
		break;
	case EGameDifficulty::GD_Normal:
		if(WaveManager->CurrentGamePhase == ECurrentGamePhase::CGP_Fight)
		{
			TickResources_Normal(DeltaTime);
			TickResources_Special(DeltaTime);
		}
		break;
	case EGameDifficulty::GD_Hard:
		if(WaveManager->CurrentGamePhase == ECurrentGamePhase::CGP_Fight)
		{
			TickResources_Normal(DeltaTime);
			TickResources_Special(DeltaTime);
		}
	case EGameDifficulty::GD_EmployeeOfTheMonth:
		if(WaveManager->CurrentGamePhase == ECurrentGamePhase::CGP_Fight)
			TickResources_Special(DeltaTime);
		break;

	case EGameDifficulty::GD_Default:
		break;
	}

}

void AResourceManager::SubscribeStructure(AEnemyTarget* _toAdd)
{
	if(Cast<AGenerator>(_toAdd))
	{
		if (!allGenerators.Contains(_toAdd))
			allGenerators.Add(_toAdd);
	}
	else if (Cast<ADrill>(_toAdd))
	{
		if (!allDrills.Contains(_toAdd))
			allDrills.Add(_toAdd);
	}
}

void AResourceManager::UnsubscribeStructure(AEnemyTarget* _toDelete)
{
	if (Cast<AGenerator>(_toDelete))
	{
		if (allGenerators.Contains(_toDelete))
			allGenerators.Add(_toDelete);
	}
	else if (Cast<ADrill>(_toDelete))
	{
		if (allDrills.Contains(_toDelete))
			allDrills.Add(_toDelete);
	}
}

void AResourceManager::SetMainDrillStatus(bool _status)
{
	mainDrillActive = _status;
}

void AResourceManager::TickResources_Normal(float DeltaTime)
{
	if (MainDrill && !MainDrill->bIsActive || MainDrill->bDrillComponentExtracted)
		return;

	if (mainDrillActive && CurrNormalTickRate <= 0)
	{
		AddNormalResources();
		CurrNormalTickRate = NormalResourceTickRate;
	}
	else if (CurrNormalTickRate > 0 )
		CurrNormalTickRate -= DeltaTime;
}

void AResourceManager::TickResources_Special(float DeltaTime)
{
	if (allDrills.Num() > 0 && CurrSpecialTickRate <= 0)
	{
		AddSpecialResources();
		CurrSpecialTickRate = SpecialResourceTickRate;
	}
	else if (CurrSpecialTickRate > 0)
		CurrSpecialTickRate -= DeltaTime;
}

void AResourceManager::DeductResources(float _normalCost, float _specialCost)
{
	if (SpaceMineGameInstance && SpaceMineGameInstance->bUnlimitedResources)
		return;

	CurrentNormalMineral -= _normalCost;
	CurrentSpecialMineral -= _specialCost;
}

bool AResourceManager::HasEnoughResources(float _normalCost, float _specialCost)
{
	if (SpaceMineGameInstance && SpaceMineGameInstance->bUnlimitedResources)
		return true;

	float tempResNormal = CurrentNormalMineral;
	float tempResSpecial = CurrentSpecialMineral;

	if ((tempResNormal -= _normalCost) >= 0 && (tempResSpecial -= _specialCost) >= 0)
	{
		return true;
	}
	else
		return false;
}

void AResourceManager::AddNormalResources()
{
	if(MainDrill->ActiveGeneratorAmount >= MainDrill->TotalGeneratorAmount)
	{
		TotalMinerals += NormalResourceWeight;
		CurrentNormalMineral += NormalResourceWeight;
	}
	else
	{
		TotalMinerals += (NormalResourceWeight / 2);
		CurrentNormalMineral += (NormalResourceWeight / 2);
	}
}

void AResourceManager::AddNormalResources(float _add)
{
	CurrentNormalMineral += _add;

	TotalMinerals += _add;
}

void AResourceManager::AddSpecialResources()
{
	for (int i = 0; i < allDrills.Num(); ++i)
	{
		CurrentSpecialMineral += SpecialResourceWeight;
	}
}

