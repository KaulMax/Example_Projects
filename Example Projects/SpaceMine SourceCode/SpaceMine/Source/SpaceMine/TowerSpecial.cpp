// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerSpecial.h"

#include "EnemyAnimInstance.h"
#include "MainEnemy.h"
#include "TowerAnimInstance.h"
#include "Components/BoxComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Particles/ParticleSystemComponent.h"


ATowerSpecial::ATowerSpecial()
{
	DamageExtendBox = CreateDefaultSubobject<UBoxComponent>("DamageExtendBox");

	AttackParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>("AttackParticleComponent");

	DamageExtendBox->OnComponentBeginOverlap.AddDynamic(this, &ATowerSpecial::ATowerSpecial::DamageBoxOnOverlapBegin);
	DamageExtendBox->OnComponentEndOverlap.AddDynamic(this, &ATowerSpecial::ATowerSpecial::DamageBoxOnOverlapEnd);

	TowerRangeMesh = CreateDefaultSubobject<UStaticMeshComponent>("TowerRangeMesh");
	TowerRangeMesh->SetupAttachment(GetRootComponent());

	bEnemyInDamageRange = true;
	AttackInterval = 1.0f;
}

void ATowerSpecial::BeginPlay()
{
	Super::BeginPlay();

	TowerRangeMesh->SetVisibility(false);

	if (AttackParticleComponent)
		AttackParticleComponent->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Gunpoint_0");

	if (DamageExtendBox)
		DamageExtendBox->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "DamageVolumenPos");

	if (AttackParticleComponent)
		AttackParticleComponent->Deactivate();

	OwnAnimInstance = Cast<UTowerAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
}

void ATowerSpecial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHasDied)
		return;

	if (TowerRangeMesh && TowerRangeMesh->IsVisible())
		TowerRangeMesh->SetWorldRotation(FRotator(TowerRangeMesh->GetComponentRotation().Pitch, TowerRangeMesh->GetComponentRotation().Yaw + (RangeIndicatorRotSpeed * DeltaTime), TowerRangeMesh->GetComponentRotation().Roll));

	if (bEnemyInDamageRange && DamageEnemies.Num() <= 0)
		bEnemyInDamageRange = false;
}

void ATowerSpecial::PlayDeath()
{
	Super::PlayDeath();

	DamageExtendBox->SetCollisionObjectType(ECollisionChannel::ECC_Camera);
	DamageExtendBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATowerSpecial::DamageBoxOnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if (bHasDied)
		return;

	if (AMainEnemy* hitEnemy = Cast<AMainEnemy>(_otherActor))
	{
		if (hitEnemy)
			bEnemyInDamageRange = true;

		if (!DamageEnemies.Contains(hitEnemy))
			DamageEnemies.Add(hitEnemy);
	}
}

void ATowerSpecial::DamageBoxOnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex)
{
	if (bHasDied)
		return;

	AMainEnemy* hitEnemy = Cast<AMainEnemy>(_otherActor);

	if (!DamageEnemiesToClean.Contains(hitEnemy))
		DamageEnemiesToClean.Add(hitEnemy);


	CleanDamageEnemies();
}

void ATowerSpecial::CleanDamageEnemies()
{
	if (bHasDied)
		return;

	if (DamageEnemiesToClean.Num() <= 0)
		return;

	for(AMainEnemy* enemy : DamageEnemiesToClean)
	{
		if (enemy)
		{
			if (DamageEnemies.Contains(enemy))
				DamageEnemies.Remove(enemy);
		}
	}

	DamageEnemiesToClean.Reset();
}

void ATowerSpecial::Attack()
{
	Super::Attack();

	if (bHasDied)
		return;

	//if (!OwnAnimInstance->bCanMakeDamage)
	//	return;

	if (AllGunPoints.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Gun Sockets"))
			return;
	}

	if (DamageEnemies.Num() <= 0)
		return;

	if (!CurrentTarget || CurrentTarget && CurrentTarget->bHasDied)
	{
		for (size_t i = 0; i < EnemiesInRange.Num(); i++)
		{
			if (EnemiesInRange[i] && EnemiesInRange[i]->TowerAmount <= 1 && EnemiesInRange[i]->DamageWeakness == DamageType)
			{
				EnemiesInRange[i]->TowerAmount++;
				CurrentTarget = EnemiesInRange[i];

				break;
			}
		}

		if (!CurrentTarget)
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

	if (AttackParticleComponent)
	{
		if (AttackParticleComponent->HasBegunPlay())
		{
			AttackParticleComponent->SetActive(false);
			AttackParticleComponent->SetActive(true);
		}
		else
			AttackParticleComponent->SetActive(true);
	}

	if (CurrentTarget && CurrentTarget->bHasDied)
	{
		if (AnimInstance->IsAnyMontagePlaying())
		{
			AttackParticleComponent->SetActive(false);
			AnimInstance->StopAllMontages(0);
		}

		return;
	}

	switch (UpgradeVisualStatus)
	{
	case ETowerUpgradeVisualStatus::TUS_Normal:
		{
			for(AMainEnemy* enemy : DamageEnemies)
			{
				if (DamageEnemies.Num() <= 0)
					break;

				if (enemy && !enemy->bHasDied && enemy->DamagePreview(Damage, DamageType))
				{
					enemy->TakeDamage(enemy->CurrentHP , enemy->DamageWeakness, nullptr);
					break;
				}
				else if(enemy && !enemy->bHasDied)
					enemy->TakeDamage(Damage, DamageType, nullptr);
			}
		}
		break;

	case ETowerUpgradeVisualStatus::TUS_Once:
	{
		for (AMainEnemy* enemy : DamageEnemies)
		{
			if (DamageEnemies.Num() <= 0)
				break;

			if (enemy && !enemy->bHasDied && enemy->DamagePreview(Damage, DamageType))
			{
				enemy->TakeDamage(enemy->CurrentHP, enemy->DamageWeakness, nullptr);
				break;
			}
			else if (enemy && !enemy->bHasDied)
				enemy->TakeDamage(Damage, DamageType, nullptr);
		}
	}
	break;
		default:
			break;
	}

	//bFirstShoot = true;
}
