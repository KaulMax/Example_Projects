// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Controller.h"

#include "Navigation/CrowdFollowingComponent.h"

AEnemy_Controller::AEnemy_Controller(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{

}
