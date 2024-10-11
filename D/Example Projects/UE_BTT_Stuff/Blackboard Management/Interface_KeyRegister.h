// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnumDirectory.h"
#include "Interface_KeyRegister.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_KeyRegister : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IInterface_KeyRegister
{
	GENERATED_BODY()

private:
	TMap<int, FName> keyValueMap;

public:
	IInterface_KeyRegister();

	virtual FName GetKeyName(EKeyRegister_Names _key);
};
