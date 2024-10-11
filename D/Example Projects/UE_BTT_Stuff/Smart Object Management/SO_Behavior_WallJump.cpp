// Fill out your copyright notice in the Description page of Project Settings.


#include "SO_Behavior_WallJump.h"

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
* This smart object's behavior is a wall jump. The AI will use the BTT_Use_SO_Distance query to search for a wall jump SO.
* The SO will be placed on walls and has a funny little quirk, which I already spoiled a little bit in BTT_Use_SO_Distance, which is that the nav agent needs to be on a navmesh for the Unreal Engine smart object to be claimed.
* This means that every BP_Behavior_WallJump needs a non-collidable mesh with a navmesh on it to function. There might have been a possibility to avoid this, for example, having the SO be associated with a jump position on
* a wall and than place the SO on the ground, but this would be more work in the long run if I ever use this system.
* But otherwise, I'm quite sure there could have been a workaround, but I couldn't find it and, at that point, had already spent too much time on it than I planned to.
*/
USO_Behavior_WallJump::USO_Behavior_WallJump()
{
	airTime = .15f;
	wallJumpCooldown = 5.f;
	initialJumpForce = 250.f;
}

bool USO_Behavior_WallJump::Trigger(AActor& Avatar, const UGameplayBehaviorConfig* Config, AActor* SmartObjectOwner)
{
	UE_LOG(LogTemp, Warning, TEXT("Trigger"))

	enemy = Cast<AEnemy_Base>(&Avatar);

	FTimerManager& timerManager = GetWorld()->GetTimerManager();

	if(enemy)
	{
		enemy->SetBlackboardValueTimer_Bool(EKeyRegister_Names::KRN_B_HasEnviAction, wallJumpCooldown, true);
		enemy->SetBlackboardValueTimer_Bool(EKeyRegister_Names::KRN_B_IsGrounded, 1.f, true);
		enemy->SetMovementModeTimer(EMovementMode::MOVE_Walking, airTime);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("USO_Behavior_WallJump, !enemy"));

	blackboard = Cast<AEnemy_AIController>(enemy->GetController())->GetBlackboardComponent();

	FEnvQueryRequest jumpPosReq;

	if (blackboard->GetValue<UBlackboardKeyType_Object>(IInterface_KeyRegister::GetKeyName(EKeyRegister_Names::KRN_O_TargetActor)) ||
		blackboard->GetValue<UBlackboardKeyType_Bool>(IInterface_KeyRegister::GetKeyName(EKeyRegister_Names::KRN_B_HasLineOfSight)))
	{
		if (jumpQueryPlayer)
		{
			UE_LOG(LogTemp, Warning, TEXT("jumpQueryPlayer"));

			jumpPosReq = FEnvQueryRequest(jumpQueryPlayer, enemy);
			jumpPosReq.Execute(EEnvQueryRunMode::RandomBest5Pct, this, &USO_Behavior_WallJump::HandleQueryResult);
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("USO_Behavior_WallJump, !jumpQueryPlayer"));
	}
	else
	{
		if (jumpQueryRandom)
		{
			UE_LOG(LogTemp, Warning, TEXT("jumpQueryRandom"));

			jumpPosReq = FEnvQueryRequest(jumpQueryRandom, enemy);
			jumpPosReq.Execute(EEnvQueryRunMode::RandomBest25Pct, this, &USO_Behavior_WallJump::HandleQueryResult);
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("USO_Behavior_WallJump, !jumpQueryRandom"));
	}

	return false;
}

void USO_Behavior_WallJump::HandleQueryResult(TSharedPtr<FEnvQueryResult> _result)
{
	if(_result->IsSuccessful())
	{
		enemy->GetCharacterMovement()->AddImpulse(enemy->GetActorUpVector() * 100000);

		FVector dirToGoal = _result->GetItemAsLocation(0) - enemy->K2_GetActorLocation();
		float jumpadditive = initialJumpForce;
		jumpadditive *= dirToGoal.Length();

		dirToGoal.Normalize();
		dirToGoal *= jumpadditive;

		enemy->GetCharacterMovement()->AddImpulse(dirToGoal);

		FRotator lookrot = UKismetMathLibrary::FindLookAtRotation(enemy->K2_GetActorLocation(), _result->GetItemAsLocation(0));
		lookrot = FRotator(0, lookrot.Yaw, 0);
		enemy->K2_SetActorRotation(lookrot, false);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("USO_Behavior_WallJump, !_result"));
}

void USO_Behavior_WallJump::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void USO_Behavior_WallJump::EndBehavior(AActor& Avatar, const bool bInterrupted)
{
}

void USO_Behavior_WallJump::OnGameplayTaskInitialized(UGameplayTask& Task)
{
}
