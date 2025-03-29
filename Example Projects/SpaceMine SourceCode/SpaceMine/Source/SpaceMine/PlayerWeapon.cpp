// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeapon.h"

#include "DrawDebugHelpers.h"
#include "MainEnemy.h"
#include "Projectile.h"
#include "SpaceMineCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
APlayerWeapon::APlayerWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageType = EDamageType::DT_Normal;

	Damage = 10.f;
	ProjectileSpeed = 10.f;

	FireRate = 0.5f;
	//FireRate = MaxFireRate;

	CrosshairSize = FVector2D(9.f, -9.f);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	RootComponent = SkeletalMeshComp;

	FireExtentRoPoint = CreateDefaultSubobject<UStaticMeshComponent>("FireExtentRoPoint");
	FireExtentRoPoint->SetupAttachment(GetRootComponent());

	FireExtent = CreateDefaultSubobject<UStaticMeshComponent>("FireExtent");
	FireExtent->SetupAttachment(FireExtentRoPoint);

	AttackParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("AttackParticle");
	AttackParticleComp->SetupAttachment(FireExtentRoPoint);

	ShootParticle = CreateDefaultSubobject<UParticleSystemComponent>("ShootParticle");
	FireExtent->SetupAttachment(FireExtentRoPoint);
}

// Called when the game starts or when spawned
void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (AttackParticleComp)
		AttackParticleComp->Deactivate();

	WeaponOwner = Cast<ASpaceMineCharacter>(GetParentActor());
	
	WeaponOwner->SubscribeWeapon(this);
	
	PlayerCamera = WeaponOwner->GetFollowCamera();
	PlayerCameraBoom = WeaponOwner->GetCameraBoom();

	if(SkeletalMeshComp)
		GunpointSocket = SkeletalMeshComp->GetSocketByName(GunpointSocketName);
	
	Damage = WeaponOwner->AttackDamage;
	
	World = GetWorld();
	CameraBoomPlayer = WeaponOwner->GetCameraBoom();

	if (!WeaponOwner)
		return;

	if (!FireExtent)
		return;

	FireExtent->OnComponentBeginOverlap.AddDynamic(this, &APlayerWeapon::APlayerWeapon::OnOverlapFireDmgBegin);
	FireExtent->OnComponentEndOverlap.AddDynamic(this, &APlayerWeapon::APlayerWeapon::OnOverlapFireDmgEnd);
}

void APlayerWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (WeaponOwner && WeaponOwner->bHasDied)
		AttackParticleComp->Deactivate();

	if (curveTimeline.IsPlaying())
		curveTimeline.TickTimeline(DeltaSeconds);
}


void APlayerWeapon::ActivateAttackSFX()
{
	if (AttackParticleComp && !bAnimToggle)
	{
		bAnimToggle = true;
		AttackParticleComp->Activate(true);
	}
}

void APlayerWeapon::ShootBullet(bool _status, AActor* _target, APlayerController* _player)
{
	if(!_status)
	{
		bShootProjectile = false; 
		return;
	}

	bShootProjectile = true;
	Damage_Bullet(_target); bShootProjectile = false;
}

void APlayerWeapon::ShootFire(bool _status)
{
	if (!_status)
	{
		bShootFire = false;
		bAnimToggle = false;

		if(AttackParticleComp)
			AttackParticleComp->Deactivate();

		return;
	}

	ActivateAttackSFX();

	FVector worlddir;
	FVector worldpos;

	float crosshairPosX = UWidgetLayoutLibrary::GetViewportSize(World).X / 2;
	float crosshairPosY = UWidgetLayoutLibrary::GetViewportSize(World).Y / 3;

	crosshairPosX -= CrosshairSize.X;
	crosshairPosY -= CrosshairSize.Y;

	FVector2D viewPortPos = FVector2D(crosshairPosX, crosshairPosY);

	UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(World, 0), viewPortPos, worldpos, worlddir);

	FHitResult hit;

	const TArray<AActor*> emptyActor = { this , WeaponOwner };

	UKismetSystemLibrary::LineTraceSingleByProfile(World, worldpos, worldpos + worlddir * 5000.f, "BlockAll",
		false, emptyActor, EDrawDebugTrace::None, hit, true, FColor::Transparent, FColor::Transparent, 0.f);

	FRotator look = UKismetMathLibrary::FindLookAtRotation(WeaponOwner->GetActorLocation(), hit.ImpactPoint);

	FireExtentRoPoint->SetWorldRotation(look);

	if (!GetWorldTimerManager().IsTimerActive(TimerHandle_Fire))
	{
		FTimerDelegate shootdelegate;
		shootdelegate.BindUFunction(this, FName("Damage_Fire"));

		GetWorldTimerManager().SetTimer(TimerHandle_Fire, shootdelegate, FireRate, false);
	}

	if(!curveTimeline.IsPlaying())
		BeginTimeline(1.5f);

	if (!bShootFire)
		bShootFire = true;
}

void APlayerWeapon::Damage_Bullet(AActor* _target)
{
	FVector worlddir;
	FVector worldpos;

	float crosshairPosX = UWidgetLayoutLibrary::GetViewportSize(World).X / 2;
	float crosshairPosY = UWidgetLayoutLibrary::GetViewportSize(World).Y / 3;

	crosshairPosX -= CrosshairSize.X;
	crosshairPosY -= CrosshairSize.Y;

	FVector2D viewPortPos = FVector2D(crosshairPosX, crosshairPosY);

	UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(World, 0), viewPortPos, worldpos, worlddir);

	FHitResult hit;

	const TArray<AActor*> emptyActor = { this , WeaponOwner };

	UKismetSystemLibrary::LineTraceSingleByProfile(World, worldpos, worldpos + worlddir * 5000.f, "BlockAll",
		false, emptyActor, EDrawDebugTrace::None, hit, true, FColor::Transparent, FColor::Transparent, 0.f);

	float speed = ProjectileSpeed + WeaponOwner->GetVelocity().X;

	FVector socketLockation = GunpointSocket->GetSocketLocation(SkeletalMeshComp);

	AProjectile* projectile = World->SpawnActor<AProjectile>(Projectile, socketLockation, FRotator(0));

	ShootParticle->Activate(true);

	BeginTimeline(7.f);

	GunIKLookPos = hit.ImpactPoint - GetActorLocation();

	projectile->SetProjectileStats(Damage, speed / 2, _target, DamageType, false, hit.ImpactPoint, socketLockation, WeaponOwner, true);
}

void APlayerWeapon::Damage_Fire()
{
	for (size_t i = 0; i < DamageEnemies.Num(); i++)
	{
		if (DamageEnemies[i] && !DamageEnemies[i]->bHasDied)
		{
			DamageEnemies[i]->TakeDamage(Damage, EDamageType::DT_Crystal, this);
			
			WeaponOwner->bMadeDamage = true;
		}
	}
}

void APlayerWeapon::OnOverlapFireDmgBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor,UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if(AMainEnemy* enemy = Cast<AMainEnemy>(_otherActor))
	{
		if (!DamageEnemies.Contains(enemy))
			DamageEnemies.Add(enemy);

		enemy->bActivateHealthBar = true;
	}
}

void APlayerWeapon::OnOverlapFireDmgEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex)
{
	if (AMainEnemy* enemy = Cast<AMainEnemy>(_otherActor))
	{
		if (DamageEnemies.Contains(enemy))
			DamageEnemies.Remove(enemy);

		enemy->bActivateHealthBar = false;
	}
}

void APlayerWeapon::BeginTimeline(float _playRate)
{
	FOnTimelineFloat timelineprogress;

	timelineprogress.BindUFunction(this, FName("TickTimeline"));

	curveTimeline.AddInterpFloat(curveFloat, timelineprogress);
	curveTimeline.SetPlayRate(_playRate);
	//curveTimeline.SetLooping(true);

	randCamShake = FMath::RandRange(0, 1);

	curveTimeline.PlayFromStart();
}

void APlayerWeapon::TickTimeline(float _alpha)
{
	if(randCamShake == 1)
	{
		PlayerCameraBoom->SocketOffset = FVector(WeaponOwner->CameraCombatOffsetX - _alpha, WeaponOwner->CameraCombatOffsetY - _alpha, _alpha);

		WeaponOwner->GetFollowCamera()->SetRelativeRotation(FRotator(0, 0, FMath::Lerp(0.f, .05f, _alpha * 10.f)));
	}
	else
	{
		PlayerCameraBoom->SocketOffset = FVector(WeaponOwner->CameraCombatOffsetX + _alpha, WeaponOwner->CameraCombatOffsetY + _alpha, -_alpha);

		WeaponOwner->GetFollowCamera()->SetRelativeRotation(FRotator(0, 0, FMath::Lerp(0.f, -.05f, _alpha * 10.f)));
	}
}