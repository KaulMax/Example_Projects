// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllEnums.h"
#include "GameFramework/Actor.h"
#include "PlayerBuilder.generated.h"


USTRUCT(BlueprintType)
struct FStructureCost
{
	GENERATED_BODY()

	FStructureCost() {};

	FStructureCost(float _normalCost, float _specialCost, float _upgradeCostNormal, float _upgradeCostSpecial, USkeletalMesh* _structureMesh)
	{
		normalCost = _normalCost;
		specialCost = _specialCost;

		upgradeCostNormal = _upgradeCostNormal;
		upgradeCostSpecial = _upgradeCostSpecial;

		structureMesh = _structureMesh;
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float normalCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float specialCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float upgradeCostNormal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float upgradeCostSpecial;

	UPROPERTY(EditAnywhere)
	USkeletalMesh* structureMesh;

	UPROPERTY(EditAnywhere)
	bool bmeshSet;
};

UCLASS()
class SPACEMINE_API APlayerBuilder : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerBuilder();

	UFUNCTION()
	void StructureAction();


	UFUNCTION()
	void TurnRight();
	UFUNCTION()
	void TurnLeft();
	UFUNCTION()
	void SwitchBuildStructure(int _structureIdx);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void BlockOnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()
	virtual void BlockOnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex);

	UFUNCTION()
	void BuildStructure();
	UFUNCTION()
	void RepairStructure();
	UFUNCTION()
	void UpgradeStructure();

	UFUNCTION()
	void CheckForStructureInfo();

	UFUNCTION()
	void ClearCurrentStructure();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void TurnStructure();

	UFUNCTION()
	void CheckBuildPosition();

	UFUNCTION()
	void SetMaterialValid();
	UFUNCTION()
	void SetMaterialUnvalid();

	UFUNCTION()
	void CheckPreviewForResources();

	UFUNCTION()
	void SetMeshEmpty(bool _bblockHit);

	UFUNCTION()
	void CheckNormalPosition();
	UFUNCTION()
	void CheckFixedPosition();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StructureInfo)
	TMap<EStructureBuildType, FStructureCost> StructureInfo;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	USkeletalMeshComponent* SkeletalMeshComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Info)
	AActor* CurrOverlapActor;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	UStaticMeshComponent* TowerRangeMeshComponment;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class ASpaceMineCharacter* BuildOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* MineralMiningParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCombat)
	FName PlacementSocketName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UWorld* World;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	EStructureBuildType StructureToBuild;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	UMaterialInterface* UnvalidMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	UMaterialInterface* NormalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	UMaterialInterface* RepairMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	UMaterialInterface* RangeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	UMaterialInterface* InsufficientResourcesMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	UMaterialInterface* TranslucentMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
		UMaterialInterface* PlayerDrillMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	FVector BuildAngleRestriction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	class UBoxComponent* BuilderHitBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	class AEnemyTarget* CurrentStructure;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
		class USpaceMineGameInstance* SpaceMineGameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	class AMainDrill* MainDrill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	float BuildingRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	float DebugZPosNormal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	float DebugZPosFixed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
		float CurrResourceDeliverTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
		float MaxResourceDeliverTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	float RangeIndicatorRotSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	bool bCanBuild;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	bool bIsBlocked;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	bool bOutsideBuildArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	bool bBuildAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	bool bCanRepair;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	bool bUpgradeAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	bool bNoAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	bool bNotEnoughResources;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	bool bCanTurnRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	bool bCanTurnLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	float MinBuildDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	float BuildHeightAdj;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	float TurnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWinCondition)
	float AddToStashValue_Minerals;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWinCondition)
	float AddToStashValue_Crystals;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	float CurrentStructureCost_Normal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	float CurrentStructureCost_Special;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	float CurrentRepairCost;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mining)
		bool bHasOre;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mining)
		bool bIsCurrentlyMining;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mining)
		bool bCanMine;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mining)
		bool bLooksAtMainDrill;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mining)
		float CurrentMineralExtrationTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mining)
		float MaxMineralExtrationTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mining)
		float ResourceMineAmount;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	USkeletalMesh* NormalTowerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	USkeletalMesh* FlamethrowerTowerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	USkeletalMesh* DrillMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	USkeletalMesh* BarrierMesh;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	USkeletalMesh* EmptyMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	USkeletalMesh* CachedMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	TSubclassOf<class ATowerBase> GunTurret;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	TSubclassOf<ATowerBase> Drill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	TSubclassOf<ATowerBase> Barrier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	TSubclassOf<ATowerBase> FlamethrowerTurret;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	FVector BuildPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	FRotator BuildRot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	class AResourceManager* ResourceManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	class AResourcePoint* ResourcePoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	TSubclassOf<AResourceManager> ResourceManagerSub;

	/// <summary>
	/// Public SFX and Audio Component Placeholder
	/// </summary>

};
