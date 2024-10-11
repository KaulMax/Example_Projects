// Copyright Epic Games, Inc. All Rights Reserved.

#include "VR_Test_CodeGameMode.h"
#include "VR_Test_CodeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVR_Test_CodeGameMode::AVR_Test_CodeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
