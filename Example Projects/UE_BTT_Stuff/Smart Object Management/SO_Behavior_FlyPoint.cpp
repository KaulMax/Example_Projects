// Fill out your copyright notice in the Description page of Project Settings.


#include "SO_Behavior_FlyPoint.h"

#include "AIController.h"
#include "Enemy_AIController.h"
#include "Enemy_Base.h"
#include "EnumDirectory.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameplayBehavior.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


/*
* This SO is quite straightforward. It's placed on the ground, and the AI, upon claiming it, is queuing a flight action.
*/
USO_Behavior_FlyPoint::USO_Behavior_FlyPoint()
{
	flyCooldown = 15.f;
	initialFlyForce = 100000.f;
}

bool USO_Behavior_FlyPoint::Trigger(AActor& Avatar, const UGameplayBehaviorConfig* Config, AActor* SmartObjectOwner)
{
	enemy = Cast<AEnemy_Base>(&Avatar);

	FTimerManager& timerManager = GetWorld()->GetTimerManager();

	if (enemy)
	{
		enemy->SetBlackboardValueTimer_Bool(EKeyRegister_Names::KRN_B_HasEnviAction, flyCooldown, true);

		enemy->SetBlackboardValueTimer_Bool(EKeyRegister_Names::KRN_B_IsGrounded, .5f, false);
		enemy->SetBlackboardValueTimer_Bool(EKeyRegister_Names::KRN_B_IsFlying, .5f, true);
		enemy->SetMovementModeTimer(EMovementMode::MOVE_Flying, .85f);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("USO_Behavior_FlyPoint, !enemy"));

	blackboard = Cast<AEnemy_AIController>(enemy->GetController())->GetBlackboardComponent();
	blackboard->SetValue<UBlackboardKeyType_Bool>(IInterface_KeyRegister::GetKeyName(EKeyRegister_Names::KRN_B_HasEnviAction), false);

	FEnvQueryRequest jumpPosReq;

	enemy->GetCharacterMovement()->AddImpulse(enemy->GetActorUpVector() * initialFlyForce);

	return false;
}

void USO_Behavior_FlyPoint::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void USO_Behavior_FlyPoint::EndBehavior(AActor& Avatar, const bool bInterrupted)
{
}

void USO_Behavior_FlyPoint::OnGameplayTaskInitialized(UGameplayTask& Task)
{
}