// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator.h"
#include "MainDrill.h"

#include "ResourceManager.h"
#include "SpaceMineGameInstance.h"
#include "TowerAnimInstance.h"
#include "Kismet/GameplayStatics.h"

AGenerator::AGenerator()
{
	bIsActivated = true;
}

void AGenerator::CleanAfterDeath()
{
	Super::CleanAfterDeath();

	if (MainDrill)
		MainDrill->UnsubGenerator(this, bIsActivated);
}

void AGenerator::BeginPlay()
{
	Super::BeginPlay();

	SpaceMineGameInstance = Cast<USpaceMineGameInstance>(GetGameInstance());
}

void AGenerator::SubResourceManager(AResourceManager* _resourceManager, AMainDrill* _mainDrill)
{
	ResourceManager = _resourceManager;
	MainDrill = _mainDrill;
}

void AGenerator::ToggleActiveStatus()
{
	if(bIsActivated)
	{
		MainDrill->ChangeActiveGenerators(true);
		bIsActivated = false;
		Cast<UTowerAnimInstance>(SkeletalMeshComponent->GetAnimInstance())->bCanUpdate = false;
	}
	else if(!bIsActivated)
	{
		MainDrill->ChangeActiveGenerators(false);
		bIsActivated = true;
		Cast<UTowerAnimInstance>(SkeletalMeshComponent->GetAnimInstance())->bCanUpdate = true;
	}
}