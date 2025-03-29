// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpaceMineGameMode.h"
#include "SpaceMineCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpaceMineGameMode::ASpaceMineGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonContent/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}