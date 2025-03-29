// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "TowerNormal.generated.h"

/**
 * DEPRECATED
 */
UCLASS()
class SPACEMINE_API ATowerNormal : public ATowerBase
{
	GENERATED_BODY()

	/// <summary>
	/// Virtual Public Methods
	/// </summary>
public:

	virtual void Attack() override;
	virtual void Tick(float _dt) override;
	virtual void BeginPlay() override;

	ATowerNormal();

	/// <summary>
	/// Normal Public Methods
	/// </summary>


	/// <summary>
	/// Collision Methods
	/// </summary>


	/// <summary>
	/// FORCEINLINE Public Methods
	/// </summary>


	/// <summary>
	/// Public Variables
	/// </summary>

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Comps)
	TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float ProjectileSpeed;

	int test;

	UPROPERTY()
	FLatentActionInfo linfo;

	/// <summary>
	/// Public Components
	/// </summary>


	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//TSubclassOf<>* GunPoint;

	/// <summary>
	/// Public SFX and Audio Component Placeholder
	/// </summary>
};
