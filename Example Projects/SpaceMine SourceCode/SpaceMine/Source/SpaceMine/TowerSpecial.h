// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "TowerSpecial.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMINE_API ATowerSpecial : public ATowerBase
{
	GENERATED_BODY()

	/// <summary>
	/// Virtual Public Methods
	/// </summary>
public:

	virtual void Attack() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void PlayDeath() override;

	ATowerSpecial();

	/// <summary>
	/// Normal Public Methods
	/// </summary>

	UFUNCTION()
	virtual void DamageBoxOnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()
	virtual void DamageBoxOnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void CleanDamageEnemies();

	/// <summary>
	/// Collision Methods
	/// </summary>


	/// <summary>
	/// FORCEINLINE Public Methods
	/// </summary>


	/// <summary>
	/// Public Variables
	/// </summary>

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps)
	UBoxComponent* DamageExtendBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	bool bEnemyInDamageRange;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	//bool bMadeAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Comps)
	float AttackInterval;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Target)
	TArray<AMainEnemy*> DamageEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Target)
	TArray<AMainEnemy*> DamageEnemiesToClean;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	//float ProjectileSpeed;

	/// <summary>
	/// Public Components
	/// </summary>


	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//TSubclassOf<>* GunPoint;

	/// <summary>
	/// Public SFX and Audio Component Placeholder
	/// </summary>
};
