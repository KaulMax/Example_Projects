// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllEnums.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


UCLASS()
class SPACEMINE_API AWeapon : public AActor
{
	GENERATED_BODY()

public:	
	AWeapon();

	UFUNCTION()
	virtual void AttackBoxOnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()	 
	virtual void AttackBoxOnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex);

protected:
	virtual void BeginPlay() override;

	void Attack(float _dt);
	void Attack();

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY()
	AActor* CurrentTarget;

	/// <summary>
	/// Virtual Public Methods
	/// </summary>

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class AEnemyTarget* AttackFollowTarget;

	/// <summary>
	/// Normal Public Methods
	/// </summary>
public:

	UFUNCTION()
	void ActivateAttackSFX();

	/// <summary>
	/// Collision Methods
	/// </summary>


	/// <summary>
	/// FORCEINLINE Public Methods
	/// </summary>


	/// <summary>
	/// Public Variables
	/// </summary>

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status)
	//bool bCanMakeDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	bool bHasKnockback;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	float KnockbackForce;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status)
	float WeaponCooldown;
	/// <summary>
	/// Public Components
	/// </summary>

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class AMainEnemy* WeaponOwner;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UBoxComponent* WeaponHitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* AttackParticleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool targetSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool debugOverlapped;

	/// <summary>
	/// Public SFX and Audio Component Placeholder
	/// </summary>
};
