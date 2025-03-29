// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerNormal.h"
#include "Projectile.h"
#include "MainEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"

ATowerNormal::ATowerNormal()
{
	ProjectileSpeed = 0.2f;

	TowerRangeMesh= CreateDefaultSubobject<UStaticMeshComponent>("TowerRangeMesh");
	TowerRangeMesh->SetupAttachment(GetRootComponent());
}

void ATowerNormal::BeginPlay()
{
	Super::BeginPlay();

	TowerRangeMesh->SetVisibility(false);
}

void ATowerNormal::Tick(float _dt)
{
	Super::Tick(_dt);

	if (bHasDied)
		return;

	if(TowerRangeMesh && TowerRangeMesh->IsVisible())
		TowerRangeMesh->SetWorldRotation(FRotator(TowerRangeMesh->GetComponentRotation().Pitch, TowerRangeMesh->GetComponentRotation().Yaw + (RangeIndicatorRotSpeed * _dt), TowerRangeMesh->GetComponentRotation().Roll));
}

void ATowerNormal::Attack( )
{
	Super::Attack();

	if (bHasDied)
		return;

	if (AllGunPoints.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Gun Socket"));
		return;
	}

	if (!World)
		return;

	if(EnemiesInRange.Num() <= 0)
		return;

	if (!CurrentTarget || CurrentTarget && CurrentTarget->bHasDied)
	{
		for (size_t i = 0; i < EnemiesInRange.Num(); i++)
		{
			if(EnemiesInRange[i] && EnemiesInRange[i]->TowerAmount <= 1 && EnemiesInRange[i]->DamageWeakness == DamageType)
			{
				EnemiesInRange[i]->TowerAmount++;
				CurrentTarget = EnemiesInRange[i];

				break;
			}
		}

		if(!CurrentTarget)
		{
			for (size_t i = 0; i < EnemiesInRange.Num(); i++)
			{
				if (EnemiesInRange[i])
				{
					EnemiesInRange[i]->TowerAmount++;
					CurrentTarget = EnemiesInRange[i];

					break;
				}
			}
		}
	}

	AProjectile* projectile = nullptr;

	test++;

	FVector socketLockation = AllGunPoints[0]->GetSocketLocation(SkeletalMeshComponent);

	if (CurrentTarget && CurrentTarget->bHasDied)
	{
		if (AnimInstance->IsAnyMontagePlaying())
			AnimInstance->StopAllMontages(0);

		return;
	}

	switch (UpgradeVisualStatus)
	{
	case ETowerUpgradeVisualStatus::TUS_Normal:
		projectile = World->SpawnActor<AProjectile>(Projectile, socketLockation, FRotator(0));
		if(projectile && Damage > 0 && CurrentTarget && SkeletalMeshComponent)
			projectile->SetProjectileStats(Damage, ProjectileSpeed, CurrentTarget, DamageType, true, UKismetMathLibrary::GetForwardVector(SkeletalMeshComponent->GetSocketRotation("Gunpoint_0")), socketLockation, nullptr, false);
		break;
	case ETowerUpgradeVisualStatus::TUS_Once:
		projectile = World->SpawnActor<AProjectile>(Projectile, socketLockation, FRotator(0));
		if (projectile && Damage > 0 && CurrentTarget && SkeletalMeshComponent)
			projectile->SetProjectileStats(Damage, ProjectileSpeed, CurrentTarget, DamageType, true, UKismetMathLibrary::GetForwardVector(SkeletalMeshComponent->GetSocketRotation("Gunpoint_0")), socketLockation, nullptr, false);
		break;
		default:
			break;
	}
}