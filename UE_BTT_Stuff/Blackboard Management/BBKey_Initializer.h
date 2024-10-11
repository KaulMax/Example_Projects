// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface_KeyRegister.h"
#include "GameFramework/Actor.h"
#include "BBKey_Initializer.generated.h"

UCLASS()
class ABBKey_Initializer : public AActor, public IInterface_KeyRegister
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Blackboards, meta = (AllowPrivateAccess))
		class UBehaviorTree* enemyBehaviorTree;

	UFUNCTION()
		bool InitBlackboard(FName _keyName, EKeyRegister_Types _metaKey, class UBlackboardData* _bbData);

public:
	ABBKey_Initializer();

	UFUNCTION(CallInEditor, Category = BlackboardInitializer)
		virtual void InitEnemyBlackboardKeys();

	UPROPERTY(EditAnywhere)
	TMap<EKeyRegister_Names, EKeyRegister_Types> KeysToUpdateOrAdd;
};
