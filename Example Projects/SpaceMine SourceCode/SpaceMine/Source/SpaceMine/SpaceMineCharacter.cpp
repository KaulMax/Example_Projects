// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpaceMineCharacter.h"
#include "PlayerWeapon.h"
#include "PlayerBuilder.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

#include "DrawDebugHelpers.h"
#include "MainEnemy.h"
#include "SpaceMineGameInstance.h"
#include "WaveManager.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/RectLightComponent.h"
#include "Components/SpotLightComponent.h"


ASpaceMineCharacter::ASpaceMineCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	MaxDebugBuildTimer = 0.1f;
	MovementSpeedModifier = 1.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	bIsBuilding = false;
	bHasDied = false;

	bTookDamageToggle = false;
	bCanTakeDamage = true;

	CrosshairSize = FVector2D(9.f, -9.f);


	MaxCanTakeDmgTimer = 0.5f;
	CurrCanTakeDmgTimer = MaxCanTakeDmgTimer;

	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	IK_LookTo = FVector(1000, 0, 0);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 350.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	Weapon_ChildActor = CreateDefaultSubobject<UChildActorComponent>("WeaponChild");
	Weapon_ChildActor->CreateChildActor();
	Weapon_ChildActor->SetupAttachment(RootComponent);

	Building_ChildActor = CreateDefaultSubobject<UChildActorComponent>("BuildingChild");
	Building_ChildActor->CreateChildActor();
	Building_ChildActor->SetAbsolute(true, false, true);
	Building_ChildActor->SetupAttachment(RootComponent);

	HeadLamp = CreateDefaultSubobject<USpotLightComponent>("HeadLamp");
	HeadLamp->SetupAttachment(RootComponent);

	HeadLightEmission = CreateDefaultSubobject<URectLightComponent>("HeadLightEmission");
	HeadLightEmission->SetupAttachment(RootComponent);

	HitBox->SetupAttachment(RootComponent);
	DamagedParticleComponent->SetupAttachment(RootComponent);

	CameraCombatOffsetX = 100.f;
	CameraCombatOffsetY = 100.f;
	CameraBoom->SocketOffset.X = CameraCombatOffsetX;
	CameraBoom->SocketOffset.Y = CameraCombatOffsetY;
}

void ASpaceMineCharacter::BeginPlay()
{
	Super::BeginPlay();

	CameraBoom->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, "CameraBoomLocation_Combat");

	HeadLamp->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, "LightSocket");
	HeadLightEmission->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, "LightEmissionSocket");

	Weapon_ChildActor->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocketName);
	Building_ChildActor->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, BuildingSocketName);

	DebugBuildTimer = MaxDebugBuildTimer;

	AnimInstance = SkeletalMeshComponent->GetAnimInstance();

	PlayerCam = UGameplayStatics::GetPlayerCameraManager(World, 0);
	StartPos = GetActorLocation();

	SpaceMineGameInstance = Cast<USpaceMineGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	MovementComponent = GetCharacterMovement();
	PlayerController = Cast<APlayerController>(GetController());

	for(UMaterialInterface* mat : SkeletalMeshComponent->GetMaterials())
	{
		CachedPlayerMats.Add(mat);
	}

}

void ASpaceMineCharacter::I_TakeDamage(float _damage, AMainEnemy* _ref)
{
	if (!bCanTakeDamage)
		return;

	bTookDamageToggle = true;

	if (SpaceMineGameInstance && SpaceMineGameInstance->GodMode)
		return;
	else
	{
		bTookDamageUIFeedback = true;
		BeginTimeline_CameraHitEffect();
		Super::I_TakeDamage(_damage, _ref);
	}
}

float ASpaceMineCharacter::SampleDamage(float _sampleDamage )
{
	float currhp = CurrentHP;
	currhp -= _sampleDamage;

	return currhp;
}

void ASpaceMineCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bTookDamageToggle && CurrCanTakeDmgTimer <= 0)
	{
		bCanTakeDamage = true;
		bTookDamageToggle = false;
	}
	else if (bTookDamage && CurrCanTakeDmgTimer > 0)
	{
		CurrCanTakeDmgTimer -= DeltaSeconds;
		bCanTakeDamage = false;
	}

	if (!bWalkingBack)
	{
		MovementComponent->bUseControllerDesiredRotation = false;
		MovementComponent->bOrientRotationToMovement = true;
	}

	//if (WaveManager && WaveManager->CurrentGamePhase == ECurrentGamePhase::CGP_Fight && bIsBuilding)
	//{
	//	if(SpaceMineGameInstance->GameDifficulty == EGameDifficulty::GD_Easy)
	//		ToggleBuildMode();
	//}

	if (curveTimeline_CameraTogglePos.IsPlaying())
		curveTimeline_CameraTogglePos.TickTimeline(DeltaSeconds);

	if (curveTimeline_CameraHitEffect.IsPlaying())
		curveTimeline_CameraHitEffect.TickTimeline(DeltaSeconds);

	ManagePlayerMesh();

	CheckForViewEnemy();


	PlayerActionDynamic(DeltaSeconds);

	if (!bShootingBullet)
		ShootAnimAlpha -= DeltaSeconds * 5.f;

	SetIK();
	SetWeaponIK();
}

void ASpaceMineCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Turn_Left", IE_Pressed, this, &ASpaceMineCharacter::TurnStructureLeft);
	PlayerInputComponent->BindAction("Turn_Right", IE_Pressed, this, &ASpaceMineCharacter::TurnStructureRight);

	PlayerInputComponent->BindAction("Turn_Left", IE_Released, this, &ASpaceMineCharacter::TurnStructureLeft);
	PlayerInputComponent->BindAction("Turn_Right", IE_Released, this, &ASpaceMineCharacter::TurnStructureRight);

	PlayerInputComponent->BindAction("ToggleBuilding", IE_Pressed, this, &ASpaceMineCharacter::ToggleBuildMode);

	PlayerInputComponent->BindAxis("StructureSelection", this, &ASpaceMineCharacter::SwitchSelectedStructure);

	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &ASpaceMineCharacter::PlayerActionStatic);
	PlayerInputComponent->BindAction("Action", IE_Released, this, &ASpaceMineCharacter::PlayerActionStaticRelease);

	PlayerInputComponent->BindAction("SkipWave", IE_Pressed, this, &ASpaceMineCharacter::SkipToWave);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASpaceMineCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpaceMineCharacter::MoveRight);

	PlayerInputComponent->BindAction("OnBackWalkEnd", IE_Released,this, &ASpaceMineCharacter::OnBackWalkEnd);

	PlayerInputComponent->BindAxis("Turn", this, &ASpaceMineCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ASpaceMineCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("WaveInfo", IE_Pressed, this, &ASpaceMineCharacter::ToggleWaveInfo);
}

void ASpaceMineCharacter::PlayerActionStaticRelease()
{
	if (bHasDied || bPaused)
		return;

	bShootingBullet = false;
	bShootingFire = false;
	CurrentAnimTime = 0;
	WeaponBP->ShootBullet(false , nullptr, PlayerController);
	WeaponBP->ShootFire(false);
}

void ASpaceMineCharacter::SkipToWave()
{
	if (WaveManager->CurrentWave > WaveManager->SpawnTypeAmountTimePair.Num())
		return;

	WaveManager->SpawnWaveManual = true;
}

void ASpaceMineCharacter::PlayerActionDynamic(float DeltaSeconds)
{
	if (bHasDied || bPaused)
		return;

	if (bShootingBullet || bShootingFire)
	{
		if (bShootingBullet)
		{
			if (CurrentAnimTime <= 0)
			{
				CurrentAnimTime = .25f;
				AnimInstance->Montage_Play(CombatMontage, 1.f);
				AnimInstance->Montage_JumpToSection(FName("Attack_1"), CombatMontage);
				
				WeaponBP->ShootBullet(true, nullptr, PlayerController);
			}
			else 
				CurrentAnimTime -= DeltaSeconds;
		}
		else if (bShootingFire)
		{
			WeaponBP->ShootFire(true);

			AnimInstance->Montage_Play(CombatMontage, 1.f);
			AnimInstance->Montage_JumpToSection(FName("Attack_1"), CombatMontage);
		}

		SetActorRotation(UKismetMathLibrary::RInterpTo(GetActorRotation(), FRotator(0, Controller->GetControlRotation().Yaw, 0), 1.f, .1f));
	}
}

void ASpaceMineCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (bHasDied || bPaused)
		return;

		Jump();
}

void ASpaceMineCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (bHasDied || bPaused)
		return;

		StopJumping();
}

void ASpaceMineCharacter::OnBackWalkEnd( )
{
	bWalkingBack = false;
}

void ASpaceMineCharacter::BeginTimeline_CameraTogglePos()
{
	FOnTimelineFloat timelineprogress;

	timelineprogress.BindUFunction(this, FName("TickTimeline_CameraTogglePos"));

	curveTimeline_CameraTogglePos.AddInterpFloat(curveFloat_CameraTogglePos, timelineprogress);

	curveTimeline_CameraTogglePos.PlayFromStart();
}

void ASpaceMineCharacter::TickTimeline_CameraTogglePos(float _alpha)
{
	if(bIsBuilding)
	{
		if (_alpha >= 0.5)
			bReachedBuildPos = true;

		CameraBoom->SocketOffset.X = FMath::Lerp(CameraBoom->SocketOffset.X, 0.f, _alpha);
		CameraBoom->SocketOffset.Y = FMath::Lerp(CameraBoom->SocketOffset.Y, 0.f, _alpha);
	}
	else
	{
		bReachedBuildPos = false;

		CameraBoom->SocketOffset.X = FMath::Lerp(CameraBoom->SocketOffset.X, CameraCombatOffsetX, _alpha);
		CameraBoom->SocketOffset.Y = FMath::Lerp(CameraBoom->SocketOffset.Y, CameraCombatOffsetY, _alpha);
	}
}

void ASpaceMineCharacter::TurnAtRate(float Rate)
{
	if (bHasDied || bPaused)
		return;

	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASpaceMineCharacter::ToggleWaveInfo()
{
	if (bHasDied || bPaused)
		return;

	bToggleWaveInfo = !bToggleWaveInfo;
}

void ASpaceMineCharacter::TurnStructureRight()
{
	if (bHasDied || bPaused)
		return;

	if(bIsBuilding)
		BuilderBP->TurnRight();
}

void ASpaceMineCharacter::TurnStructureLeft()
{
	if (bHasDied || bPaused)
		return;

	if(bIsBuilding)
		BuilderBP->TurnLeft();
}

void ASpaceMineCharacter::ToggleBuildMode()
{
	if (bHasDied || bPaused)
		return;

	if(bShootingBullet || bShootingFire)
		PlayerActionStaticRelease();

	if(!bIsBuilding)
		BuilderBP->SwitchBuildStructure(5);

	//if (WaveManager->CurrentGamePhase == ECurrentGamePhase::CGP_Fight)
	//	bIsBuilding = false;
	//else
	bIsBuilding = !bIsBuilding;

	if (bIsBuilding)
		CameraBoom->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "CameraBoomLocation_Build");
	else if (!bIsBuilding)
		CameraBoom->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "CameraBoomLocation_Combat");

	BeginTimeline_CameraTogglePos();
}

void ASpaceMineCharacter::SwitchSelectedStructure(float _structureIdx)
{
	if (bHasDied || bPaused)
		return;

	if(WaveManager && bIsBuilding && WaveManager->CurrentGamePhase == ECurrentGamePhase::CGP_Build)
		BuilderBP->SwitchBuildStructure(_structureIdx);
	else if(WaveManager && bIsBuilding && WaveManager->CurrentGamePhase == ECurrentGamePhase::CGP_Fight)
		BuilderBP->SwitchBuildStructure(5);
	else
		BuilderBP->SwitchBuildStructure(-1);
}

void ASpaceMineCharacter::SubscribeBuilder(APlayerBuilder* _builder)
{
	BuilderBP = _builder;
}

void ASpaceMineCharacter::SubscribeWeapon(APlayerWeapon* _weapon)
{
	WeaponBP = _weapon;
}

void ASpaceMineCharacter::LookUpAtRate(float Rate)
{
	if (UGameplayStatics::GetGlobalTimeDilation(World) <= 0.1f || bHasDied || bPaused)
		return;

	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASpaceMineCharacter::PlayerActionStatic()
{
	if (bHasDied || bPaused)
		return;

	if (!bIsBuilding && WeaponBP)
	{
		if(PlayerController->WasInputKeyJustPressed(EKeys::LeftMouseButton))
		{
			bShootingBullet = !bShootingBullet;

			if (bShootingBullet)
				ShootAnimAlpha = 1.f;
		}
		else if(PlayerController->WasInputKeyJustPressed(EKeys::RightMouseButton))
		{
			bShootingFire = !bShootingFire;

			if (bShootingFire)
				ShootAnimAlpha = .5f;
		}
	}
	else if(bIsBuilding && BuilderBP)
		BuilderBP->StructureAction();
}

void ASpaceMineCharacter::MoveForward(float Value)
{
	if (bHasDied || bPaused)
		return;

	if (UGameplayStatics::GetGlobalTimeDilation(World) <= 0.1f)
		return;

	if ((Controller != nullptr) && (Value != 0.0f))
	{
		if(bIsBuilding && bReachedBuildPos && MovementComponent->IsMovingOnGround())
		{
			if (curveTimeline_CameraWalkShake.IsPlaying())
				curveTimeline_CameraWalkShake.TickTimeline(World->GetDeltaSeconds());
			else
			{
				bWalkShakeToggle = !bWalkShakeToggle;
				//CameraBoom->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "CameraBoomLocation_Build");
				BeginTimeline_CameraWalkShake();
			}
		}

		if (Value < 0.0f) 
		{
			Value += MovementSpeedModifier;
			bWalkingBack = true;
			MovementComponent->bUseControllerDesiredRotation = true;
			MovementComponent->bOrientRotationToMovement = false;
		}
		else
		{
			bWalkingBack = false;
			MovementComponent->bUseControllerDesiredRotation = false;
			MovementComponent->bOrientRotationToMovement = true;
		}

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);

	}

	if(Value == 0 && curveTimeline_CameraWalkShake.IsPlaying() && bIsBuilding)
	{
		curveTimeline_CameraWalkShake.Stop();
		//CameraBoom->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "CameraBoomLocation_Build_Idle");
	}
}


void ASpaceMineCharacter::MoveRight(float Value)
{
	if (bHasDied || bPaused)
		return;

	if (UGameplayStatics::GetGlobalTimeDilation(World) <= 0.1f)
		return;

	if ( (Controller != nullptr) && (Value != 0.0f))
	{
		if (Value < 0 && MovementComponent->bUseControllerDesiredRotation)
			Value += MovementSpeedModifier * 1.5f;
		else if(Value > 0 && MovementComponent->bUseControllerDesiredRotation)
			Value -= MovementSpeedModifier * 1.5f;

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}

void ASpaceMineCharacter::BeginTimeline_CameraHitEffect()
{
	FOnTimelineFloat timelineprogress;

	timelineprogress.BindUFunction(this, FName("TickTimeline_CameraHitEffect"));

	curveTimeline_CameraHitEffect.AddInterpFloat(curveFloat_CameraHitEffect, timelineprogress);
	curveTimeline_CameraHitEffect.SetPlayRate(10.f);

	randCamShake = FMath::RandRange(0, 1);

	curveTimeline_CameraHitEffect.PlayFromStart();
}

void ASpaceMineCharacter::TickTimeline_CameraHitEffect(float _alpha)
{
	if(randCamShake == 1)
	{
		if (!bIsBuilding)
			CameraBoom->SocketOffset = FVector(CameraCombatOffsetX - _alpha, CameraCombatOffsetY - _alpha, _alpha);
		else if (bIsBuilding)
			CameraBoom->SocketOffset = FVector(-_alpha, -_alpha, _alpha);
	}
	else
	{
		if (!bIsBuilding)
			CameraBoom->SocketOffset = FVector(CameraCombatOffsetX + _alpha, CameraCombatOffsetY + _alpha, -_alpha);
		else if (bIsBuilding)
			CameraBoom->SocketOffset = FVector(+_alpha, +_alpha, -_alpha);
	}
}

void ASpaceMineCharacter::BeginTimeline_CameraWalkShake()
{
	FOnTimelineFloat timelineprogress;

	timelineprogress.BindUFunction(this, FName("TickTimeline_CameraWalkShake"));

	curveTimeline_CameraWalkShake.AddInterpFloat(curveFloat_CameraWalkShake, timelineprogress);
	curveTimeline_CameraWalkShake.SetPlayRate(10.f);

	curveTimeline_CameraWalkShake.PlayFromStart();
}

void ASpaceMineCharacter::TickTimeline_CameraWalkShake(float _alpha)
{
	_alpha *= 2.f;

	if (bWalkShakeToggle)
	{
		if (!bIsBuilding)
			CameraBoom->SocketOffset = FVector(0 - _alpha, 0 - _alpha, _alpha);
		else if (bIsBuilding)
			CameraBoom->SocketOffset = FVector(-_alpha, -_alpha, _alpha);
	}
	else
	{
		if (!bIsBuilding)
			CameraBoom->SocketOffset = FVector(0 + _alpha, 0 + _alpha, -_alpha);
		else if (bIsBuilding)
			CameraBoom->SocketOffset = FVector(+_alpha, +_alpha, -_alpha);
	}
}

void ASpaceMineCharacter::CheckForViewEnemy()
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

	const TArray<AActor*> emptyActor = { this};

	UKismetSystemLibrary::LineTraceSingleByProfile(World, worldpos, worldpos + worlddir * 5000.f, "BlockAll",
		false, emptyActor, EDrawDebugTrace::None, hit, true, FColor::Transparent, FColor::Transparent, 0.f);


	if(AMainEnemy* enemy = Cast<AMainEnemy>(hit.GetActor()))
	{
		resethandle.Invalidate();

		CachedEnemies.Add(enemy);
		currLookEnemy = enemy;
		enemy->bActivateHealthBar = true;
	}
	else
	{
		currLookEnemy = nullptr;
		GetWorld()->GetTimerManager().SetTimer(resethandle, this, &ASpaceMineCharacter::ResetEnemiesInView, 1.f, false);
	}
}

void ASpaceMineCharacter::ResetEnemiesInView()
{
	for (size_t i = 0; i < CachedEnemies.Num(); i++)
	{
		if (!CachedEnemies[i])
			return;

		if(CachedEnemies[i] != currLookEnemy || !currLookEnemy)
			CachedEnemies[i]->bActivateHealthBar = false;
	}

	CachedEnemies.Reset();

	if (currLookEnemy)
		CachedEnemies.Add(currLookEnemy);
}

void ASpaceMineCharacter::PlayDeath()
{
	Super::PlayDeath();

	HeadLamp->DestroyComponent(false);
	HeadLightEmission->DestroyComponent(false);

	SkeletalMeshComponent->SetSimulatePhysics(true);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	PlayerController->StopMovement();

	CapsuleComp->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PlayerController->UnPossess();
}

void ASpaceMineCharacter::SetIK()
{
	FVector worlddir = GetFollowCamera()->GetForwardVector();
	FVector location = GetActorLocation();

	FHitResult hit;

	const TArray<AActor*> emptyActor = { this  };

	UKismetSystemLibrary::LineTraceSingleByProfile(World, location, location + worlddir * 50000.f, "BlockAll",
		false, emptyActor, EDrawDebugTrace::None, hit, true, FColor::Transparent, FColor::Transparent, 0.f);

	FVector dirtohit = hit.ImpactPoint - location;
	dirtohit.Normalize();

	dirtohit = location + (dirtohit * 100.f);

	IK_LookTo = dirtohit;
}

void ASpaceMineCharacter::ManagePlayerMesh()
{
	FVector camtoplayerlenght = GetActorLocation() - FollowCamera->GetComponentLocation();

	if (camtoplayerlenght.Size() <= 80.f)
	{
		for (size_t i = 0; i < SkeletalMeshComponent->GetMaterials().Num(); i++)
		{
			SkeletalMeshComponent->SetMaterial(i, FadeMaterials[i]);

			SkeletalMeshComponent->SetScalarParameterValueOnMaterials("Fade", .75f);
		}
	}
	else
	{
		for (size_t i = 0; i < SkeletalMeshComponent->GetMaterials().Num(); i++)
		{
			SkeletalMeshComponent->SetMaterial(i, CachedPlayerMats[i]);
		}
	}
}

void ASpaceMineCharacter::SetWeaponIK()
{
	if (!Weapon_ChildActor)
		return;

	FVector worlddir;
	FVector worldpos;

	float crosshairPosX = UWidgetLayoutLibrary::GetViewportSize(World).X / 2;
	float crosshairPosY = UWidgetLayoutLibrary::GetViewportSize(World).Y / 3;

	crosshairPosX -= CrosshairSize.X;
	crosshairPosY -= CrosshairSize.Y;

	FVector2D viewPortPos = FVector2D(crosshairPosX, crosshairPosY);

	UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(World, 0), viewPortPos, worldpos, worlddir);

	FHitResult hit;

	const TArray<AActor*> emptyActor = { this};

	UKismetSystemLibrary::LineTraceSingleByProfile(World, worldpos, worldpos + worlddir * 50000.f, "BlockAll",
		false, emptyActor, EDrawDebugTrace::None, hit, true, FColor::Transparent, FColor::Transparent, 0.f);

	if (!hit.bBlockingHit)
		return;

	WeaponIK = hit.ImpactPoint - Weapon_ChildActor->GetComponentLocation();
	WeaponIK.Normalize();
}
