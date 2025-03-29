// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageUISpawn.h"

#include <string>

#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetTextLibrary.h"

ADamageUISpawn::ADamageUISpawn()
{
	PrimaryActorTick.bCanEverTick = true;

	timeTillDestroy = 1.f;
	AlphaStart = 90.f;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>("Default Root");
	RootComponent = DefaultRoot;

	DamageText = CreateDefaultSubobject<UTextRenderComponent>("Damage Text");
	DamageText->SetupAttachment(GetRootComponent());
}

void ADamageUISpawn::InitDamageText(float _damage, AActor* _attachActor, bool _rightDamageType, bool _hasDamageWeakness, bool _spawnedTroughPlayer)
{
	AttachActor = _attachActor;

	SpawnedTroughPlayer = _spawnedTroughPlayer;

	DamageText->Text = UKismetTextLibrary::Conv_FloatToText(_damage, FromZero);

	if(_hasDamageWeakness)
	{
		if (_rightDamageType)
			DamageText->SetTextRenderColor(FColor(255, 255, 0, 255));
		else if (!_rightDamageType)
			DamageText->SetTextRenderColor(FColor(225, 0, 0, 255));
	}
	else
		DamageText->SetTextRenderColor(FColor(26, 23, 0, 255));

	float rndX = FMath::RandRange(_attachActor->GetActorLocation().X - 50.f,_attachActor->GetActorLocation().X + 50.f);
	float rndY = FMath::RandRange(_attachActor->GetActorLocation().Y - 50.f, _attachActor->GetActorLocation().Y + 50.f);
	float rndZ = FMath::RandRange(_attachActor->GetActorLocation().Z,_attachActor->GetActorLocation().Z + 25.f);
	rndZ += 50.f;

	InitZ = rndZ;

	FVector rnduitextpos = FVector(rndX, rndY, rndZ);

	DamageText->SetWorldLocation(rnduitextpos);

	FVector dirtoplayer = UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraLocation() - AttachActor->GetActorLocation();
	dirtoplayer.Normalize();

	SetActorRotation(FRotator(0,0,0));

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &ADamageUISpawn::DestroySelf, timeTillDestroy);
}

void ADamageUISpawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ManageTextRotation();

	if (AttachActor)
	{
		float locX = AttachActor->GetActorLocation().X;
		float locY = AttachActor->GetActorLocation().Y;

		InitZ += 3.f;

		UMaterialInstanceDynamic* dynamicmat = DamageText->CreateDynamicMaterialInstance(0, DamageText->GetMaterial(0));

		dynamicmat->SetScalarParameterValue("Opacity", AlphaStart -= .2f);

		SetActorLocation(FVector(locX, locY, InitZ));
	}
	else if (!AttachActor)
		DestroySelf();
}

void ADamageUISpawn::DestroySelf()
{
	Destroy();
}

void ADamageUISpawn::ManageTextRotation()
{
	FRotator textRot = UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraRotation();

	if(!SpawnedTroughPlayer)
	{
		textRot.Roll = -180.f;
		textRot.Pitch = -180.f;
	}

	textRot = FRotator(textRot.Pitch, textRot.Yaw, textRot.Roll);

	DamageText->SetRelativeRotation(textRot);
}
