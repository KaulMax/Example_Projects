// Fill out your copyright notice in the Description page of Project Settings.


#include "MainDrill.h"

#include "GameManager.h"
#include "Generator.h"
#include "ResourceManager.h"
#include "SpaceMineGameInstance.h"
#include "WaveManager.h"

AMainDrill::AMainDrill()
{
	ResourceManager = nullptr;
	ResourceAmountToWin = 100;
	CurrentResourceAmount = 0;

	bIsActive = true;
	bDrillComponentExtracted = false;

	HardModeDamage = 10.f;

	MaxTimeTillFirstTick = 3.5f;
	CurrTimeTillFirstTick = MaxTimeTillFirstTick;

	MaxDamageTick = 1.f;
	CurrDamageTick = MaxDamageTick;
}

void AMainDrill::BeginPlay()
{
	Super::BeginPlay();

	TotalGeneratorAmount = allGenerators.Num();
	ActiveGeneratorAmount = TotalGeneratorAmount;

	SpaceMineGameInstance = Cast<USpaceMineGameInstance>(GetGameInstance());
}

void AMainDrill::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ResourceManager && allGenerators.Num() <= 0)
		ResourceManager->SetMainDrillStatus(false);

	if (EnvyMontage && AnimInstance && !AnimInstance->Montage_IsPlaying(EnvyMontage))
	{
		AnimInstance->Montage_Play(EnvyMontage, 1.f);
		AnimInstance->Montage_JumpToSection(FName("EnvyAnim"), EnvyMontage);
	}

	if (ActiveGeneratorAmount > 0 && !bIsActive)
		bIsActive = true;
	else if (ActiveGeneratorAmount <= 0 && bIsActive)
		bIsActive = false;

	if (!GameManager->WaveManager || !SpaceMineGameInstance)
		return;

	if(SpaceMineGameInstance->GameDifficulty != EGameDifficulty::GD_Hard)
		return;

	if (GameManager->WaveManager->CurrentGamePhase == ECurrentGamePhase::CGP_Fight && bDrillComponentExtracted)
	{
		if (bDrillComponentExtracted && bAllGeneratorsDestroyed || ActiveGeneratorAmount <= 0)
			return;

		if (CurrTimeTillFirstTick <= 0)
		{
			if (CurrDamageTick <= 0.f)
			{
				I_TakeDamage(HardModeDamage, nullptr);
				CurrDamageTick = MaxDamageTick;
			}
			else
				CurrDamageTick -= DeltaSeconds;
		}
		else
			CurrTimeTillFirstTick -= DeltaSeconds;
	}
	else if (CurrTimeTillFirstTick < MaxTimeTillFirstTick)
		CurrTimeTillFirstTick = MaxTimeTillFirstTick;

	if(GameManager->WaveManager->CurrentGamePhase == ECurrentGamePhase::CGP_Build)
	{
		if (allGenerators.Num() <= 0)
			return;

		for(AGenerator* gen : allGenerators)
		{
			if (gen->bIsActivated)
				gen->ToggleActiveStatus();
		}
	}
}

void AMainDrill::SubscribeManager(AResourceManager* _manager)
{
	if (_manager)
		ResourceManager = _manager;
	else
		return;

	for (size_t i = 0; i < allGenerators.Num(); i++)
	{
		allGenerators[i]->SubResourceManager(_manager, this);
	}
}

void AMainDrill::AddResourcesToStash(int _resourcesToAdd)
{
	CurrentResourceAmount += _resourcesToAdd;

	if (CurrentResourceAmount >= ResourceAmountToWin)
		GameManager->GameWon(true);
}

void AMainDrill::UnsubGenerator(AGenerator* _toUnsub, bool _activationStatus)
{
	if (allGenerators.Contains(_toUnsub))
	{
		allGenerators.Remove(_toUnsub);

		if(_activationStatus)
			ActiveGeneratorAmount--;

		if (allGenerators.Num() <= 0)
		{
			bAllGeneratorsDestroyed = true;
		}
	}
}

void AMainDrill::ChangeActiveGenerators(bool _decrement)
{
	if (_decrement)
		ActiveGeneratorAmount--;
	else if (!_decrement)
		ActiveGeneratorAmount++;
}
