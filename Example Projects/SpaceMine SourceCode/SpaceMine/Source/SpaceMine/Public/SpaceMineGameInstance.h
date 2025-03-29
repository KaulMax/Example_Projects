// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SpaceMine/AllEnums.h"
#include "SpaceMineGameInstance.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FHighscoreItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName PlayerName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TotalMinerals;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DeathCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGameDifficulty Difficulty;
};


UCLASS(config = Game, transient, BlueprintType, Blueprintable)
class SPACEMINE_API USpaceMineGameInstance : public UGameInstance
{
	GENERATED_BODY()

	USpaceMineGameInstance();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
		float VCA_Volume_Master;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
		float VCA_Volume_SFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
		float VCA_Volume_Dialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Audio)
		float VCA_Volume_Music;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Slider")
		float VCA_Volume_Master_Slider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Slider")
		float VCA_Volume_SFX_Slider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Slider")
		float VCA_Volume_Dialogue_Slider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Slider")
		float VCA_Volume_Music_Slider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conf)
		float GameFOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conf)
		float GameMouseSens;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conf Slider")
		float GameFOV_Slider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conf Slider")
		float GameMouseSens_Slider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conf)
		bool bUnlimitedResources;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conf)
		bool GodMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conf)
		bool FirstPhaseMod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conf)
		int StartWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conf)
		int MaxWaves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conf)
		EGameDifficulty GameDifficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conf)
		FIntPoint Resolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Conf)
		TArray<FHighscoreItem> HighscoreItems;
};
