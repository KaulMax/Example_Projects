// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "EnemyTarget.h"
#include "MainEnemy.h"
#include "InterfaceDamageablePlayer.h"
#include "SpaceMineCharacter.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	RootComponent = SkeletalMesh;

	WeaponHitBox = CreateDefaultSubobject<UBoxComponent>("WeaponHitBox");
	WeaponHitBox->SetupAttachment(GetRootComponent());

	AttackParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("AttackParticle");
	AttackParticleComp->SetupAttachment(GetRootComponent());

	targetSet = false;
}

void AWeapon::AttackBoxOnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if (WeaponOwner->EnemyType == EEnemyType::ET_Crystal)
	{
		if (AEnemyTarget* target = Cast<AEnemyTarget>(_otherActor))
		{
			targetSet = true;
			CurrentTarget = target;
		}
	}

	if (WeaponOwner && WeaponOwner->bCanMakeDamage)
	{
		if (AEnemyTarget* target = Cast<AEnemyTarget>(_otherActor)) 
		{
			if (!target)
				return;

			CurrentTarget = target;
			WeaponCooldown = 0;
			Attack();
		}
	}
}

void AWeapon::AttackBoxOnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex)
{
	if (!_otherActor)
		return;

	if (AEnemyTarget* target = Cast<AEnemyTarget>(_otherActor))
	{
		targetSet = false;

		if (!target || !CurrentTarget)
			return;

		WeaponCooldown = 0;
		CurrentTarget = nullptr;
	}
}


void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (AttackParticleComp)
		AttackParticleComp->Deactivate();

	WeaponHitBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::AWeapon::AttackBoxOnOverlapBegin);
	WeaponHitBox->OnComponentEndOverlap.AddDynamic(this, &AWeapon::AWeapon::AttackBoxOnOverlapEnd);

	WeaponOwner = Cast<AMainEnemy>(GetParentActor());
	Damage = WeaponOwner->AttackDamage;
}

void AWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (targetSet && WeaponOwner && WeaponOwner->bCanMakeDamage && CurrentTarget)
		Attack(DeltaSeconds);

	if(WeaponOwner && WeaponOwner->bHasDied)
		AttackParticleComp->Deactivate();
}

void AWeapon::ActivateAttackSFX()
{
	if (AttackParticleComp && AttackParticleComp->HasCompleted())
		AttackParticleComp->Activate(true);
	else if(AttackParticleComp && !AttackParticleComp->HasCompleted())
	{
		AttackParticleComp->Deactivate();
		AttackParticleComp->Activate(true);
	}
}

void AWeapon::Attack(float _dt)
{
	if (WeaponCooldown <= 0)
	{
		WeaponCooldown = WeaponOwner->AttackCooldown / 2;

		ActivateAttackSFX();
		Cast<IInterfaceDamageablePlayer>(CurrentTarget)->I_TakeDamage(Damage, WeaponOwner);
	}
	else
		WeaponCooldown -= _dt;
}

void AWeapon::Attack()
{
	ActivateAttackSFX();

	if(CurrentTarget)
	{
		if(bHasKnockback)
			Cast<IInterfaceDamageablePlayer>(CurrentTarget)->I_ApplyKnockback(-CurrentTarget->GetActorForwardVector() * KnockbackForce + CurrentTarget->GetActorUpVector() * KnockbackForce, true, true);

		Cast<IInterfaceDamageablePlayer>(CurrentTarget)->I_TakeDamage(Damage, WeaponOwner);
	}
}
