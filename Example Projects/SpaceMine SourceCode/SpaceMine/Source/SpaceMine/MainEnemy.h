// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllEnums.h"
#include "GameFramework/Character.h"
#include "MainEnemy.generated.h"

UCLASS()
class SPACEMINE_API AMainEnemy : public ACharacter
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnimation)
	UAnimMontage* CombatMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyAnimation)
	UAnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyAnimation)
		class UEnemyAnimInstance* AnimInstanceCast;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyCombatTarget)
	class AActor* CurrentTarget;

public:
	virtual void Tick(float _deltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	AMainEnemy();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
		bool bActivateHealthBar;

	UFUNCTION(BlueprintCallable)
	void MoveToGoalTarget();
	UFUNCTION()
	void DebugEnemyAttack();
	UFUNCTION(BlueprintCallable)
	void MoveToTarget();
	UFUNCTION(BlueprintCallable)
	void Attack(AActor* _target);
	UFUNCTION(BlueprintCallable)
	void PlayDeath();
	UFUNCTION(BlueprintCallable)
	void CleanAfterDeath();
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float _damage, EDamageType _towerType, AActor* _attacker);
	UFUNCTION()
	bool DamagePreview(float _damage, EDamageType _towerType);
	UFUNCTION(BlueprintCallable)
	void ResetTarget();
	UFUNCTION(BlueprintCallable)
	void SetAttackFinished(bool _status);
	UFUNCTION(BlueprintCallable)
	void ResetCooldown(bool _status);
	UFUNCTION()
	void SwitchState();
	UFUNCTION()
	void RotateGunpoint(float _deltaTime);
	UFUNCTION()
	void RotateWithTarget(float _deltaTime);
	UFUNCTION()
	FRotator GetLookAtYaw(FVector _target);
	UFUNCTION()
	FRotator GetLookAtPitch(FVector _target);
	UFUNCTION()
	FRotator GetLookAtRoll(FVector _target);
	UFUNCTION()
	void SetTargetInfos(AActor* _target);
	UFUNCTION()
	void RotateHealthBar();

	UFUNCTION(BlueprintCallable)
	void SetSpawnStats(class AGameManager* _gameManager, class AEnemySpawner* _enemySpawner, bool _bBridgeDebug);

	/// <summary>
	/// Collision Methods
	/// </summary>

	UFUNCTION()
	virtual void AggroRangeOnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()		
	virtual void AggroRangeOnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex);

	UFUNCTION()
	virtual void CombatRangeOnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()		   
	virtual void CombatRangeOnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex);

	UFUNCTION()
	virtual void FollowDamageRangeOnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()
	virtual void FollowDamageRangeOnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex);

	/// <summary>
	/// FORCEINLINE Public Methods
	/// </summary>

	FORCEINLINE void SetEnemyMovementStatus(EEnemyState _state) { CurrentMovementState = _state; }

	/// <summary>
	/// Public Variables
	/// </summary>

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
	EEnemyType EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
	float DamageTolerance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
		float GetHitAnimLenght;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyInfo)
		bool bResetGetHitAlpha;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyInfo)
	bool bCantMoveToggle;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyInfo)
	//bool bIsMovingToggle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyInfo)
	bool bTargedLocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyComps)
	UMaterialInstance* FadeMaterial_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyComps)
	UMaterialInstance* FadeMaterial_2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
		TSubclassOf<class ADamageUISpawn> DamageUIText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyStats)
	float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
	float AttackCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
	float CombatRotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyStats)
	float EnemyAggroExtend;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyStats)
	bool bHasCombatOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyStats)
	float EnemyCombatExtend;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyStats)
	float EnemyFollowExtend;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyStatus)
	EEnemyState CurrentMovementState;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyNavigation)
	//TSubclassOf<class UNavigationQueryFilter> NavClassFilter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStatus)
	bool bCanResetStateChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStatus)
	bool bCanSeeTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStatus)
	bool bCanTakeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyStatus)
	float MaxStateChangeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStatus)
	bool bCanSwitchState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyStatus)
	bool bAttackFinished;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyStatus)
	bool bCanAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStatus)
	bool bCanMakeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyStatus)
	bool bIsInCombat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyStatus)
	bool bTargetInAggroRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyStatus)
	bool bHasDied;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyStatus)
	bool bIsBeingAttacked;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyStatus)
	bool bOverlapAttacker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStatus)
	bool bBridgeDebug;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyStatus)
	bool bRangedAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyStatus)
	int TowerAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TargetInfo)
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyInfo)
	class UWidgetComponent* EnemyHealthBar;

	const TArray<AActor*> ActorRefference = TArray<AActor*>{ Cast<AActor>(this) };

	/// <summary>
	/// Public Components
	/// </summary>

	UPROPERTY(VisibleAnywhere, Category = EnemyCombatComponents)
	class USphereComponent* EnemyAggroRange;

	UPROPERTY(VisibleAnywhere, Category = EnemyCombatComponents)
	USphereComponent* EnemyCombatRange;

	UPROPERTY(VisibleAnywhere, Category = EnemyCombatComponents)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, Category = EnemyCombatComponents)
	USphereComponent* EnemyFollowAttackRange;

	UPROPERTY(EditAnywhere, Category = EnemyCombatComponents)
	class AAIController* EnemyController;;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyCombatTarget)
	AActor* CurrentFollowTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyGoalPosition)
	class AEnemyTarget* MainDrill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyGoalPosition)
	class AGameManager* GameManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyGoalPosition)
	class AEnemySpawner* EnemySpawner;

	UPROPERTY(BlueprintReadOnly, Category = Navigation)
	class UNavigationSystemV1* NavigationSystem;

	UPROPERTY(BlueprintReadOnly, Category = Navigation)
	class UNavigationPath* currentPath;

	UPROPERTY(BlueprintReadOnly, Category = World)
	UWorld* World;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = World)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = World)
	APlayerCameraManager* PlayerCameraManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyWeapon)
	TSubclassOf<class AWeapon> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyWeapon)
	EDamageType DamageWeakness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyWeapon)
	FName WeaponSocketName;

	UPROPERTY(BlueprintReadOnly, Category = EnemyWeapon)
	const USkeletalMeshSocket* WeaponSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyWeapon)
	UChildActorComponent* ChildActor;

	/// <summary>
	/// Public SFX and Audio Component Placeholder
	/// </summary>

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy SFX and Sound")
	class USoundCue* EnemyDamagedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* DamagedParticleComponent;
 };