// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourceManager.generated.h"

UCLASS()
class SPACEMINE_API AResourceManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	bool mainDrillActive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Managment)
	TSubclassOf<class AMainDrill> Drill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Managment)
	class AMainDrill* MainDrill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Managment)
	TSubclassOf<class AWaveManager> WaveSub;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Managment)
	TArray<class AEnemyTarget*> allDrills;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Managment)
	TArray<AEnemyTarget*> allGenerators;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Cheats)
	class USpaceMineGameInstance* SpaceMineGameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Managment)
		class AWaveManager* WaveManager;

	UFUNCTION()
	void SubscribeStructure(AEnemyTarget* _toAdd);
	UFUNCTION()
	void UnsubscribeStructure(AEnemyTarget* _toDelete);

	FORCEINLINE
	bool IsMainDrillAlive() { return mainDrillActive; }
	UFUNCTION()
	void SetMainDrillStatus(bool _status);

	void TickResources_Normal(float DeltaTime);
	void TickResources_Special(float DeltaTime);

	void DeductResources(float _normalCost, float _specialCost);

	bool HasEnoughResources(float _normalCost, float _specialCost);

	UFUNCTION(BlueprintCallable)
	void AddNormalResources();
	void AddNormalResources(float _add);
	UFUNCTION(BlueprintCallable)
	void AddSpecialResources();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Resources)
	float CurrentNormalMineral;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Resources)
	float CurrentSpecialMineral;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Resources)
	float NormalResourceTickRate;
	float CurrNormalTickRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Resources)
	float SpecialResourceTickRate;
	float CurrSpecialTickRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Resources)
	float NormalResourceWeight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Resources)
	float SpecialResourceWeight;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Resources)
		int TotalMinerals;
};