// Fill out your copyright notice in the Description page of Project Settings.


#include "MainEnemy.h"

#include "AIController.h"
#include <SpaceMine/EnemyTarget.h>

#include "Barrier.h"
#include "DamageUISpawn.h"
#include "EnemySpawner.h"
#include "GameManager.h"
#include "NavigationPath.h"
#include "EnemyAnimInstance.h"
#include "Generator.h"
#include "MainDrill.h"
#include "NavigationSystem.h"
#include "SpaceMineCharacter.h"
#include "TowerNormal.h"
#include "Weapon.h"
#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMainEnemy::AMainEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	MaxHP = 100.f;
	MaxStateChangeTime = 0.8f;
	AttackDamage = 10.f;
	DamageTolerance = 5.f;
	AttackCooldown = 2.5f;
	CombatRotationSpeed = 4.5f;

	GetHitAnimLenght = 0.54;

	bCanAttack = true;
	bAttackFinished = true;
	bCanResetStateChange = false;
	bTargetInAggroRange = false;
	bCanMakeDamage = false;
	bCanSeeTarget = false;
	bActivateHealthBar = false;

	EnemyAggroExtend = 520.f;
	EnemyCombatExtend = 85.f;
	EnemyFollowExtend = 300.f;

	EnemyAggroRange = CreateDefaultSubobject<USphereComponent>("EnemyAggroSphere");
	EnemyAggroRange->SetupAttachment(GetRootComponent());
	EnemyAggroRange->InitSphereRadius(EnemyAggroExtend);

	EnemyCombatRange = CreateDefaultSubobject<USphereComponent>("EnemyCombatSphere");
	EnemyCombatRange->SetupAttachment(GetRootComponent());
	EnemyCombatRange->InitSphereRadius(EnemyCombatExtend);

	EnemyFollowAttackRange = CreateDefaultSubobject<USphereComponent>("EnemyFollowAttackSphere");
	EnemyFollowAttackRange->SetupAttachment(GetRootComponent());
	EnemyFollowAttackRange->InitSphereRadius(EnemyFollowExtend);

	ChildActor = CreateDefaultSubobject<UChildActorComponent>("WeaponChild");
	ChildActor->CreateChildActor();

	DamagedParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>("DamagedParticleSystem");
	DamagedParticleComponent->SetupAttachment(GetRootComponent());

	EnemyHealthBar = CreateDefaultSubobject<UWidgetComponent>("EnemyHealthBar");
	EnemyHealthBar->SetupAttachment(RootComponent);

	CapsuleComp = GetCapsuleComponent();

	SetEnemyMovementStatus(EEnemyState::ES_WalkToGoal);
}

void AMainEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMainEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyAggroRange->OnComponentBeginOverlap.AddDynamic(this, &AMainEnemy::AMainEnemy::AggroRangeOnOverlapBegin);
	EnemyAggroRange->OnComponentEndOverlap.AddDynamic(this, &AMainEnemy::AMainEnemy::AggroRangeOnOverlapEnd);
	
	EnemyCombatRange->OnComponentBeginOverlap.AddDynamic(this, &AMainEnemy::AMainEnemy::CombatRangeOnOverlapBegin);
	EnemyCombatRange->OnComponentEndOverlap.AddDynamic(this, &AMainEnemy::AMainEnemy::CombatRangeOnOverlapEnd);
	
	EnemyFollowAttackRange->OnComponentBeginOverlap.AddDynamic(this, &AMainEnemy::AMainEnemy::FollowDamageRangeOnOverlapBegin);
	EnemyFollowAttackRange->OnComponentEndOverlap.AddDynamic(this, &AMainEnemy::AMainEnemy::FollowDamageRangeOnOverlapEnd);

	if(DamagedParticleComponent)
		DamagedParticleComponent->Deactivate();

	SkeletalMesh = GetMesh();
	ChildActor->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocketName);
	ChildActor->SetChildActorClass(Weapon);

	TSubclassOf<AActor> weaponActor = ChildActor->GetChildActorClass();
	AWeapon* weaponRef = Cast<AWeapon>(weaponActor.GetDefaultObject());

	if (!weaponRef)
		return;
	

	bCanMakeDamage = false;
}

void AMainEnemy::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	if(bHasDied)
		return;

	if(CurrentTarget && bIsInCombat && bAttackFinished)
		RotateWithTarget(_deltaTime);

	switch (CurrentMovementState)
	{
	case EEnemyState::ES_WalkToGoal:
		if(bAttackFinished && bCanSwitchState && !bIsInCombat && !bTargetInAggroRange)
			MoveToGoalTarget();
		break;

	case EEnemyState::ES_Attacking:
		if (bCanAttack && bCanSwitchState && !bCanMakeDamage)
			Attack(CurrentTarget);
		break;

	case EEnemyState::ES_WalkToTarget:
		if (CurrentTarget && bAttackFinished && bCanSwitchState && !CurrentTarget->HasAnyFlags(EObjectFlags::RF_BeginDestroyed))
		{
			SetTargetInfos(CurrentFollowTarget);
			MoveToTarget();
		}
		else
			ResetTarget();


		break;

	case EEnemyState::ES_Idle:
		if(bAttackFinished)
			ResetTarget();
		break;
	}

	if(bOverlapAttacker && bIsBeingAttacked)
	{
		SetTargetInfos(CurrentFollowTarget);
		SetEnemyMovementStatus(EEnemyState::ES_WalkToTarget);
	}
	else if (!bOverlapAttacker && bIsBeingAttacked) 
	{
		SetTargetInfos(CurrentTarget);
		bIsBeingAttacked = false;
		SetEnemyMovementStatus(EEnemyState::ES_WalkToTarget);
	}

	// TODO: Debug -> Die bleiben random stehen wenn die Direkt vor dem Target stehen
	if (CurrentMovementState == EEnemyState::ES_WalkToTarget && bCanSwitchState
		&& bAttackFinished && bCanAttack && bIsInCombat && bIsBeingAttacked && bOverlapAttacker && !bHasDied)
		DebugEnemyAttack();

	//if(CurrentTarget && CurrentTarget->bHasDied)
	//{
	//	ResetTarget();
	//	bIsInCombat = false;
	//	bTargetInAggroRange = false;
	//	bTargedLocked = false;
	//}

	RotateHealthBar();

	if (AnimInstanceCast && bResetGetHitAlpha && AnimInstanceCast->GetHitAlpha > 0)
		AnimInstanceCast->GetHitAlpha -= _deltaTime * 2;
	else if (AnimInstanceCast && bResetGetHitAlpha && AnimInstanceCast->GetHitAlpha <= 0)
		bResetGetHitAlpha = false;
}

void AMainEnemy::MoveToGoalTarget()
{
	if (!EnemyController)
		return;

	currentPath = NavigationSystem->FindPathToLocationSynchronously(World, GetActorLocation(), TargetLocation, NULL);

	if (currentPath && currentPath->IsPartial() || currentPath && !currentPath->GetPath().IsValid())
	{
		ResetTarget();
		return;
	}

	if(!bCantMoveToggle /* && !bIsMovingToggle*/)
	{
		//bIsMovingToggle = true;
		if (EnemyController)
			EnemyController->MoveTo(MainDrill);
	}
}

void AMainEnemy::MoveToTarget( )
{
	if (!EnemyController)
		return;

	if(CurrentTarget && Cast<AEnemyTarget>(CurrentTarget)->bHasDied)
	{
		ResetTarget();
		return;
	}

	currentPath = NavigationSystem->FindPathToLocationSynchronously(World, GetActorLocation(), TargetLocation, NULL);

	if (currentPath && currentPath->IsPartial() || currentPath && !currentPath->GetPath().IsValid())
	{
		bHasCombatOverlap = false;
		bIsInCombat = false;
		bTargetInAggroRange = false;
		bOverlapAttacker = false;
		bIsBeingAttacked = false;
		bTargedLocked = false;
		ResetTarget();
		SwitchState();

		return;
	}

	if (!bCantMoveToggle/* && !bIsMovingToggle*/)
	{
		//bIsMovingToggle = true;
		if(EnemyController)
			EnemyController->MoveTo(TargetLocation);
	}
}

void AMainEnemy::Attack(AActor* _target)
{
	if(bHasDied)
		bCanMakeDamage = false;

	if (!AnimInstance || bHasDied)
		return;

	if (EnemyController)
	EnemyController->StopMovement();

	AnimInstance->Montage_Play(CombatMontage, 1.f);
	AnimInstance->Montage_JumpToSection(FName("Attack_1"), CombatMontage);

	bCanMakeDamage = true;
}

void AMainEnemy::TakeDamage(float _damage, EDamageType _damageType, AActor* _attacker)
{
	if(bHasDied || !bCanTakeDamage || UGameplayStatics::GetGlobalTimeDilation(World) <= 0.1f)
		return;

	if(Cast<AMainEnemy>(_attacker))
		bActivateHealthBar = true;

	if (!CurrentTarget)
		CurrentTarget = _attacker;

	if (_damageType == DamageWeakness)
	{
		CurrentHP -= _damage;

		if (DamageUIText)
		{
			ADamageUISpawn* damagetext = World->SpawnActor<ADamageUISpawn>(DamageUIText, GetActorLocation(), GetActorRotation());

			bool uidebug = false;

			if (_attacker)
				uidebug = true;

			damagetext->InitDamageText(_damage, this, true, true, uidebug);
		}
	}
	else
	{
		CurrentHP -= (_damage / DamageTolerance);

		if (DamageUIText)
		{
			ADamageUISpawn* damagetext = World->SpawnActor<ADamageUISpawn>(DamageUIText, GetActorLocation(), GetActorRotation());

			bool uidebug = false;

			if (_attacker)
				uidebug = true;

				damagetext->InitDamageText(_damage / DamageTolerance, this, false,true, uidebug);
		}
	}

	if (DamagedParticleComponent)
		DamagedParticleComponent->Activate(true);

	AnimInstanceCast->GetHitAlpha = 1.f;

	bResetGetHitAlpha = true;

	if (!bHasCombatOverlap)
		bIsBeingAttacked = true;

	if(CurrentHP <= 0.05f)
		PlayDeath();
}

bool AMainEnemy::DamagePreview(float _damage, EDamageType _damageType)
{
	if (bHasDied || !bCanTakeDamage || UGameplayStatics::GetGlobalTimeDilation(World) <= 0.1f)
		return false;

	float currhp = CurrentHP;

	if (_damageType == DamageWeakness)
	{
		if (currhp - _damage <= 0)
			return true;
	}
	else if(_damageType != DamageWeakness)
	{
		if (currhp - (_damage / DamageTolerance) <= 0)
			return true;
	}

	return false;
}

void AMainEnemy::PlayDeath()
{
	SkeletalMesh->SetSimulatePhysics(true);

	bHasDied = true;
	bCanMakeDamage = false;

	if(EnemyController)
		EnemyController->StopMovement();

	EnemySpawner->AddToClean(this);

	SkeletalMesh->SetMaterial(0, FadeMaterial_1);

	CapsuleComp->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->bDynamicObstacle = false;
	CapsuleComp->AreaClass = nullptr;
	EnemyController->Destroy();

	GetMovementComponent()->Deactivate();

	if(SkeletalMesh->GetNumMaterials() >= 2)
		SkeletalMesh->SetMaterial(1, FadeMaterial_2);

}

void AMainEnemy::CleanAfterDeath()
{
	Destroy();
}


void AMainEnemy::AggroRangeOnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if (!_otherActor || !EnemyController || !bCanTakeDamage || bTargedLocked)
		return;


	if (CurrentMovementState == EEnemyState::ES_Attacking)
		return;

	if (_otherActor->GetClass()->ImplementsInterface(UInterfaceDamageablePlayer::StaticClass()))
	{
		bTargetInAggroRange = true;

		SetTargetInfos(_otherActor);
		bTargedLocked = true;
		SetEnemyMovementStatus(EEnemyState::ES_WalkToTarget);
	}
}

void AMainEnemy::AggroRangeOnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex)
{
	if (!_otherActor || !EnemyController || !bCanTakeDamage)
		return;

	if (CurrentMovementState == EEnemyState::ES_Attacking)
		return;

	if (_otherActor->GetClass()->ImplementsInterface(UInterfaceDamageablePlayer::StaticClass()))
	{
		bTargetInAggroRange = false;
		bTargedLocked = false;
		ResetTarget();
	}
}

void AMainEnemy::CombatRangeOnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if (CurrentMovementState == EEnemyState::ES_Attacking || !bCanTakeDamage)
		return;

	if (_otherActor->GetClass()->ImplementsInterface(UInterfaceDamageablePlayer::StaticClass()))
	{
		bHasCombatOverlap = true;
		bIsInCombat = true; 
		bTargedLocked = false;

		SetTargetInfos(_otherActor);
		if(EnemyController)
			EnemyController->StopMovement();
		SetEnemyMovementStatus(EEnemyState::ES_Attacking);
	}
}

void AMainEnemy::CombatRangeOnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex)
{
	if (!EnemyController || !bCanTakeDamage)
		return;

	if (_otherActor->GetClass()->ImplementsInterface(UInterfaceDamageablePlayer::StaticClass()))
	{
		if(_otherActor)
		{
			SetTargetInfos(_otherActor);
			bHasCombatOverlap = false;
			bIsInCombat = false;
			SetEnemyMovementStatus(EEnemyState::ES_WalkToTarget);
		}
		else
		{
			ResetTarget();
			bHasCombatOverlap = false;
			bIsInCombat = false;
		}
	}
}

void AMainEnemy::FollowDamageRangeOnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if (CurrentMovementState == EEnemyState::ES_Attacking || !bCanTakeDamage || Cast<ATowerBase>(_otherActor) || Cast<AGenerator>(_otherActor))
		return;

	if (_otherActor->GetClass()->ImplementsInterface(UInterfaceDamageablePlayer::StaticClass()) )
	{
		bOverlapAttacker = true;

		if (!_otherActor)
			return;

		CurrentFollowTarget = _otherActor;
	}
}

void AMainEnemy::FollowDamageRangeOnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex)
{
	if (!EnemyController || !bCanTakeDamage || Cast<ATowerBase>(_otherActor) || Cast<AGenerator>(_otherActor))
		return;

	if (CurrentMovementState == EEnemyState::ES_Attacking)
		return;

	if (!_otherActor)
	{
		if (_otherActor->GetClass()->ImplementsInterface(UInterfaceDamageablePlayer::StaticClass()))
		{
			bIsBeingAttacked = false;
			bOverlapAttacker = false;
			bTargetInAggroRange = false;
		}
	}
}

void AMainEnemy::ResetTarget()
{
	SetEnemyMovementStatus(EEnemyState::ES_WalkToGoal);
	SwitchState();
	SetTargetInfos(MainDrill);
	bCanResetStateChange = true;
	//bIsMovingToggle = false;
	bIsInCombat = false;
	bTargetInAggroRange = false;
}

// Gets called when the attack is Finished
void AMainEnemy::SetAttackFinished(bool _status)
{
	//if(WeaponRef)
	//	WeaponRef->AttackStatus(false);

	bAttackFinished = _status;
}

// Gets called when the Cooldown is <= 0
void AMainEnemy::ResetCooldown(bool _status)
{
	bCanAttack = _status;
}

void AMainEnemy::SwitchState()
{
	SetAttackFinished(true);
	bCanMakeDamage = false;
	bCanResetStateChange = true;
	bCanSwitchState = false;
}

void AMainEnemy::RotateGunpoint(float _deltaTime)
{
	if (!CurrentTarget)
		return;

	FVector gunpointRot = CurrentTarget->GetActorLocation();

	FRotator lookAt = GetLookAtRoll(gunpointRot);
	FRotator interpRotation = FMath::RInterpTo(ChildActor->GetComponentRotation(), lookAt, _deltaTime, CombatRotationSpeed);

	ChildActor->SetRelativeRotation(interpRotation);
}

void AMainEnemy::RotateWithTarget(float _deltaTime)
{
	if (!CurrentTarget)
		return;

	FRotator lookAt = GetLookAtYaw(CurrentTarget->GetActorLocation());
	FRotator interpRotation = FMath::RInterpTo(GetActorRotation(), lookAt, _deltaTime, CombatRotationSpeed);

	SetActorRotation(interpRotation);
}

FRotator AMainEnemy::GetLookAtYaw(FVector _target)
{
	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), _target);
	FRotator LookAtYaw(0.f, lookAtRotation.Yaw, 0.f);

	return LookAtYaw;
}

FRotator AMainEnemy::GetLookAtPitch(FVector _target)
{
	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), _target);
	FRotator LookAtPitch(lookAtRotation.Pitch, 0.f, 0.f);

	return LookAtPitch;
}

FRotator AMainEnemy::GetLookAtRoll(FVector _target)
{
	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), _target);
	FRotator LookAtRoll(0.f, 0.f, lookAtRotation.Roll);

	return LookAtRoll;
}

void AMainEnemy::SetTargetInfos(AActor* _target)
{
	if (!_target)
		return;

	CurrentTarget = _target;

	FVector dirToTarget = CurrentTarget->GetActorLocation() - GetActorLocation();

	float distance = dirToTarget.Size();
	distance -= 60;
	dirToTarget.Normalize();
	TargetLocation = GetActorLocation() + (dirToTarget * distance);
	//bIsMovingToggle = false;
}

void AMainEnemy::SetSpawnStats(AGameManager* _gameManager, AEnemySpawner* _enemySpawner, bool _bBridgeDebug)
{
	if (_gameManager && _enemySpawner && !EnemySpawner && !GameManager)
	{
		EnemySpawner = _enemySpawner;
		GameManager = _gameManager;
		bBridgeDebug = _bBridgeDebug;
	}
	else
		return;
		

	AnimInstance = SkeletalMesh->GetAnimInstance();
	AnimInstanceCast = Cast<UEnemyAnimInstance>(AnimInstance);

	World = GetWorld();
	NavigationSystem = UNavigationSystemV1::GetCurrent(World);

	SpawnDefaultController();
	
	EnemyController = Cast<AAIController>(GetController());

	CurrentHP = MaxHP;

	if (!GameManager)
		return;

	MainDrill = GameManager->MainDrill;
	ResetTarget();

	bCanTakeDamage = true;

	PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(World, 0);
}

void AMainEnemy::DebugEnemyAttack()
{
	CurrentMovementState = EEnemyState::ES_Attacking;
}


void AMainEnemy::RotateHealthBar()
{
	if (EnemyHealthBar && EnemyHealthBar && PlayerCameraManager)
		EnemyHealthBar->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(EnemyHealthBar->GetComponentLocation(), PlayerCameraManager->GetCameraLocation()));
}
