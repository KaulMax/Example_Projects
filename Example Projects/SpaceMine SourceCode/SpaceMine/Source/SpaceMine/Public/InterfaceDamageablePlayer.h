// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfaceDamageablePlayer.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfaceDamageablePlayer : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPACEMINE_API IInterfaceDamageablePlayer
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual void I_TakeDamage(float _damage, class AMainEnemy* _ref);

	UFUNCTION()
	virtual void I_ApplyKnockback(FVector _launchVelo, bool _bXYOverride, bool __bZOverride);
};
