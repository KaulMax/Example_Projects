// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBuilder.h"

#include "DrawDebugHelpers.h"
#include "Generator.h"
#include "MainDrill.h"
#include "NoBuildZone.h"
#include "ResourceManager.h"
#include "ResourcePoint.h"
#include "SpaceMineCharacter.h"
#include "SpaceMineGameInstance.h"
#include "TowerBase.h"
#include "WaveManager.h"
#include "Components/BoxComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

APlayerBuilder::APlayerBuilder()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	//RootComponent = SkeletalMeshComponent;

	TowerRangeMeshComponment = CreateDefaultSubobject<UStaticMeshComponent>("RangeMesh");
	TowerRangeMeshComponment->SetupAttachment(SkeletalMeshComponent);

	BuilderHitBox = CreateDefaultSubobject<UBoxComponent>("BuilderHitBox");
	BuilderHitBox->SetupAttachment(SkeletalMeshComponent);

	MineralMiningParticle = CreateDefaultSubobject<UParticleSystemComponent>("MineralMiningParticle");
	MineralMiningParticle->SetupAttachment(SkeletalMeshComponent);

	BuildAngleRestriction = FVector(0.55f, 0.75f, 0.55f);

	bCanBuild = false;
	bCanRepair = false;
	bNotEnoughResources = false;
	bCanMine = false;
	bIsBlocked = false;

	bNoAction = true;

	StructureToBuild = EStructureBuildType::SBT_BoltTurret;

	BuildingRange = 1000.f;
	MinBuildDistance = 100.f;
	BuildHeightAdj = 250.f;
	DebugZPosNormal = 70.f;
	DebugZPosFixed = 90.f;
	RangeIndicatorRotSpeed = 1.f;
	AddToStashValue_Minerals = 15.f;
	AddToStashValue_Crystals = 15.f;

	MaxResourceDeliverTimer = 0.15f;
	CurrResourceDeliverTimer = MaxResourceDeliverTimer;

	MaxMineralExtrationTime = 0.5f;

	ResourceMineAmount = 10.f;

	TurnSpeed = 5.f;
}

void APlayerBuilder::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();

	BuildOwner = Cast<ASpaceMineCharacter>(GetParentActor());
	BuildOwner->SubscribeBuilder(this);

	if (ResourceManagerSub)
	{
		TArray<AActor*> resmanager;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ResourceManagerSub, resmanager);

		if (resmanager.Num() > 0)
			ResourceManager = Cast<AResourceManager>(resmanager[0]);
		else
			ResourceManager = World->SpawnActor<AResourceManager>(ResourceManagerSub, FVector(0), FRotator(0));
	}

	PlayerController = UGameplayStatics::GetPlayerController(World, 0);

	BuildRot.Yaw -= 90.f;

	BuilderHitBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerBuilder::APlayerBuilder::BlockOnOverlapBegin);
	BuilderHitBox->OnComponentEndOverlap.AddDynamic(this, &APlayerBuilder::APlayerBuilder::BlockOnOverlapEnd);

	SpaceMineGameInstance = Cast<USpaceMineGameInstance>(GetGameInstance());

	SwitchBuildStructure(-1);

	if(MineralMiningParticle)
		MineralMiningParticle->Deactivate();

	if (SpaceMineGameInstance && SpaceMineGameInstance->GameDifficulty == EGameDifficulty::GD_EmployeeOfTheMonth)
		bCanMine = true;
}

void APlayerBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!BuildOwner)
		return;

	if (bCanTurnLeft || bCanTurnRight)
		TurnStructure();

	if(!bNoAction)
		CheckBuildPosition();

	if (bCanRepair)
		CheckForStructureInfo();

	if(TowerRangeMeshComponment)
		TowerRangeMeshComponment->SetWorldRotation(FRotator(TowerRangeMeshComponment->GetComponentRotation().Pitch , TowerRangeMeshComponment->GetComponentRotation().Yaw + (RangeIndicatorRotSpeed * DeltaTime), TowerRangeMeshComponment->GetComponentRotation().Roll ));

	if(CurrOverlapActor && Cast<ATowerBase>(CurrOverlapActor) || Cast<ANoBuildZone>(CurrOverlapActor))
		CurrOverlapActor = nullptr;

	CheckPreviewForResources();

	if(!CurrOverlapActor && bIsBlocked && StructureToBuild != EStructureBuildType::SBT_Barrier)
		bIsBlocked = false;

	if (bIsBlocked)
		SetMaterialUnvalid();

	if (bHasOre && PlayerController->IsInputKeyDown(EKeys::LeftMouseButton) && BuildOwner->bIsBuilding)
	{
		if (BuildOwner)
		{
			BuildOwner->AnimInstance->Montage_Play(BuildOwner->CombatMontage, 1.f);
			BuildOwner->AnimInstance->Montage_JumpToSection(FName("Mine_1"), BuildOwner->CombatMontage);
		}

		if (CurrentMineralExtrationTime <= 0)
		{
			if (MineralMiningParticle)
				MineralMiningParticle->Activate(true);

			CurrentMineralExtrationTime = MaxMineralExtrationTime;
			ResourceManager->AddNormalResources(ResourceMineAmount);
			bIsCurrentlyMining = true;
		}
		else
			CurrentMineralExtrationTime -= DeltaTime;
	}
	else
	{
		bIsCurrentlyMining = false;
		if (MineralMiningParticle)
			MineralMiningParticle->Deactivate();
	}

	if (!BuildOwner->bIsBuilding && TowerRangeMeshComponment)
		TowerRangeMeshComponment->SetMaterial(0, TranslucentMaterial);

	if(!BuildOwner->bIsBuilding && MineralMiningParticle)
		MineralMiningParticle->Deactivate();
}

void APlayerBuilder::TurnStructure()
{
	if(bCanTurnLeft)
	{
		BuildRot.Yaw -= TurnSpeed;

		if (BuildRot.Yaw <= -360)
			BuildRot.Yaw = 0;

		SkeletalMeshComponent->SetWorldRotation(BuildRot);
	}

	if(bCanTurnRight)
	{
		BuildRot.Yaw += TurnSpeed;

		if (BuildRot.Yaw >= 360)
			BuildRot.Yaw = 0;

		SkeletalMeshComponent->SetWorldRotation(BuildRot);
	}
}

void APlayerBuilder::CheckBuildPosition()
{
	switch (StructureToBuild)
	{
	case EStructureBuildType::SBT_Drill:
		CheckFixedPosition();
		break;
	case EStructureBuildType::SBT_Barrier:
		CheckNormalPosition();
		break;
	case EStructureBuildType::SBT_FlamethrowerTurret:
		CheckNormalPosition();
		break;
	case EStructureBuildType::SBT_BoltTurret:
		CheckNormalPosition();
		break;
	}
}

void APlayerBuilder::SetMaterialValid()
{
	FHitResult hit;

	const TArray<AActor*> emptyActor = {  };

	UKismetSystemLibrary::LineTraceSingleByProfile(World, BuildPos, FVector(BuildPos.X, BuildPos.Y, BuildPos.Z - 150.f) , "BlockAll",
		false, emptyActor, EDrawDebugTrace::None, hit, true, FColor::Transparent, FColor::Transparent, 0.f);

	if (hit.bBlockingHit && Cast<ATowerBase>(hit.GetActor()))
	{
		SetMaterialUnvalid();
		return;
	}
	else
		bCanBuild = true;

	if (StructureToBuild == EStructureBuildType::SBT_Repair)
	{
		SkeletalMeshComponent->SetMaterial(0, RepairMaterial);
		return;
	}

	if(bNotEnoughResources)
	{
		if (!InsufficientResourcesMaterial)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Insufficient Resources Material"));
			return;
		}

		for (size_t i = 0; i < SkeletalMeshComponent->GetMaterials().Num(); i++)
		{
			SkeletalMeshComponent->SetMaterial(i, InsufficientResourcesMaterial);
		}
	}
	else
	{
		if (!NormalMaterial)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Valid Material"));
			return;
		}

		for (size_t i = 0; i < SkeletalMeshComponent->GetMaterials().Num(); i++)
		{
			SkeletalMeshComponent->SetMaterial(i, NormalMaterial);
		}

		if(StructureToBuild != EStructureBuildType::SBT_Drill && StructureToBuild != EStructureBuildType::SBT_Barrier)
			TowerRangeMeshComponment->SetMaterial(0, RangeMaterial);
	}
}

void APlayerBuilder::SetMaterialUnvalid()
{
	bCanBuild = false;

	if (StructureToBuild == EStructureBuildType::SBT_Repair)
	{
		SkeletalMeshComponent->SetMaterial(0, RepairMaterial);
		return;
	}

	if (!UnvalidMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Unvalid Material"));
		return;
	}

	for (size_t i = 0; i < SkeletalMeshComponent->GetMaterials().Num(); i++)
	{
		SkeletalMeshComponent->SetMaterial(i, UnvalidMaterial);
	}
}

void APlayerBuilder::SetMeshEmpty(bool _bblockHit)
{
	if(_bblockHit)
		SkeletalMeshComponent->SetSkeletalMesh(CachedMesh);
	else if(!_bblockHit)
	{
		TowerRangeMeshComponment->SetMaterial(0, TranslucentMaterial);
		SkeletalMeshComponent->SetSkeletalMesh(EmptyMesh);
	}
}

void APlayerBuilder::CheckNormalPosition()
{
	FVector ltLine = FVector(BuildOwner->GetActorLocation().X, BuildOwner->GetActorLocation().Y, BuildOwner->GetActorLocation().Z + BuildHeightAdj);

	FHitResult hit;

	const TArray<AActor*> emptyActor = { this };

	UKismetSystemLibrary::LineTraceSingleByProfile(World, ltLine, UGameplayStatics::GetPlayerCameraManager(World, 0)->GetActorForwardVector() * BuildingRange + ltLine, "BlockAll",
		false, emptyActor, EDrawDebugTrace::None , hit, true, FColor::Transparent, FColor::Transparent, 0.f);

	float lenghtToBuildPoint = (hit.ImpactPoint - ltLine).SizeSquared() / 1000.f;

	if (hit.bBlockingHit)
	{
		SkeletalMeshComponent->SetWorldRotation(BuildRot);
		SkeletalMeshComponent->SetWorldLocation(hit.ImpactPoint, false, nullptr, ETeleportType::None);

		SetMeshEmpty(true);

		if (hit.ImpactNormal.X <= BuildAngleRestriction.X && hit.ImpactNormal.Y <= BuildAngleRestriction.Y && hit.ImpactNormal.Z >= BuildAngleRestriction.Z &&
			lenghtToBuildPoint >= MinBuildDistance)
		{
			if (!bCanBuild && !bIsBlocked && !Cast<AEnemyTarget>(hit.Actor) && !Cast<ANoBuildZone>(hit.Actor) && !bOutsideBuildArea && !Cast<AResourcePoint>(hit.Actor) 
				 && hit.Actor->ActorHasTag("Build"))
				SetMaterialValid();
			else if(!hit.Actor->ActorHasTag("Build"))
				SetMaterialUnvalid();

			FVector rot = FVector::CrossProduct(SkeletalMeshComponent->GetUpVector(), hit.ImpactNormal);
			float angle = acosf(FVector::DotProduct(GetActorUpVector(), hit.ImpactNormal));

			FQuat quat = FQuat(rot, angle);
			FQuat newQuat = quat * SkeletalMeshComponent->GetComponentQuat();
			FRotator newRot = newQuat.Rotator();

			BuildRot.Roll = newRot.Roll;
			BuildRot.Pitch = newRot.Pitch;

			BuildPos = SkeletalMeshComponent->GetComponentLocation();
			BuildPos.Z += DebugZPosNormal;
		}
		else if(bCanBuild || bIsBlocked)
			SetMaterialUnvalid();
	}
	else if (bCanBuild) 
	{
		SetMeshEmpty(false);
		SetMaterialUnvalid();
	}
}

void APlayerBuilder::CheckFixedPosition()
{
	FVector ltLine = FVector(BuildOwner->GetActorLocation().X, BuildOwner->GetActorLocation().Y, BuildOwner->GetActorLocation().Z + BuildHeightAdj);

	FHitResult hit;

	const TArray<AActor*> emptyActor = { this, BuildOwner };

	UKismetSystemLibrary::LineTraceSingleByProfile(World, ltLine, UGameplayStatics::GetPlayerCameraManager(World, 0)->GetActorForwardVector() * BuildingRange + ltLine, "BlockOre",
		false, emptyActor, EDrawDebugTrace::None, hit, true, FColor::Transparent, FColor::Transparent, 0.f);

	float lenghtToBuildPoint = (hit.ImpactPoint - ltLine).SizeSquared() / 1000.f;

	if (hit.bBlockingHit)
	{
		SkeletalMeshComponent->SetWorldRotation(BuildRot);
		SkeletalMeshComponent->SetWorldLocation(hit.ImpactPoint, false, nullptr, ETeleportType::None);

		SetMeshEmpty(true);

		if (hit.ImpactNormal.X <= BuildAngleRestriction.X && hit.ImpactNormal.Y <= BuildAngleRestriction.Y && hit.ImpactNormal.Z >= BuildAngleRestriction.Z &&
			lenghtToBuildPoint >= MinBuildDistance)
		{
			if (!bCanBuild)
			{
				SetMaterialValid();
				ResourcePoint = Cast<AResourcePoint>(hit.GetActor());
			}

			if (ResourcePoint && !ResourcePoint->bIsEmpty)
				SetMaterialUnvalid();

			FVector rot = FVector::CrossProduct(SkeletalMeshComponent->GetUpVector(), hit.ImpactNormal);
			float angle = acosf(FVector::DotProduct(GetActorUpVector(), hit.ImpactNormal));

			FQuat quat = FQuat(rot, angle);
			FQuat newQuat = quat * SkeletalMeshComponent->GetComponentQuat();
			FRotator newRot = newQuat.Rotator();

			BuildRot.Roll = newRot.Roll;
			BuildRot.Pitch = newRot.Pitch;

			BuildPos = SkeletalMeshComponent->GetComponentLocation();
			BuildPos.Z += DebugZPosFixed;
		}
		else if (bCanBuild)
		{
			ResourcePoint = nullptr;
			SetMaterialUnvalid();
		}
	}
	else if(bCanBuild)
	{
		ResourcePoint = nullptr;
		SetMeshEmpty(false);
		SetMaterialUnvalid();
	}
	else if(!bCanBuild)
	{
		UKismetSystemLibrary::LineTraceSingleByProfile(World, ltLine, UGameplayStatics::GetPlayerCameraManager(World, 0)->GetActorForwardVector() * BuildingRange + ltLine, "BlockAll",
			false, emptyActor, EDrawDebugTrace::None, hit, true, FColor::Transparent, FColor::Transparent, 0.f);

		SetMaterialUnvalid();
		SetMeshEmpty(true);
		SkeletalMeshComponent->SetWorldLocation(hit.ImpactPoint, false, nullptr, ETeleportType::None);
	}
}

void APlayerBuilder::TurnRight()
{
	if (!bCanTurnRight)
		bCanTurnRight = true;
	else
		bCanTurnRight = false;
}

void APlayerBuilder::TurnLeft()
{
	if(!bCanTurnLeft)
		bCanTurnLeft = true;
	else
		bCanTurnLeft = false;
}

void APlayerBuilder::StructureAction()
{
	bBuildAction = true;

	 if (bCanBuild && !bIsBlocked)
		BuildStructure();

	 if (bCanRepair && PlayerController->WasInputKeyJustPressed(EKeys::LeftMouseButton))
			RepairStructure();
}

void APlayerBuilder::BuildStructure()
{
	if (bOutsideBuildArea)
		return;
	ATowerBase* toSpawn = nullptr;

	FRotator relativCompRot = SkeletalMeshComponent->GetComponentRotation();

	if (!bHasOre )
	{
		if(MineralMiningParticle->IsActive())
			MineralMiningParticle->Deactivate();
	}

	switch (StructureToBuild)
	{
	case EStructureBuildType::SBT_BoltTurret:
		if(GunTurret)
		{
			const FStructureCost* structureCost = StructureInfo.Find(EStructureBuildType::SBT_BoltTurret);

			if (ResourceManager->HasEnoughResources(structureCost->normalCost, structureCost->specialCost))
			{
				bNotEnoughResources = false;

				toSpawn = World->SpawnActor<ATowerBase>(GunTurret, BuildPos, relativCompRot);
				if (toSpawn)
				{
					toSpawn->InitStructure(ResourceManager, nullptr);
					ResourceManager->DeductResources(structureCost->normalCost, structureCost->specialCost);
				}
				else
					UE_LOG(LogTemp, Warning, TEXT("Could not be Build -> BUG?!"));
			}
			else
				bNotEnoughResources = true;
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("No Turret Template Selected!"));
		break;

	case EStructureBuildType::SBT_Barrier:
		if(Barrier)
		{
			const FStructureCost* structureCost = StructureInfo.Find(EStructureBuildType::SBT_Barrier);

			if (ResourceManager->HasEnoughResources(structureCost->normalCost, structureCost->specialCost))
			{
				bNotEnoughResources = false;

				toSpawn = World->SpawnActor<ATowerBase>(Barrier, BuildPos, relativCompRot);
				if (toSpawn)
				{
					toSpawn->InitStructure(ResourceManager, nullptr);
					ResourceManager->DeductResources(structureCost->normalCost, structureCost->specialCost);
				}
				else
					UE_LOG(LogTemp, Warning, TEXT("Coulkd not be Build -> BUG?!"));
			}
			else
				bNotEnoughResources = true;
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("No Turret Template Selected!"));
		break;

	case EStructureBuildType::SBT_FlamethrowerTurret:
		if(FlamethrowerTurret)
		{
			const FStructureCost* structureCost = StructureInfo.Find(EStructureBuildType::SBT_FlamethrowerTurret);

			if (ResourceManager->HasEnoughResources(structureCost->normalCost, structureCost->specialCost))
			{
				bNotEnoughResources = false;

				toSpawn = World->SpawnActor<ATowerBase>(FlamethrowerTurret, BuildPos, relativCompRot);
				if (toSpawn)
				{
					toSpawn->InitStructure(ResourceManager, nullptr);
					ResourceManager->DeductResources(structureCost->normalCost, structureCost->specialCost);
				}
				else
					UE_LOG(LogTemp, Warning, TEXT("Coulkd not be Build -> BUG?!"));
			}
			else
				bNotEnoughResources = true;
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("No Turret Template Selected!"));
		break;

	case EStructureBuildType::SBT_Drill:
		if(Drill)
		{
			if(!ResourcePoint)
			{
				UE_LOG(LogTemp, Warning, TEXT("No Resource Point!"));
				return;
			}

			if (!ResourcePoint->bIsEmpty)
			{
				UE_LOG(LogTemp, Warning, TEXT("Resource Full!"));
				return;
			}
			const FStructureCost* structureCost = StructureInfo.Find(EStructureBuildType::SBT_Drill);

			if (ResourceManager->HasEnoughResources(structureCost->normalCost, structureCost->specialCost))
			{
				bNotEnoughResources = false;

				toSpawn = World->SpawnActor<ATowerBase>(Drill, ResourcePoint->Position, ResourcePoint->Rotation);
				if (toSpawn)
				{
					toSpawn->InitStructure(ResourceManager, ResourcePoint);
					ResourcePoint->bIsEmpty = false;
					ResourceManager->DeductResources(structureCost->normalCost, structureCost->specialCost);
				}
				else
					UE_LOG(LogTemp, Warning, TEXT("Coulkd not be Build -> BUG?!"));
			}
			else
				bNotEnoughResources = true;
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("No Turret Template Selected!"));
	default:
		break;
	}
}


void APlayerBuilder::RepairStructure()
{
	if (!CurrentStructure)
		return;

	if (SpaceMineGameInstance->GameDifficulty == EGameDifficulty::GD_EmployeeOfTheMonth)
		return;

	if (Cast<AMainDrill>(CurrentStructure))
		return;

	if (Cast<AGenerator>(CurrentStructure) && SpaceMineGameInstance->GameDifficulty == EGameDifficulty::GD_Hard)
		return;

	CurrentStructure->RepairCurrStructure();
}

void APlayerBuilder::UpgradeStructure()
{
	if (SpaceMineGameInstance->GameDifficulty == EGameDifficulty::GD_EmployeeOfTheMonth)
		return;

	if (ATowerBase* tower = Cast<ATowerBase>(CurrentStructure) )
		tower->UpgradeStructure();
}

void APlayerBuilder::ClearCurrentStructure()
{
	if (!CurrentStructure)
		return;

	CurrentStructure->SetIsWatched(false, this);
	CurrentStructure->SkeletalMeshComponent->bRenderCustomDepth = false;
	CurrentStructure->SkeletalMeshComponent->MarkRenderStateDirty();
	CurrentStructure = nullptr;
	bHasOre = false;
	bIsCurrentlyMining = false;

	if (MineralMiningParticle)
		MineralMiningParticle->Deactivate();
}

void APlayerBuilder::CheckForStructureInfo()
{
	if(bCanMine)
		SkeletalMeshComponent->SetMaterial(0, PlayerDrillMaterial);
	else if(!bCanMine)
		SkeletalMeshComponent->SetMaterial(0, RepairMaterial);

	SkeletalMeshComponent->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.5f));

	FVector ltLine = FVector(BuildOwner->GetActorLocation().X, BuildOwner->GetActorLocation().Y, BuildOwner->GetActorLocation().Z + BuildHeightAdj);

	FHitResult hit;

	const TArray<AActor*> emptyActor = { this, BuildOwner };

	UKismetSystemLibrary::LineTraceSingleByProfile(World, ltLine, UGameplayStatics::GetPlayerCameraManager(World, 0)->GetActorForwardVector() * BuildingRange + ltLine, "BlockAll",
		false, emptyActor, EDrawDebugTrace::None, hit, true, FColor::Transparent, FColor::Transparent, 0.f);

	float lenghtToBuildPoint = (hit.ImpactPoint - ltLine).SizeSquared() / 1000.f;

	if (hit.bBlockingHit)
	{
		SkeletalMeshComponent->SetWorldRotation(BuildRot);

		SetMeshEmpty(true);

		if (Cast<AMainDrill>(hit.GetActor()))
		{
			bLooksAtMainDrill = true;

			if (PlayerController->WasInputKeyJustPressed(EKeys::RightMouseButton))
			{
				switch (SpaceMineGameInstance->GameDifficulty)
				{
				case EGameDifficulty::GD_Easy:
					if (MainDrill->bAllGeneratorsDestroyed && !bCanMine)
						bCanMine = true;
					else if (MainDrill->bAllGeneratorsDestroyed && bCanMine)
						bCanMine = false;
					break;

				case EGameDifficulty::GD_Normal:
					if (!bCanMine && BuildOwner->WaveManager->CurrentGamePhase == ECurrentGamePhase::CGP_Build)
						bCanMine = true;
					else if (bCanMine)
						bCanMine = false;
					break;

				case EGameDifficulty::GD_Hard:
					if (!MainDrill->bIsActive && !bCanMine)
						bCanMine = true;
					else if (MainDrill->bIsActive && bCanMine)
						bCanMine = false;
					else if (MainDrill->bAllGeneratorsDestroyed && bCanMine && BuildOwner->WaveManager->CurrentGamePhase == ECurrentGamePhase::CGP_Fight)
						bCanMine = false;
					break;

				case EGameDifficulty::GD_EmployeeOfTheMonth:
					bCanMine = true;
					break;

				case EGameDifficulty::GD_Default:
					break;
				}

				MainDrill->bDrillComponentExtracted = bCanMine;
			}
		}
		else
			bLooksAtMainDrill = false;

		if (hit.GetActor()->ActorHasTag("Mineral") && !bHasOre && bCanMine)
			bHasOre = true;
		else if (bHasOre && !hit.GetActor()->ActorHasTag("Mineral") || !bCanMine)
		{
			bHasOre = false;
			bIsCurrentlyMining = false;
		}

		SkeletalMeshComponent->SetWorldLocation(hit.ImpactPoint, false, nullptr, ETeleportType::None);

		FVector rot = FVector::CrossProduct(SkeletalMeshComponent->GetUpVector(), hit.ImpactNormal);
		float angle = acosf(FVector::DotProduct(GetActorUpVector(), hit.ImpactNormal));

		FQuat quat = FQuat(rot, angle);
		FQuat newQuat = quat * SkeletalMeshComponent->GetComponentQuat();
		FRotator newRot = newQuat.Rotator();

		BuildRot.Roll = newRot.Roll;
		BuildRot.Pitch = newRot.Pitch;

		BuildPos = SkeletalMeshComponent->GetComponentLocation();
		BuildPos.Z += 100.f;

		if(Cast<AEnemyTarget>(hit.Actor))
		{
			if (lenghtToBuildPoint <= BuildingRange)
			{
				SetMeshEmpty(true);

				if (!CurrentStructure || CurrentStructure != hit.GetActor() || !MainDrill)
				{
					if (AEnemyTarget* structure = Cast<AEnemyTarget>(hit.GetActor()))
					{
						CurrentStructure = structure;

						CurrentStructure->SkeletalMeshComponent->bRenderCustomDepth = true;
						CurrentStructure->SkeletalMeshComponent->MarkRenderStateDirty();
						CurrentStructure->SetIsWatched(true, this);
					}

					if (!MainDrill && Cast<AMainDrill>(hit.GetActor()))
					{
						MainDrill = Cast<AMainDrill>(hit.GetActor());
						MainDrill->SkeletalMeshComponent->CustomDepthStencilValue = 2;
					}
				}

				if (Cast<ATowerBase>(CurrentStructure) && CurrentStructure->bCanUpgrade && PlayerController->WasInputKeyJustPressed(EKeys::RightMouseButton) &&
					ResourceManager->HasEnoughResources(StructureInfo.Find(CurrentStructure->StructureType)->upgradeCostNormal, StructureInfo.Find(CurrentStructure->StructureType)->upgradeCostSpecial) &&
					CurrentStructure->CurrStructureLevel < CurrentStructure->MaxStructureLevel && SpaceMineGameInstance->GameDifficulty != EGameDifficulty::GD_EmployeeOfTheMonth)
				{
					UpgradeStructure();
					ResourceManager->DeductResources(StructureInfo.Find(CurrentStructure->StructureType)->upgradeCostNormal, StructureInfo.Find(CurrentStructure->StructureType)->upgradeCostSpecial);
					bNotEnoughResources = false;
					bBuildAction = true;
					bUpgradeAction = true;
				}
				else if (Cast<ATowerBase>(CurrentStructure) && CurrentStructure->bCanUpgrade && PlayerController->WasInputKeyJustPressed(EKeys::RightMouseButton) &&
					     !ResourceManager->HasEnoughResources(StructureInfo.Find(CurrentStructure->StructureType)->upgradeCostNormal, StructureInfo.Find(CurrentStructure->StructureType)->upgradeCostSpecial) &&
					     CurrentStructure->CurrStructureLevel >= CurrentStructure->MaxStructureLevel && SpaceMineGameInstance->GameDifficulty != EGameDifficulty::GD_EmployeeOfTheMonth)
				{
					bNotEnoughResources = true;
					bBuildAction = true;
					bUpgradeAction = true;
				}
				else if (bUpgradeAction && SpaceMineGameInstance->GameDifficulty != EGameDifficulty::GD_EmployeeOfTheMonth)
					bUpgradeAction = false;
				else if(Cast<AGenerator>(CurrentStructure) && PlayerController->WasInputKeyJustPressed(EKeys::RightMouseButton))
					Cast<AGenerator>(CurrentStructure)->ToggleActiveStatus();


				if (Cast<AMainDrill>(CurrentStructure) && MainDrill)
				{
					float mineralstashadd = AddToStashValue_Minerals;
					float crytsalstashadd = AddToStashValue_Crystals;

					if (MainDrill->bIsActive && BuildOwner->WaveManager->CurrentWave <= 5)
					{
						if (!ResourceManager->HasEnoughResources(AddToStashValue_Minerals, 0))
							mineralstashadd = ResourceManager->CurrentNormalMineral;

						crytsalstashadd = 0.f;
					}
					else if (!MainDrill->bIsActive && MainDrill->bAllGeneratorsDestroyed && BuildOwner->WaveManager->CurrentWave <= 5)
					{
						if (!ResourceManager->HasEnoughResources(AddToStashValue_Minerals, AddToStashValue_Crystals))
						{
							mineralstashadd = ResourceManager->CurrentNormalMineral;
							crytsalstashadd = ResourceManager->CurrentSpecialMineral;
						}
					}
					else if (!ResourceManager->HasEnoughResources(AddToStashValue_Minerals, AddToStashValue_Crystals))
					{
						if (!ResourceManager->HasEnoughResources(AddToStashValue_Minerals, AddToStashValue_Crystals))
						{
							mineralstashadd = ResourceManager->CurrentNormalMineral;
							crytsalstashadd = ResourceManager->CurrentSpecialMineral;
						}
					}

					if(PlayerController->WasInputKeyJustPressed(EKeys::LeftMouseButton) || PlayerController->GetInputKeyTimeDown(EKeys::LeftMouseButton) > 0.1f && CurrResourceDeliverTimer <= 0)
					{
						if(!ResourceManager)
							return;

						CurrResourceDeliverTimer = MaxResourceDeliverTimer;

						if (SpaceMineGameInstance->GameDifficulty != EGameDifficulty::GD_EmployeeOfTheMonth && MainDrill->bDrillComponentExtracted && BuildOwner->WaveManager->CurrentWave <= 5)
							return;

						if (BuildOwner->WaveManager->CurrentWave >= 6)
						{
							if (MainDrill->bIsActive)
								crytsalstashadd = 0.f;
							MainDrill->AddResourcesToStash(mineralstashadd);
							ResourceManager->DeductResources(mineralstashadd, crytsalstashadd);
						}
						else if(MainDrill->bIsActive)
						{
							MainDrill->AddResourcesToStash(mineralstashadd);
							ResourceManager->DeductResources(mineralstashadd, 0);
						}
						else if(!MainDrill->bIsActive && MainDrill->bAllGeneratorsDestroyed)
						{
							MainDrill->AddResourcesToStash(mineralstashadd);
							ResourceManager->DeductResources(mineralstashadd, crytsalstashadd);
						}
					}
					else if (PlayerController->GetInputKeyTimeDown(EKeys::LeftMouseButton) > 0.1f)
						CurrResourceDeliverTimer -= World->GetDeltaSeconds();
				}
			}
		}
		else if (CurrentStructure)
			ClearCurrentStructure();
	}
	else if (CurrentStructure)
		ClearCurrentStructure();
	else
		SetMeshEmpty(false);
}

void APlayerBuilder::SwitchBuildStructure(int _structureIdx)
{
	if(_structureIdx == 4)
		SkeletalMeshComponent->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	else
		SkeletalMeshComponent->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));

	switch (_structureIdx)
	{
	case -1:

		ClearCurrentStructure();
		SkeletalMeshComponent->SetSkeletalMesh(EmptyMesh);
		TowerRangeMeshComponment->SetMaterial(0, TranslucentMaterial);
		CachedMesh = EmptyMesh;
		bNoAction = true;
		bCanRepair = false;
	break;

	case 1:
		if (StructureInfo.Find(EStructureBuildType::SBT_BoltTurret)->bmeshSet)
		{
			ClearCurrentStructure();
			StructureToBuild = EStructureBuildType::SBT_BoltTurret;
			SkeletalMeshComponent->SetSkeletalMesh(StructureInfo.Find(EStructureBuildType::SBT_BoltTurret)->structureMesh);
			CachedMesh = SkeletalMeshComponent->SkeletalMesh;
			bNoAction = false;
			bCanRepair = false;

			CurrentStructureCost_Normal =  StructureInfo.Find(EStructureBuildType::SBT_BoltTurret)->normalCost;
			CurrentStructureCost_Special = StructureInfo.Find(EStructureBuildType::SBT_BoltTurret)->specialCost;

			TowerRangeMeshComponment->SetMaterial(0, RangeMaterial);
			TowerRangeMeshComponment->SetRelativeScale3D(FVector(5.f, 5.f, 5.f));
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("No Structure Mesh Selected!"));
		break;

	case 2:
		if(StructureInfo.Find(EStructureBuildType::SBT_Barrier)->bmeshSet)
		{
			ClearCurrentStructure();
			StructureToBuild = EStructureBuildType::SBT_Barrier;
			SkeletalMeshComponent->SetSkeletalMesh(StructureInfo.Find(EStructureBuildType::SBT_Barrier)->structureMesh);
			CachedMesh = SkeletalMeshComponent->SkeletalMesh;
			bNoAction = false;
			bCanRepair = false;

			CurrentStructureCost_Normal = StructureInfo.Find(EStructureBuildType::SBT_Barrier)->normalCost;
			CurrentStructureCost_Special = StructureInfo.Find(EStructureBuildType::SBT_Barrier)->specialCost;

			TowerRangeMeshComponment->SetMaterial(0, TranslucentMaterial);
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("No Structure Mesh Selected!"));
		break;

	case 3:
		if (StructureInfo.Find(EStructureBuildType::SBT_FlamethrowerTurret)->bmeshSet)
		{
			ClearCurrentStructure();
			StructureToBuild = EStructureBuildType::SBT_FlamethrowerTurret;
			SkeletalMeshComponent->SetSkeletalMesh(StructureInfo.Find(EStructureBuildType::SBT_FlamethrowerTurret)->structureMesh);
			CachedMesh = SkeletalMeshComponent->SkeletalMesh;
			bNoAction = false;
			bCanRepair = false;

			CurrentStructureCost_Normal = StructureInfo.Find(EStructureBuildType::SBT_FlamethrowerTurret)->normalCost;
			CurrentStructureCost_Special = StructureInfo.Find(EStructureBuildType::SBT_FlamethrowerTurret)->specialCost;

			TowerRangeMeshComponment->SetMaterial(0, RangeMaterial);
			TowerRangeMeshComponment->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("No Structure Mesh Selected!"));
		break;

	case 4:
		if (StructureInfo.Find(EStructureBuildType::SBT_Drill)->bmeshSet)
		{
			ClearCurrentStructure();
			StructureToBuild = EStructureBuildType::SBT_Drill;
			SkeletalMeshComponent->SetSkeletalMesh(StructureInfo.Find(EStructureBuildType::SBT_Drill)->structureMesh);
			CachedMesh = SkeletalMeshComponent->SkeletalMesh;
			bNoAction = false;
			bCanRepair = false;

			CurrentStructureCost_Normal = StructureInfo.Find(EStructureBuildType::SBT_Drill)->normalCost;
			CurrentStructureCost_Special = StructureInfo.Find(EStructureBuildType::SBT_Drill)->specialCost;

			TowerRangeMeshComponment->SetMaterial(0, TranslucentMaterial);
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("No Structure Mesh Selected!"));
		break;

	case 5:
		{
			StructureToBuild = EStructureBuildType::SBT_Repair;
			SkeletalMeshComponent->SetSkeletalMesh(StructureInfo.Find(EStructureBuildType::SBT_Repair)->structureMesh);
			CachedMesh = SkeletalMeshComponent->SkeletalMesh;
			bCanRepair = true;
			bNoAction = false;

			TowerRangeMeshComponment->SetMaterial(0, TranslucentMaterial);
			if (CurrentStructure && CurrentStructure->CurrentHP < CurrentStructure->MaxHP)
				CurrentRepairCost = CurrentStructure->MaxHP - CurrentStructure->CurrentHP;
		}
		break;

		default:
			if(_structureIdx != 0)
				UE_LOG(LogTemp, Warning, TEXT("Unvalid Action in Player Builder"));
		break;
	}
}


void APlayerBuilder::BlockOnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if (Cast<ATowerBase>(_otherActor) || Cast<ANoBuildZone>(_otherActor))
	{
		bIsBlocked = true;

		CurrOverlapActor = _otherActor;

		if (Cast<ANoBuildZone>(_otherActor))
		{
			SetMaterialUnvalid();
			bOutsideBuildArea = true;
		}
	}
}
void APlayerBuilder::BlockOnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex)
{
	if (Cast<ANoBuildZone>(_otherActor))
	{
		bIsBlocked = false;
		CurrOverlapActor = nullptr;

		SetMaterialValid();
		bOutsideBuildArea = false;
	}

	if (Cast<ATowerBase>(_otherActor))
	{
		bIsBlocked = false;
		CurrOverlapActor = nullptr;
	}
}

void APlayerBuilder::CheckPreviewForResources()
{
	if (!ResourceManager || StructureToBuild == EStructureBuildType::SBT_Default || StructureToBuild == EStructureBuildType::SBT_Repair)
		return;

	FStructureCost* structureCostCheck = StructureInfo.Find(StructureToBuild);

	if(!bIsBlocked && ResourceManager->HasEnoughResources(structureCostCheck->normalCost, structureCostCheck->specialCost) && bCanBuild)
	{
		bNotEnoughResources = false;

		SetMaterialValid();
	}
	else if(bCanBuild)
	{
		bNotEnoughResources = true;

		if (!InsufficientResourcesMaterial)
			return;

		for (size_t i = 0; i < SkeletalMeshComponent->GetMaterials().Num(); i++)
		{
			SkeletalMeshComponent->SetMaterial(i, InsufficientResourcesMaterial);
		}
	}
}
