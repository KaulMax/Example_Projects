// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogManager.generated.h"

UCLASS()
class SPACEMINE_API ADialogManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ADialogManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DialogInfo)
	class AWaveManager* WaveManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DialogInfo)
	class AGameManager* GameManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DialogInfo)
	class AMainDrill* MainDrill;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DialogInfo)
	class ASpaceMineCharacter* MainCharacter;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void InitDialogManager(ASpaceMineCharacter* _mainCharacter, AWaveManager* _waveManager, AGameManager* _gameManager, AMainDrill* _mainDrill);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DialogInfo)
	bool bIsPlayingDialog;
};
