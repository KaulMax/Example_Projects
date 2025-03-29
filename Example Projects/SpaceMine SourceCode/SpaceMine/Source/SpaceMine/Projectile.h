// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllEnums.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class SPACEMINE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void Tick(float DeltaSeconds) override;

public:	
	void DestroyProjectile();


	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex);

	UFUNCTION()
	void OnOverlapBeginEnvi(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);

	UFUNCTION()
	void SetProjectileStats(float _damage, float _projectileSpeed, AActor* _targetActor, EDamageType _damageType, bool _followStatus, FVector _endPos, FVector _startPos, class ASpaceMineCharacter* _weaponOwner, bool _playerOwned);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float ProjectileSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float LifeTime;

	UPROPERTY()
		bool bDeathToggle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	bool bFollow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		bool bPlayerOwned;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	bool bHitTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	bool bIsInit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	bool bTargetHasDied;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status)
	class USphereComponent* HitBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Goal)
	class AMainEnemy* TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyComps)
		UMaterialInstance* TranslucentMat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comps)
	ASpaceMineCharacter* WeaponOwner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Goal)
	EDamageType DamageType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Goal)
	FVector StartPos;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Goal)
	FVector EndPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Goal)
	float speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status)
		AMainEnemy* HitEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comps)
	UStaticMeshComponent* ProjectileMesh;
};
