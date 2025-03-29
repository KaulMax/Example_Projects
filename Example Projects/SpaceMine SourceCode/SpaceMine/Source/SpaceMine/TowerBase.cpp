// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBase.h"
#include "MainEnemy.h"
#include "Projectile.h"
#include "ResourceManager.h"
#include "Components/PoseableMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include <SpaceMine/TowerAnimInstance.h>

#include "PlayerBuilder.h"
#include "WaveManager.h"
#include "Components/BoxComponent.h"
#include "Components/RectLightComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ATowerBase::ATowerBase()
{
	AttackRangeRadius = CreateDefaultSubobject<USphereComponent>("AttackSphere");
	AttackRangeRadius->SetupAttachment(GetRootComponent());

	InitLookAt = CreateDefaultSubobject<USphereComponent>("InitLookAt");
	InitLookAt->SetupAttachment(GetRootComponent());

	LaserPointerEmission = CreateDefaultSubobject<URectLightComponent>("LaserEmission");
	LaserPointerEmission->SetupAttachment(RootComponent);

	LaserPointer = CreateDefaultSubobject<UStaticMeshComponent>("Laser");
	LaserPointer->SetupAttachment(RootComponent);

	RootCapsule = GetCapsuleComponent();

	UpgradeParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>("UpgradeParticleComponent");

	Damage = 5.f;
	MaxAttackCooldown = 2.f;
	CurrAttackCooldown = 0.f;
	RotationSpeed = 2.f;
	LastOverlappedSize = 0;
	RangeIndicatorRotSpeed = 5.f;
	MaxStructureLevel = 10.f;

	UpgradeValue_Damage = 10.f;
	UpgradeValue_AttackCooldown = 0.15f;
	UpgradeValue_MaxHP = 25.f;
	CurrStructureLevel = 1;

	bEnemyInRange = false;
	bHasVisualChange = false;
	bCanUpgrade = false;
	bResetTurretRotation = false;
	CurrentState = ETowerState::TS_Dormant;
	UpgradeVisualStatus = ETowerUpgradeVisualStatus::TUS_Normal;
}

void ATowerBase::BeginPlay()
{
	Super::BeginPlay();

	AttackRangeRadius->OnComponentBeginOverlap.AddDynamic(this, &ATowerBase::ATowerBase::OnOverlapBegin);
	AttackRangeRadius->OnComponentEndOverlap.AddDynamic(this, &ATowerBase::ATowerBase::OnOverlapEnd);

	AllGunPoints.Add(SkeletalMeshComponent->GetSocketByName("Gunpoint_0"));
	AnimInstance = SkeletalMeshComponent->GetAnimInstance();

	LaserPointer->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "LaserPointerSocket");
	LaserPointerEmission->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "LaserPointerEmissionSocket");

	UpgradeParticleComponent->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "SpecialEffectSocket");
	RepairParticleComponent->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "SpecialEffectSocket");
	DamagedParticleComponent->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "SpecialEffectSocket");
		
	StartRotation = GetActorRotation();

	if (UpgradeParticleComponent)
		UpgradeParticleComponent->SetActive(false);

	if (RepairParticleComponent)
		RepairParticleComponent->SetActive(false);

	if (DamagedParticleComponent)
		DamagedParticleComponent->SetActive(false);
}

void ATowerBase::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (CheckIfActionUnvalid())
		return;

	//if (AnimInstance && !CurrentTarget)
	//	AnimInstance->StopAllMontages(0.f);

	if (bResetTurretRotation)
		ResetTurret(_deltaTime);

	if(bHasCombatAbility)
		ManageState(_deltaTime);

	if(bHasRange)
		ManageRangeIndicator();
}

void ATowerBase::ManageState(float _deltaTime)
{
	if (CheckIfActionUnvalid())
		return;

	if (!bEnemyInRange && CurrentState != ETowerState::TS_Dormant)
	{
		CurrentState = ETowerState::TS_Dormant;
		bTargetHasDied = false;
		if (AttackParticleComponent)
			AttackParticleComponent->Deactivate();
	}
	else if (EnemiesInRange.Num() > 0)
	{
		ValidateAttack(_deltaTime);
		CurrentState = ETowerState::TS_AttackingEnemy;
	}
}

void ATowerBase::OnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if (CheckIfActionUnvalid())
		return;

	if(AMainEnemy* currentOverlapped = Cast<AMainEnemy>(_otherActor))
	{
		if(EnemiesInRange.Num() <= 0)
			bFirstShoot = true;
		else
			bFirstShoot = false;

		bResetTurretRotation = false;
		bEnemyInRange = true;

		if(!EnemiesInRange.Contains(currentOverlapped))
			EnemiesInRange.Add(currentOverlapped);
	}
}

void ATowerBase::OnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex)
{
	if (CheckIfActionUnvalid())
		return;

	if (AMainEnemy* currentOverlapped = Cast<AMainEnemy>(_otherActor))
	{
		if(!EnemiesInRangeToClean.Contains(currentOverlapped))
			EnemiesInRangeToClean.Add(currentOverlapped);

		if (EnemiesInRangeToClean.Num() <= 1 && EnemiesInRange.Num() <= 1)
			CleanOverlappedInRange();
	}
}

void ATowerBase::ValidateAttack(float _deltaTime)
{
	CleanOverlappedInRange();

	if (!RotateWithTarget(_deltaTime))
		return;

	if(CurrentTarget && CurrentTarget->bHasDied)
	{
		for (AMainEnemy* enemy : EnemiesInRange)
		{
			if(!enemy->bHasDied)
				CurrentTarget = enemy;
		}
	}

	if (CurrAttackCooldown <= 0)
	{
		Attack();
		CurrAttackCooldown = MaxAttackCooldown;
	}
	else
		CurrAttackCooldown -= _deltaTime;
}

void ATowerBase::PlayDeath()
{
	Super::PlayDeath();

	LaserPointer->SetMaterial(0, nullptr);
}

void ATowerBase::Attack()
{
	CleanOverlappedInRange();

	if (!bEnemyInRange || EnemiesInRange.Num() <= 0)
		return;

	FVector ltLine = GetActorLocation();
	FHitResult hit;

	if(!CheckIfActionUnvalid() && EnemiesInRange.Num() > 0 && EnemiesInRange[0] && World)
	{
		if (UKismetSystemLibrary::LineTraceSingleByProfile(World, ltLine, EnemiesInRange[0]->GetActorLocation(), "IgnoreAllButEnemy",
			false, ActorRefference, EDrawDebugTrace::None, hit, true, FColor::Transparent, FColor::Transparent, 0.f))
			bTargetHasDied = false;
		else
			bTargetHasDied = true;
	}

	if (!hit.bBlockingHit)
		return;

	if(CombatMontage && AnimInstance)
	{
		if (AnimInstance->IsAnyMontagePlaying())
			AnimInstance->StopAllMontages(0);

		AnimInstance->Montage_Play(CombatMontage, 1.f);
		AnimInstance->Montage_JumpToSection(FName("Attack_1"), CombatMontage);
	}
}



bool ATowerBase::RotateWithTarget(float _deltaTime)
{
	if (CheckIfActionUnvalid())
		return false;

	if (EnemiesInRange.Num() > 0 && EnemiesInRange[0])
	{
		FVector LookAtLerp = UKismetMathLibrary::VLerp(Cast<UTowerAnimInstance>(AnimInstance)->LookAtPos, EnemiesInRange[0]->GetActorLocation(), 0.05f);

		Cast<UTowerAnimInstance>(AnimInstance)->LookAtPos = LookAtLerp;

		return true;
	}
	else 
		return false;
}

void ATowerBase::I_TakeDamage(float _damage, AMainEnemy* _ref)
{
	Super::I_TakeDamage(_damage, _ref);

	if (EnemiesInRange.Num() <= 0)
	{
		bResetTurretRotation = false;
		bEnemyInRange = true;
		bFirstShoot = true;

		if (!EnemiesInRange.Contains(_ref))
			EnemiesInRange.Add(_ref);
	}
}

void ATowerBase::ResetTurret(float _deltaTime)
{
	if (CheckIfActionUnvalid())
		return;

	FRotator interpRotation = FMath::RInterpTo(GetActorRotation(), StartRotation, _deltaTime, RotationSpeed);

	SetActorRotation(interpRotation);
}

void ATowerBase::SetToNoEnemyInRange()
{
	if (CheckIfActionUnvalid())
		return;

	if (CurrentTarget && CurrentTarget->TowerAmount > 0)
		CurrentTarget->TowerAmount--;

		CurrentTarget = nullptr;
	bEnemyInRange = false;
	bFirstShoot = false;
	bResetTurretRotation = true;
}

void ATowerBase::UpgradeStructure()
{
	if (CheckIfActionUnvalid())
		return;

	if(CurrStructureLevel >= MaxStructureLevel)
		bCanUpgrade = false;

	if(bHasVisualChange)
	{
		if(StructureType == EStructureBuildType::SBT_BoltTurret)
		{
			//StructureType = EStructureBuildType::SBT_BoltTurret;
			CombatMontage = UpgradedCombatMontage;
		}

		UpgradeParticleComponent->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "SpecialEffectSocket");
		RepairParticleComponent->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "SpecialEffectSocket");

		SkeletalMeshComponent->SetAnimClass(UpgradedAnimInterface);
		SkeletalMeshComponent->SetSkeletalMesh(UpgradedMesh);
		AnimInstance = SkeletalMeshComponent->GetAnimInstance();
		AllGunPoints.Add(SkeletalMeshComponent->GetSocketByName("Gunpoint_1"));
		AllGunPoints.Add(SkeletalMeshComponent->GetSocketByName("Gunpoint_2"));
		Cast<UTowerAnimInstance>(AnimInstance)->LookAtPos = InitLookAt->GetComponentLocation();
	}



	if (UpgradeParticleComponent)
		UpgradeParticleComponent->SetActive(true);

	if (DamagedParticleComponent)
		DamagedParticleComponent->SetActive(false);

	bWasRepaired = false;
	CurrStructureLevel++;

	Damage += UpgradeValue_Damage;
	MaxHP += UpgradeValue_MaxHP;

	MaxAttackCooldown -= UpgradeValue_AttackCooldown;

	CurrAttackCooldown = 0.f;

	SkeletalMeshComponent->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	CurrentHP = MaxHP;
	UpgradeVisualStatus = ETowerUpgradeVisualStatus::TUS_Once;
}


void ATowerBase::InitStructure(AResourceManager* _manager, AResourcePoint* _resourcePoint)
{
	ResourceManager = _manager;
	
	if(AnimInstance)
		Cast<UTowerAnimInstance>(AnimInstance)->LookAtPos = InitLookAt->GetComponentLocation();
}

void ATowerBase::CleanOverlappedInRange()
{
	for(AMainEnemy* enemy : EnemiesInRange)
	{
		if (!enemy && !EnemiesInRangeToClean.Contains(enemy))
			EnemiesInRangeToClean.Add(enemy);
	}

	for(AMainEnemy* enemy : EnemiesInRangeToClean)
	{
		if(EnemiesInRange.Contains(enemy))
			EnemiesInRange.Remove(enemy);
	}

	if (EnemiesInRange.Num() <= 0)
	{
		SetToNoEnemyInRange();
		EnemiesInRangeToClean.Reset();
	}

}

bool ATowerBase::CheckIfActionUnvalid()
{
	if (bHasDied /*||  bTargetHasDied  || CurrentTarget && CurrentTarget->bHasDied */)
		return true;
	else
		return false;
}

void ATowerBase::ManageRangeIndicator()
{
	if (bHasDied || !WaveManager || !TowerRangeMesh || !BuilderRef)
		return;

	if (WaveManager && WaveManager->CurrentGamePhase == ECurrentGamePhase::CGP_Fight && TowerRangeMesh->IsVisible() || !bIsBeignWatched ||
		!BuilderRef->CurrentStructure || BuilderRef->CurrentStructure != this)
	{
		TowerRangeMesh->SetVisibility(false);
		SkeletalMeshComponent->bRenderCustomDepth = false;
		SkeletalMeshComponent->MarkRenderStateDirty();
	}
	else if (bIsBeignWatched && !TowerRangeMesh->IsVisible())
	{
		TowerRangeMesh->SetVisibility(true);
		SkeletalMeshComponent->bRenderCustomDepth = true;
		SkeletalMeshComponent->MarkRenderStateDirty();
	}
}
