#include "Enemy_Base.h"

#include "Enemy_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Uprooted/UprootedCharacter.h"


/*
* Simple Enemy AI base class with Inits and Component based actions and timer management. 
* Enemy decision making is based on Behaviour Tree transitions while the behaviour is executed based on Behaviour Tree Tasks prefixed as BTT_.
*/
AEnemy_Base::AEnemy_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	attackColission = CreateDefaultSubobject<UStaticMeshComponent>("AttackColission");
	attackColission->SetupAttachment(GetRootComponent());

	flightHeight = 855.48495f;
}

void AEnemy_Base::BeginPlay()
{
	aiController = Cast<AEnemy_AIController>(GetController());

	if (aiController)
		blackboard = aiController->GetBlackboardComponent();
	else
		UE_LOG(LogTemp, Warning, TEXT("AEnemy_Base, !aiController"));

	if(blackboard)
	{
		blackboard->SetValue<UBlackboardKeyType_Bool>(IInterface_KeyRegister::GetKeyName(EKeyRegister_Names::KRN_B_IsGrounded), true);
		blackboard->SetValue<UBlackboardKeyType_Bool>(IInterface_KeyRegister::GetKeyName(EKeyRegister_Names::KRN_B_HasEnviAction), true);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("AEnemy_Base, !blackboard"));

	attackColission->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_Base::AEnemy_Base::OnTargetBeginOverlap);
	attackColission->OnComponentEndOverlap.AddDynamic(this, &AEnemy_Base::AEnemy_Base::OnTargetEndOverlap);
}

void AEnemy_Base::Tick(float DeltaSeconds)
{

}

void AEnemy_Base::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack"))
}

void AEnemy_Base::OnTargetBeginOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if (_otherActor != this && _otherActor->GetClass()->ImplementsInterface(UIDamageable::StaticClass()))
	{
		if(AUprootedCharacter* player = Cast<AUprootedCharacter>(_otherActor))
		{
			if (!blackboard)
			{
				UE_LOG(LogTemp, Warning, TEXT("AEnemy_Base, !blackboard"));
				return;
			}
			else
				blackboard->SetValue<UBlackboardKeyType_Bool>(IInterface_KeyRegister::GetKeyName(EKeyRegister_Names::KRN_B_PlayerInAttackRange), true);
		}
	}
}
void AEnemy_Base::OnTargetEndOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex)
{
	if (_otherActor->GetClass()->ImplementsInterface(UIDamageable::StaticClass()))
	{
		if (!blackboard)
		{
			UE_LOG(LogTemp, Warning, TEXT("AEnemy_Base, !blackboard"));
			return;
		}
		else
		{
			AUprootedCharacter* player = Cast<AUprootedCharacter>(_otherActor);
			blackboard->SetValue<UBlackboardKeyType_Bool>(IInterface_KeyRegister::GetKeyName(EKeyRegister_Names::KRN_B_PlayerInAttackRange), false);
		}
	}
}

void AEnemy_Base::SetBlackboardValueTimer_Bool(EKeyRegister_Names _bbKey, float _timer, bool _resetValue)
{
	if (!bbTimerDelegates.Contains(_bbKey))
	{
		FTimerDelegate newtimerdelegate;
		newtimerdelegate.BindUFunction(this, FName("Reset_BlackboardValue"), _bbKey, _resetValue);

		bbTimerDelegates.Add(_bbKey, newtimerdelegate);
	}

	if (!bbTimerHandles.Contains(_bbKey))
	{
		FTimerHandle newtimerhandle;
		bbTimerHandles.Add(_bbKey, newtimerhandle);
	}

	bbTimerHandles.FindRef(_bbKey).Invalidate();
	FTimerHandle currhandle = bbTimerHandles.FindRef(_bbKey);

	FTimerDelegate currdelegate = bbTimerDelegates.FindRef(_bbKey);
	
	GetWorld()->GetTimerManager().SetTimer(currhandle, currdelegate, _timer, false);
}

void AEnemy_Base::SetMovementModeTimer(EMovementMode _mmKey, float _timer)
{
	if (!mmTimerDelegates.Contains(_mmKey))
	{
		FTimerDelegate newtimerdelegate;
		newtimerdelegate.BindUFunction(this, FName("Reset_MovementMode"), _mmKey);

		mmTimerDelegates.Add(_mmKey, newtimerdelegate);
	}

	if (!mmTimerHandles.Contains(_mmKey))
	{
		FTimerHandle newtimerhandle;
		mmTimerHandles.Add(_mmKey, newtimerhandle);
	}

	mmTimerHandles.FindRef(_mmKey).Invalidate();
	FTimerDelegate currdelegate = mmTimerDelegates.FindRef(_mmKey);

	FTimerHandle currhandle = mmTimerHandles.FindRef(_mmKey);

	GetWorld()->GetTimerManager().SetTimer(currhandle, currdelegate, _timer, false);
}

void AEnemy_Base::Reset_BlackboardValue(EKeyRegister_Names _bbKey, bool _value)
{
	blackboard->SetValue<UBlackboardKeyType_Bool>(IInterface_KeyRegister::GetKeyName(_bbKey), _value);
}

void AEnemy_Base::Reset_MovementMode(EMovementMode _mmKey)
{
	GetCharacterMovement()->SetMovementMode(_mmKey);

	if (_mmKey == EMovementMode::MOVE_Flying)
	{
		UE_LOG(LogTemp, Warning, TEXT("Reset_MovementMode"));
		GetCharacterMovement()->Velocity = FVector(0);
	}
}