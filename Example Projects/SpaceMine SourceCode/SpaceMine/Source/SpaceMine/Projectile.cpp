#include "Projectile.h"

#include "EnemySpawner.h"
#include "MainEnemy.h"
#include "PlayerWeapon.h"
#include "SpaceMineCharacter.h"
#include "TowerBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;

	HitBox = CreateDefaultSubobject<USphereComponent>("HitBox");
	HitBox->SetupAttachment(GetRootComponent());

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	ProjectileMesh->SetupAttachment(GetRootComponent());

	bFollow = false;
	bIsInit = false;
	bTargetHasDied = false;

	Damage = 0;
	LifeTime = 10.f;
	ProjectileSpeed = 0;

	DamageType = EDamageType::DT_Normal;
}

void AProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bIsInit)
		return;

	if(!bTargetHasDied && bFollow && TargetActor)
	{
		FVector alpha = TargetActor->GetActorLocation() - GetActorLocation();
		alpha.Normalize();
		alpha *= ProjectileSpeed;

		FRotator lookrot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetActor->GetActorLocation());
		MeshComponent->MoveComponent(alpha, lookrot,false);

		if (TargetActor->bHasDied)
			bTargetHasDied = true;
	}
	else if(bFollow && bTargetHasDied && !bHitTarget)
		MeshComponent->AddForce(GetActorForwardVector() * (ProjectileSpeed * 100000) * DeltaSeconds);
	else if(!bFollow && !bHitTarget)
	{
		speed += (DeltaSeconds / (EndPos - StartPos).Size()) * ProjectileSpeed;

		SetActorLocation(UKismetMathLibrary::VLerp(StartPos, EndPos, speed));

		if (speed >= 1.1f)
			DestroyProjectile();
	}


	if (bTargetHasDied && !bDeathToggle && LifeTime > 1.f)
	{
		LifeTime = 1.f;
		bDeathToggle = true;
	}

	if (LifeTime > 0.f)
		LifeTime -= DeltaSeconds;
	else if (LifeTime <= 0.f)
		DestroyProjectile();
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if (bHitTarget)
		return;

	if (Cast<AMainEnemy>(_otherActor) && Cast<UCapsuleComponent>(_otherComp))
	{
		HitEnemy = Cast<AMainEnemy>(_otherActor);

		if (HitEnemy && !HitEnemy->bHasDied)
		{
			bHitTarget = true;

			ProjectileMesh->SetMaterial(0, TranslucentMat);

			ProjectileMesh->SetSimulatePhysics(false);
			ProjectileMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
			ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			MeshComponent->SetSimulatePhysics(false);
			MeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
			MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			if (!HitEnemy || HitEnemy->bHasDied)
				return;

			if(HitEnemy && HitEnemy->DamagePreview(Damage, DamageType))
			{
				HitEnemy->TakeDamage(HitEnemy->CurrentHP, HitEnemy->DamageWeakness, WeaponOwner);

				if(WeaponOwner)
					WeaponOwner->bMadeDamage = true;
			}
			else if(HitEnemy)
			{
				HitEnemy->TakeDamage(Damage, DamageType, WeaponOwner);

				if(WeaponOwner)
					WeaponOwner->bMadeDamage = true;
			}
		}
	}
}

void AProjectile::OnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex)
{

}

void AProjectile::OnOverlapBeginEnvi(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if(!Cast<AMainEnemy>(_otherActor) && !Cast<ASpaceMineCharacter>(_otherActor) && !Cast<AProjectile>(_otherActor) && !Cast<ATowerBase>(_otherActor) && !Cast<APlayerWeapon>(_otherActor))
		DestroyProjectile();
	
}

void AProjectile::SetProjectileStats(float _damage, float _projectileSpeed, AActor* _targetActor, EDamageType _damageType, bool _followStatus, FVector _endPos, FVector _startPos, ASpaceMineCharacter* _weaponOwner, bool _playerOwned)
{
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::AProjectile::OnOverlapBegin);
	HitBox->OnComponentEndOverlap.AddDynamic(this, &AProjectile::AProjectile::OnOverlapEnd);

	ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::AProjectile::OnOverlapBeginEnvi);

	Damage = _damage;
	StartPos = _startPos;
	EndPos = _endPos;
	bFollow = _followStatus;
	ProjectileSpeed = _projectileSpeed;
	DamageType = _damageType;
	WeaponOwner = _weaponOwner;
	bPlayerOwned = _playerOwned;

	TargetActor = Cast<AMainEnemy>(_targetActor);

	if (!bFollow || !_targetActor)
	{
		FVector dirtohit = _endPos - _startPos;
		dirtohit.Normalize();

		SetActorRelativeRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetActorLocation() + dirtohit));
	}

	bIsInit = true;
}

void AProjectile::DestroyProjectile()
{
	Destroy();
}