// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllEnums.h"
#include "InterfaceDamageablePlayer.h"
#include "GameFramework/Character.h"
#include "EnemyTarget.generated.h"

UCLASS()
class SPACEMINE_API AEnemyTarget : public ACharacter, public IInterfaceDamageablePlayer
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _deltaTime) override;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Manager)
		class AResourceManager* ResourceManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Managment)
		TSubclassOf<AResourceManager> ResourceManagerSub;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
	UAnimInstance* AnimInstance;

	  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		  UAnimMontage* CombatMontage;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void I_TakeDamage(float _damage, AMainEnemy* _ref) override;
	virtual void I_ApplyKnockback(FVector _launchVelo, bool _bXYOverride, bool __bZOverride) override;

	virtual void RepairCurrStructure();

	void OnResetDamageToggle();

	bool bCanTakeDamage;

	UFUNCTION()
		void SetIsWatched(bool _status, class APlayerBuilder* _builderRef);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Info)
		EStructureBuildType StructureType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		APlayerBuilder* BuilderRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status)
		bool bIsBeignWatched;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Info)
		int MaxStructureLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Info)
		int CurrStructureLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
		bool bCanUpgrade;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
		bool bHasRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
		bool bHasDeathPhysics;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
		TSubclassOf<class ADamageUISpawn> DamageUIText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
		float currMeshUpdateDebug;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
		float maxMeshUpdateDebug;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyComps)
		TArray<UMaterialInstance*> FadeMaterials;

	/// <summary>
	/// Normal Public Methods
	/// </summary>

	AEnemyTarget();

	//UFUNCTION(BlueprintCallable)
	//virtual void TakeDamage(float _damage, class AMainEnemy* _ref);
	UFUNCTION(BlueprintCallable)
	virtual void PlayDeath();
	UFUNCTION(BlueprintCallable)
	virtual void CleanAfterDeath();

	/// <summary>
	/// Collision Methods
	/// </summary>

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex);

	/// <summary>
	/// FORCEINLINE Public Methods
	/// </summary>


	/// <summary>
	/// Public Variables
	/// </summary>

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float CurrentHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats)
	bool bHasDied;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	bool bTookDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stats)
	FVector HitBoxExtend;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
		bool bWasRepaired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SFX)
		UParticleSystemComponent* RepairParticleComponent;

	/// <summary>
	/// Public Components
	/// </summary>

	UPROPERTY(VisibleAnywhere, Category = HitBox)
	class UBoxComponent* HitBox;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	class USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UWorld* World;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	EEnemyTargetType TargetType;

	/// <summary>
	/// Public SFX and Audio Component Placeholder
	/// </summary>

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SFX and Sound")
	class USoundCue* EnemyDamagedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX and Sound")
	class UParticleSystemComponent* DamagedParticleComponent;
};
