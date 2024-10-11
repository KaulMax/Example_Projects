// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface_KeyRegister.h"


/*
* Register for the enum string combinations for the behaviour trees blackboard, more information in ABBKey_Initializer.cpp
*/
IInterface_KeyRegister::IInterface_KeyRegister()
{
	keyValueMap.Add((int)EKeyRegister_Names::KRN_O_SelfActor, "SelfActor");
	keyValueMap.Add((int)EKeyRegister_Names::KRN_O_TargetActor, "TargetActor");

	keyValueMap.Add((int)EKeyRegister_Names::KRN_V_MoveToLocation, "MoveToLocation");

	keyValueMap.Add((int)EKeyRegister_Names::KRN_SO_ClaimHandle, "ClaimHandle");

	keyValueMap.Add((int)EKeyRegister_Names::KRN_B_HasLineOfSight, "HasLineOfSight");
	keyValueMap.Add((int)EKeyRegister_Names::KRN_B_HasEnviAction, "CanCommitEnviAction");
	keyValueMap.Add((int)EKeyRegister_Names::KRN_B_IsGrounded, "IsGrounded");
	keyValueMap.Add((int)EKeyRegister_Names::KRN_B_PlayerInAttackRange, "PlayerIsInAttackRange");
	keyValueMap.Add((int)EKeyRegister_Names::KRN_B_CanHearPlayer, "CanHearPlayer");
	keyValueMap.Add((int)EKeyRegister_Names::KRN_B_IsFlying, "IsFlying");
}

FName IInterface_KeyRegister::GetKeyName(EKeyRegister_Names _key)
{
	if (keyValueMap.Contains((int)_key))
		return *keyValueMap.Find((int)_key);
	else
		return *keyValueMap.Find(0);
}