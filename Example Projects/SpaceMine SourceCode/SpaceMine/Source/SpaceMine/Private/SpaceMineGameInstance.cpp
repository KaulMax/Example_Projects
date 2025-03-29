// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceMineGameInstance.h"

#include <string>

#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"

USpaceMineGameInstance::USpaceMineGameInstance()
{
	 VCA_Volume_Master = 1.f;
	 VCA_Volume_SFX = 1.f;
	 VCA_Volume_Dialogue = 1.f;
	 VCA_Volume_Music = 1.f;

	 VCA_Volume_Master_Slider = 1.f;
	 VCA_Volume_SFX_Slider = 1.f;
	 VCA_Volume_Dialogue_Slider = 1.f;
	 VCA_Volume_Music_Slider = 1.f;

	 GameFOV = 90.f;
	 GameFOV_Slider = 90.f;
	 GameMouseSens = 45.f;
	 GameMouseSens_Slider = 45.f;

	 bUnlimitedResources = false;
	 GodMode = false;
	 FirstPhaseMod = false;

	 StartWave = 1;
	 MaxWaves = 6;

	 GameDifficulty = EGameDifficulty::GD_Easy;

	 Resolution = FIntPoint(1920, 1080);
}