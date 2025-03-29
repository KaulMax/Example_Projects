// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyTarget.h"
#include "MainDrill.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMINE_API AMainDrill : public AEnemyTarget
{
	GENERATED_BODY()

	AMainDrill();

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Managment)
	TArray<class AGenerator*> allGenerators;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Managment)
	class AGameManager* GameManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WinCondition)
	float ResourceAmountToWin;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = WinCondition)
	float CurrentResourceAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	UAnimMontage* EnvyMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		class USpaceMineGameInstance* SpaceMineGameInstance;

public:

	UFUNCTION()
	void SubscribeManager(class AResourceManager* _manager);

	UFUNCTION()
	void AddResourcesToStash(int _resourcesToAdd);

	FORCEINLINE
	float CurrentResources() { return CurrentResourceAmount; }

	UFUNCTION()
	void UnsubGenerator(AGenerator* _toUnsub, bool _activationStatus);

	UFUNCTION()
		void ChangeActiveGenerators(bool _decrement);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Managment)
		bool bIsActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Managment)
		bool bAllGeneratorsDestroyed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Managment)
		bool bDrillComponentExtracted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Managment)
		float HardModeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Managment)
		float CurrDamageTick;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Managment)
		float MaxDamageTick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Managment)
		float CurrTimeTillFirstTick;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Managment)
		float MaxTimeTillFirstTick;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Managment)
		int ActiveGeneratorAmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Managment)
		int TotalGeneratorAmount;
};
