// Fill out your copyright notice in the Description page of Project Settings.


#include "SO_BlueprintBase.h"

#include "Enemy_Base.h"
#include "Interface_SmartObject.h"
#include "SmartObjectComponent.h"
#include "Components/SphereComponent.h"

/*
* Base class to set up the smart object BP, includes the component-based behavior base.
*/
ASO_BlueprintBase::ASO_BlueprintBase()
{
	PrimaryActorTick.bCanEverTick = true;

	smartObject = CreateDefaultSubobject<USmartObjectComponent>("SmartObject");
	RootComponent = smartObject;

	collisionCheck = CreateDefaultSubobject<USphereComponent>("ColissionCheck");
	collisionCheck->SetupAttachment(smartObject);
}

void ASO_BlueprintBase::BeginPlay()
{
	Super::BeginPlay();

	collisionCheck->OnComponentBeginOverlap.AddDynamic(this, &ASO_BlueprintBase::ASO_BlueprintBase::OnOverlapBegin);
	collisionCheck->OnComponentEndOverlap.AddDynamic(this, &ASO_BlueprintBase::ASO_BlueprintBase::OnOverlapEnd);
}

void ASO_BlueprintBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASO_BlueprintBase::GetCurrOverlapStatus()
{
	return bIsOverlapping;
}

AActor* ASO_BlueprintBase::GetCurrOverlapActor()
{
	return overlapActor;
}

void ASO_BlueprintBase::OnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor,UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if (_otherActor->GetClass()->ImplementsInterface(UInterface_SmartObject_Caller::StaticClass()))
	{
		bIsOverlapping = true;
		overlapActor = _otherActor;
	}
}

void ASO_BlueprintBase::OnOverlapEnd(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex)
{
	if (_otherActor->GetClass()->ImplementsInterface(UInterface_SmartObject_Caller::StaticClass()))
	{
		bIsOverlapping = false;
		overlapActor = nullptr;
	}
}
