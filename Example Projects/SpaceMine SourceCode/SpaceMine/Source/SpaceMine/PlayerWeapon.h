// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllEnums.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "PlayerWeapon.generated.h"

UCLASS()
class SPACEMINE_API APlayerWeapon : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoomPlayer;
	
public:	
	APlayerWeapon();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
		void BeginTimeline(float _playRate);
	UFUNCTION()
		void TickTimeline(float _alpha);

	UPROPERTY(EditAnywhere, Category = Timeline, meta = (AllowPrivateAccess))
		UCurveFloat* curveFloat;

	FTimeline curveTimeline;

public:
	UPROPERTY()
	int randCamShake;

	UFUNCTION()
	void ActivateAttackSFX();

	UFUNCTION(BlueprintCallable)
	void ShootBullet(bool _status, AActor* _target, APlayerController* _player);
	UFUNCTION(BlueprintCallable)
	void ShootFire(bool _status);
	UFUNCTION(BlueprintCallable)
	void Damage_Bullet(AActor* _target);
	UFUNCTION(BlueprintCallable)
	void Damage_Fire();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	float ProjectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	float FireRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status)
	bool bShootProjectile;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status)
	bool bShootFire;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status)
	bool bAnimToggle;

	float ttt;

	bool kkk;

	UFUNCTION()
		virtual  void OnOverlapFireDmgBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()
		virtual void OnOverlapFireDmgEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UStaticMeshComponent* FireExtent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UStaticMeshComponent* FireExtentRoPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class ASpaceMineCharacter* WeaponOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* AttackParticleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	class UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	USpringArmComponent* PlayerCameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	FVector2D CrosshairSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	FVector GunIKLookPos;

	FTimerHandle TimerHandle_Fire;

	FLatentActionInfo fireRateInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerWeapon)
	TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(BlueprintReadOnly, Category = PlayerWeapon)
	USkeletalMeshSocket const* GunpointSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWeapon)
	FName GunpointSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWeapon)
	EDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWeapon)
	TArray<class AMainEnemy*> DamageEnemies;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UWorld* World;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent* ShootParticle;
};