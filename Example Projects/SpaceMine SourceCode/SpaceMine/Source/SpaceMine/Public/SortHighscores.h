// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceMineGameInstance.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SortHighscores.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMINE_API USortHighscores : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:
    UFUNCTION(BlueprintCallable, Category = "Sort Highscores")                                                               
        static void  Sort(UPARAM(ref) TArray <FHighscoreItem>& _highscoresToSort, TArray <FHighscoreItem>& _sortedHighscores);
};