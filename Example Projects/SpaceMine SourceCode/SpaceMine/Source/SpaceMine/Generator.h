// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyTarget.h"
#include "Generator.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMINE_API AGenerator : public AEnemyTarget
{
	GENERATED_BODY()

	AGenerator();

protected:
	virtual void CleanAfterDeath() override;
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Managment)
	class AMainDrill* MainDrill;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Managment)
		class USpaceMineGameInstance* SpaceMineGameInstance;


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BuildingInfo)
		bool bIsActivated;

	UFUNCTION()
	void SubResourceManager(class AResourceManager* _resourceManager, AMainDrill* _mainDrill);

	UFUNCTION()
		void ToggleActiveStatus();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BuildingInfo)
	int GeneratorID;
};
