// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageUISpawn.generated.h"

UCLASS()
class SPACEMINE_API ADamageUISpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	ADamageUISpawn();

	UFUNCTION()
	void InitDamageText(float _damage, AActor* _attachActor, bool _rightDamageType, bool _hasDamageWeakness, bool _spawnedTroughPlayer);

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		float timeTillDestroy;

	UFUNCTION()
		void DestroySelf();

	UFUNCTION()
		void ManageTextRotation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		class UTextRenderComponent* DamageText;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* DefaultRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = UI)
		AActor* AttachActor;

	UPROPERTY()
		float InitZ;

	UPROPERTY()
		float AlphaStart;

	UPROPERTY()
		bool SpawnedTroughPlayer;
};
