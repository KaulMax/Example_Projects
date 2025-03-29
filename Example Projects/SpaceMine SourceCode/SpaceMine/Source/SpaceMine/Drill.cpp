// Fill out your copyright notice in the Description page of Project Settings.


#include "Drill.h"
#include "ResourceManager.h"

ADrill::ADrill()
{
}

void ADrill::BeginPlay()
{
	Super::BeginPlay();
}

void ADrill::InitStructure(AResourceManager* _manager, class AResourcePoint* _resoucePoint )
{
	Super::InitStructure(_manager, _resoucePoint);

	ResourceManager->SubscribeStructure(this);
}

void ADrill::Tick(float _deltatime)
{
	Super::Tick(_deltatime);

	if (EnvyMontage && AnimInstance && !AnimInstance->Montage_IsPlaying(EnvyMontage))
	{
		AnimInstance->Montage_Play(EnvyMontage, 1.f);
		AnimInstance->Montage_JumpToSection(FName("EnvyAnim"), EnvyMontage);
	}
}

void ADrill::CleanAfterDeath()
{
	Super::CleanAfterDeath();

	ResourceManager->UnsubscribeStructure(this);
}
