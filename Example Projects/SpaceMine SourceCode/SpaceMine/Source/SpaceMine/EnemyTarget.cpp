// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTarget.h"

#include "DamageUISpawn.h"
#include "MainEnemy.h"
#include "PlayerBuilder.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "ResourceManager.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AEnemyTarget::AEnemyTarget()
{
	PrimaryActorTick.bCanEverTick = true;

	MaxHP = 100;
	CurrentHP = MaxHP;
	HitBoxExtend = FVector(25.f, 25.f, 25.f);

	HitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	HitBox->SetupAttachment(GetRootComponent());
	HitBox->InitBoxExtent(HitBoxExtend);

	maxMeshUpdateDebug = 1.f;
	currMeshUpdateDebug = maxMeshUpdateDebug;

	bTookDamage = false;
	bHasDeathPhysics = false;
	bCanTakeDamage = true;

	CapsuleComp = GetCapsuleComponent();

	DamagedParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>("DamagedParticleComponent");
	DamagedParticleComponent->SetupAttachment(GetRootComponent());

	RepairParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>("RepairParticleComponent");
	RepairParticleComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AEnemyTarget::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();

	SkeletalMeshComponent = GetMesh();
}

void AEnemyTarget::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (!ResourceManager && ResourceManagerSub)
		UGameplayStatics::GetActorOfClass(GetWorld(), ResourceManagerSub);

	if(SkeletalMeshComponent->bRenderCustomDepth)
	{
		if (currMeshUpdateDebug <= 0)
		{
			currMeshUpdateDebug = maxMeshUpdateDebug;
			SkeletalMeshComponent->bRenderCustomDepth = false;
			SkeletalMeshComponent->MarkRenderStateDirty();
		}
		else
			currMeshUpdateDebug -= _deltaTime;
	}
}

// Called to bind functionality to input
void AEnemyTarget::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AEnemyTarget::SetIsWatched(bool _status, APlayerBuilder* _builderRef)
{
	BuilderRef = _builderRef;
	bIsBeignWatched = _status;
}

void AEnemyTarget::I_TakeDamage(float _damage, AMainEnemy* _ref)
{
	IInterfaceDamageablePlayer::I_TakeDamage(_damage, _ref);

	if (CurrentHP - _damage > 0)
	{
		if (!bCanTakeDamage)
			return;

		bTookDamage = true;

		CurrentHP -= _damage;

		if(DamageUIText)
		{
			ADamageUISpawn* damagetext = World->SpawnActor<ADamageUISpawn>(DamageUIText, GetActorLocation(), GetActorRotation());
			damagetext->InitDamageText(_damage, this, true, false, false);
		}

		FTimerHandle DamageToggleHandle;

		GetWorld()->GetTimerManager().SetTimer(DamageToggleHandle, this, &AEnemyTarget::OnResetDamageToggle, 0.5f, false);
		bCanTakeDamage = false;

		if (DamagedParticleComponent)
			DamagedParticleComponent->SetActive(true);

		if (!AnimInstance || !CombatMontage)
			return;
	}
	if (CurrentHP - _damage <= 0 || CurrentHP <= 0)
		PlayDeath();
}

void AEnemyTarget::I_ApplyKnockback(FVector _launchVelo, bool _bXYOverride, bool __bZOverride)
{
	IInterfaceDamageablePlayer::I_ApplyKnockback(_launchVelo, _bXYOverride, __bZOverride);

	if(TargetType == EEnemyTargetType::ETT_Player)
		LaunchCharacter(_launchVelo, _bXYOverride, __bZOverride);
}

void AEnemyTarget::PlayDeath()
{
	bHasDied = true;

	for (size_t i = 0; i < SkeletalMeshComponent->GetNumMaterials(); i++)
	{
		if(FadeMaterials[i])
			SkeletalMeshComponent->SetMaterial(i, FadeMaterials[i]);
	}

	CapsuleComp->SetCollisionObjectType(ECollisionChannel::ECC_Camera);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetGenerateOverlapEvents(false);

	HitBox->SetCollisionObjectType(ECollisionChannel::ECC_Camera);
	HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBox->SetGenerateOverlapEvents(false);

	SkeletalMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_Camera);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkeletalMeshComponent->SetGenerateOverlapEvents(false);

	CapsuleComp->bDynamicObstacle = false;
	TSubclassOf<class UNavAreaBase> AreaClass;

	CapsuleComp->AreaClass = AreaClass;
}

void AEnemyTarget::CleanAfterDeath()
{
	Destroy();
}

void AEnemyTarget::OnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{

}

void AEnemyTarget::OnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex)
{

}

void AEnemyTarget::RepairCurrStructure()
{
	if (CurrentHP >= MaxHP)
		return;

	if (ResourceManager->HasEnoughResources(0, (MaxHP - CurrentHP) / 5.f))
	{
		bWasRepaired = true;
		ResourceManager->DeductResources(0, (MaxHP - CurrentHP) / 5.f);
		bWasRepaired = false;

		CurrentHP = MaxHP;

		if (DamagedParticleComponent)
			DamagedParticleComponent->SetActive(false);

		if (RepairParticleComponent)
			RepairParticleComponent->SetActive(true);
	}
}

void AEnemyTarget::OnResetDamageToggle()
{
	bCanTakeDamage = true;
}
