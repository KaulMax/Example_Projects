// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GrabComponent.h"
#include "GrabObjectBase.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "InputAction.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"


/*
 * Creates all player bindings, sets up inits, and manages the movement.
 */
AVRPlayer::AVRPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>("VRRoot");
	RootComponent = VRRoot;

	motionController_RightHand = CreateDefaultSubobject<UMotionControllerComponent>("MotionControllerRightHand");
	motionController_RightHand->SetupAttachment(VRRoot);
	
	motionController_LeftHand = CreateDefaultSubobject<UMotionControllerComponent>("MotionControllerLeftHand");
	motionController_LeftHand->SetupAttachment(VRRoot);

	mesh_RightHand = CreateDefaultSubobject<UStaticMeshComponent>("MeshRightHand");
	mesh_RightHand->SetupAttachment(motionController_RightHand);
	
	mesh_LeftHand = CreateDefaultSubobject<UStaticMeshComponent>("MeshLeftHand");
	mesh_LeftHand->SetupAttachment(motionController_LeftHand);

	firstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	firstPersonCameraComponent->SetupAttachment(RootComponent);
	firstPersonCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f)); 
	firstPersonCameraComponent->bUsePawnControlRotation = true;
}

void AVRPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (!displayLib->IsHeadMountedDisplayEnabled())
		return;

	world = GetWorld();

	mesh_RightHand->SetRelativeLocation(motionController_RightHand->GetRelativeLocation());


	mesh_RightHand->OnComponentBeginOverlap.AddDynamic(this, &AVRPlayer::OnOverlapBegin_GrabRight);
	mesh_RightHand->OnComponentEndOverlap.AddDynamic(this, &AVRPlayer::OnOverlapEnd_GrabRight);


	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(defaultMappingContext, 0);
		}
	}

	SetupVRDepends();
}

void AVRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!displayLib->IsHeadMountedDisplayEnabled())
		return;

	Walk();
}

void AVRPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedinputcomp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedinputcomp->BindAction(grabAction_RightHand, ETriggerEvent::Started, this, &AVRPlayer::Grab_RightHand);
		enhancedinputcomp->BindAction(grabAction_RightHand, ETriggerEvent::Completed, this, &AVRPlayer::Release_RightHand);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("!EnhancedInputComponent"));
}

void AVRPlayer::SetupVRDepends()
{
	displayLib->SetTrackingOrigin(EHMDTrackingOrigin::Stage);
	// ref ->  https://www.unrealengine.com/blog/significant-changes-coming-to-vr-resolution-settings-in-4-19 ( KP wie aktuell das is )
	UKismetSystemLibrary::ExecuteConsoleCommand(this, TEXT( "vr.PixelDensity 1.0"), nullptr);
}

void AVRPlayer::Grab_RightHand()
{
	if (!currOverlapActor)
		return;

	if (!currOverlapActor->GetGrabComponent()->TryGrabObject(this, motionController_RightHand))
		return;

	currGrabActor = currOverlapActor;
}

void AVRPlayer::Release_RightHand()
{
	if (!currOverlapActor)
		return;

	if (!currOverlapActor->GetGrabComponent()->TryReleaseObject())
		return;


	currGrabActor = nullptr;
}

void AVRPlayer::Walk()
{
	FVector newloc = FVector();
	FRotator newrot = FRotator();

	FXRDeviceId deviceid = FXRDeviceId();

	bool bistraccked = false;
	bool bhastrackpos = false;

	displayLib->GetDeviceWorldPose(world, deviceid, bistraccked, newrot, bhastrackpos, newloc);

	this->SetActorLocation(newloc);
	this->SetActorRotation(newrot);
}

void AVRPlayer::OnOverlapBegin_GrabRight(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor,
	UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if (AGrabObjectBase* grabactor = Cast<AGrabObjectBase>(_otherActor))
		currOverlapActor = grabactor;
}

void AVRPlayer::OnOverlapEnd_GrabRight(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor,
	UPrimitiveComponent* _otherComp, int32 _otherBodyIndex)
{
	if (currOverlapActor && Cast<AGrabObjectBase>(_otherActor))
		currOverlapActor = nullptr;
}