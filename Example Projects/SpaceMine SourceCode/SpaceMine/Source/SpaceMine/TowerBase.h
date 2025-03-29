// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllEnums.h"
#include "EnemyTarget.h"
#include "TowerBase.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMINE_API ATowerBase : public AEnemyTarget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	class AMainEnemy* CurrentTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	FVector CurrentTargetPos;

	const TArray<AActor*> ActorRefference = TArray<AActor*>{ Cast<AActor>(this) };

public:

	ATowerBase();

	/// <summary>
	/// Virtual Public Methods
	/// </summary>

	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void Tick(float _deltaSeconds) override;

	UFUNCTION()
	virtual bool RotateWithTarget(float _deltaTime);
	UFUNCTION()
	virtual void I_TakeDamage(float _damage, AMainEnemy* _ref) override;
	UFUNCTION()
	virtual void ValidateAttack(float _deltaTime);

	virtual void PlayDeath() override;

	virtual void OnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult) override;
	virtual void OnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex) override;


	UFUNCTION(BlueprintCallable)
	virtual void Attack();
	UFUNCTION()
	virtual void ManageState(float _deltaTime);
	UFUNCTION()
	virtual void ResetTurret(float _deltaTime);
	UFUNCTION()
	virtual void SetToNoEnemyInRange();
	UFUNCTION()
	virtual void UpgradeStructure();

	UFUNCTION()
	bool CheckIfActionUnvalid();
	UFUNCTION()
	void ManageRangeIndicator();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float RangeIndicatorRotSpeed;

	UFUNCTION()
	virtual void InitStructure(class AResourceManager* _manager, class AResourcePoint* _resoucePoint);

	UFUNCTION(BlueprintCallable)
	virtual void CleanOverlappedInRange();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	bool bEnemyInRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	bool bHasCombatAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	bool bFirstShoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	bool bTargetHasDied;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	bool bResetTurretRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	int CurrEnemyIdx;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Info)
	bool bHasVisualChange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	ETowerState CurrentState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Info)
	UStaticMeshComponent* TowerRangeMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	float LastOverlappedSize;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Info)
	//float NormalUpgradeCost;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Info)
	//float SpecialUpgradeCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	TArray<AMainEnemy*> EnemiesInRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	TArray<AMainEnemy*> EnemiesInRangeToClean;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status)
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UAnimMontage* UpgradedCombatMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TSubclassOf<UAnimInstance> UpgradedAnimInterface;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UTowerAnimInstance* OwnAnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status)
	FRotator StartRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status)
	UCapsuleComponent* RootCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	EDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	USkeletalMesh* UpgradedMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	ETowerUpgradeVisualStatus UpgradeVisualStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SFX)
	UParticleSystemComponent* AttackParticleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SFX)
	UParticleSystemComponent* UpgradeParticleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float UpgradeValue_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float MaxAttackCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float CurrAttackCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float UpgradeValue_AttackCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float UpgradeValue_MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	UStaticMeshComponent* LaserPointer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	class URectLightComponent* LaserPointerEmission;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<USkeletalMeshSocket const*> AllGunPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	USkeletalMeshComponent* VerticalRotator;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	USkeletalMeshComponent* HorizontalRotator;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
	class USphereComponent* InitLookAt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Stats)
	USphereComponent* AttackRangeRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
    class AWaveManager* WaveManager;
};
