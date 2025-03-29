// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnemyTarget.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "SpaceMineCharacter.generated.h"

UCLASS(config=Game)
class ASpaceMineCharacter : public AEnemyTarget
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	APlayerCameraManager* PlayerCam;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	APlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCharacterMovementComponent* MovementComponent;

protected:

	UFUNCTION()
	void BeginTimeline_CameraTogglePos();
	UFUNCTION()
	void TickTimeline_CameraTogglePos(float _alpha);

	UFUNCTION()
		void BeginTimeline_CameraHitEffect();
	UFUNCTION()
		void TickTimeline_CameraHitEffect(float _alpha);

	UFUNCTION()
		void BeginTimeline_CameraWalkShake();
	UFUNCTION()
		void TickTimeline_CameraWalkShake(float _alpha);

	UFUNCTION()
		void ResetEnemiesInView();
	UFUNCTION()
	void CheckForViewEnemy();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		FVector2D CrosshairSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		TArray<AMainEnemy*> CachedEnemies;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		AMainEnemy* currLookEnemy;

	FTimerHandle resethandle;

public:
	virtual void PlayDeath() override;
	ASpaceMineCharacter();

	UFUNCTION()
	void SubscribeBuilder(class APlayerBuilder* _builder);
	UFUNCTION()
	void SubscribeWeapon(class APlayerWeapon* _weapon);

	UFUNCTION()
	void ManagePlayerMesh();

	UFUNCTION()
	void SetWeaponIK();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerComps)
		TArray<UMaterialInterface*> CachedPlayerMats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerComps)
		TArray<UMaterialInterface*> SeetroughPlayerMats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector WeaponIK;

	UFUNCTION()
	void SetIK();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	//virtual void RepairCurrStructure() override;

	virtual void I_TakeDamage(float _damage, AMainEnemy* _ref) override;
	virtual float SampleDamage(float _sampleDamage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	float CurrentAnimTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
		float ShootAnimAlpha;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= PlayerBuilding)
	float DebugBuildTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	float MaxDebugBuildTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Stats)
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	float MovementSpeedModifier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Status)
	bool bIsBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Status)
	bool bShootingBullet;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Status)
	bool bShootingFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		bool bTookDamageUIFeedback;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	bool bWalkingBack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= GlobalStatus)
	bool bToggleWaveInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GlobalStatus)
	bool bPaused;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerSpawning)
	FVector StartPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCombat)
	FName WeaponSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCombat)
	FName BuildingSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCombat)
	UChildActorComponent* Weapon_ChildActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCombat)
	class USpotLightComponent* HeadLamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCombat)
	class URectLightComponent* HeadLightEmission;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerCombat)
	APlayerWeapon* WeaponBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stuff)
		FVector IK_LookTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCombat)
	UChildActorComponent* Building_ChildActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCombat)
	bool bMadeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCombat)
		bool bTookDamageToggle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCombat)
		bool bCanTakeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCombat)
		float CurrCanTakeDmgTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCombat)
		float MaxCanTakeDmgTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerBuilding)
	APlayerBuilder* BuilderBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerBuilding)
	class AWaveManager* WaveManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Cheats)
	class USpaceMineGameInstance* SpaceMineGameInstance;

	bool buildModeRoundStartToggle;

	UFUNCTION(BlueprintCallable)
	void ToggleBuildMode();

	UPROPERTY(EditAnywhere, Category = Timeline, meta = (AllowPrivateAccess))
		float CameraCombatOffsetX;
	UPROPERTY(EditAnywhere, Category = Timeline, meta = (AllowPrivateAccess))
		float CameraCombatOffsetY;

protected:
	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void TurnAtRate(float Rate);

	UFUNCTION()
	void TurnStructureRight();
	UFUNCTION()
	void TurnStructureLeft();


	UFUNCTION()
	void SwitchSelectedStructure(float _structureIdx);

	UFUNCTION()
	void LookUpAtRate(float Rate);

	UFUNCTION()
	void PlayerActionStatic();
	UFUNCTION()
	void PlayerActionStaticRelease();

	UFUNCTION()
	void SkipToWave();

	UFUNCTION()
	void PlayerActionDynamic(float DeltaSeconds);

	UFUNCTION()
	void ToggleWaveInfo();

	UFUNCTION()
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	UFUNCTION()
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	UFUNCTION()
		void OnBackWalkEnd( );

	UPROPERTY(EditAnywhere, Category = Timeline, meta = (AllowPrivateAccess))
		UCurveFloat* curveFloat_CameraTogglePos;

	FTimeline curveTimeline_CameraTogglePos;


	UPROPERTY(EditAnywhere, Category = Timeline, meta = (AllowPrivateAccess))
		UCurveFloat* curveFloat_CameraHitEffect;

	FTimeline curveTimeline_CameraHitEffect;


	UPROPERTY(EditAnywhere, Category = Timeline, meta = (AllowPrivateAccess))
		UCurveFloat* curveFloat_CameraWalkShake;

	FTimeline curveTimeline_CameraWalkShake;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
		int randCamShake;
	UPROPERTY()
		bool bWalkShakeToggle;
	UPROPERTY()
		bool bReachedBuildPos;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};