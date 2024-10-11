// Fill out your copyright notice in the Description page of Project Settings.


#include "BBKey_Initializer.h"

#include "BlackboardKeyType_SOClaimHandle.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnumDirectory.h"
#include "SmartObjectRuntime.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Kismet/GameplayStatics.h"


/*
* This class is used to initialize the blackboard for a chosen behavior tree. It uses a two-step categorization system. 
* Enums are set up in EnumDirectory.h, one for the data type and one to be associated with the specific EKeyRegister_Names. 
* The combination is then hardcoded within IInterface_KeyRegister.cpp, by associating a string with a given key. This is the first categorization. 
* The second is within the engine, where the created keyValueMap is associated with EKeyRegister_Types, which represent the data type of the now-created blackboard. 
* This works via the CallInEditor function InitEnemyBlackboardKeys(), which allows the population and editing of blackboards through the editor without going into play mode.
* 
* All of this could, of course, also have been done via a UDataTable, but I wanted to try it that way so I could better evaluate which option is better for cases like this.
* Spoiler alert:
* The better option would be a DataTable.
* The main reason, of course, being maintainability. But that part can easily be converted into a UDataTable, 
* and if I ever want a system that designers would be absolutely unable to use, I now know at least one way :D
*/

ABBKey_Initializer::ABBKey_Initializer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABBKey_Initializer::InitEnemyBlackboardKeys()
{
	if (!enemyBehaviorTree)
	{
		UE_LOG(LogTemp, Warning, TEXT("BBKeyInitializer, !enemyBehaviorTree"));
		return;
	}

	UBlackboardData* blackboarddata = enemyBehaviorTree->GetBlackboardAsset();


	TMap<FName, EKeyRegister_Types> updatekeys; 

	for (const TPair<EKeyRegister_Names, EKeyRegister_Types> keyvaluepair : KeysToUpdateOrAdd)
	{
		updatekeys.Add(IInterface_KeyRegister::GetKeyName(keyvaluepair.Key), keyvaluepair.Value);
	}
	

	bool iteratemaxed = false;

	if (updatekeys.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Keys selected"));
		return;
	}

	for (size_t i = 0; i < updatekeys.Num(); i++)
	{
		if (!iteratemaxed && blackboarddata->Keys.Num() > 0)
		{
			for (size_t j = 0; j < blackboarddata->Keys.Num(); j++)
			{
				if (updatekeys.Contains(blackboarddata->GetKeyName(j)))
				{
					TArray<FName> names;
					updatekeys.GetKeys(names);

					InitBlackboard(names[i], updatekeys.FindRef(names[i]), blackboarddata);
				}
				else
					blackboarddata->Keys.RemoveAt(j);
			}
		}
		else
			iteratemaxed = true;

		if (iteratemaxed && updatekeys.Num() > blackboarddata->Keys.Num())
		{
			TArray<FName> names;
			updatekeys.GetKeys(names);

			InitBlackboard(names[i], updatekeys.FindRef(names[i]), blackboarddata);
		}
	}
}

bool ABBKey_Initializer::InitBlackboard(FName _keyName, EKeyRegister_Types _metaKey, UBlackboardData* _bbData)
{
	switch (_metaKey)
	{
	case EKeyRegister_Types::KRM_Bool:
		_bbData->UpdatePersistentKey<UBlackboardKeyType_Bool>(_keyName);
		break;

	case EKeyRegister_Types::KRM_Class:
		_bbData->UpdatePersistentKey<UBlackboardKeyType_Class>(_keyName);
		break;

	case EKeyRegister_Types::KRM_Enum:
		_bbData->UpdatePersistentKey<UBlackboardKeyType_Enum>(_keyName);
		break;

	case EKeyRegister_Types::KRM_Float:
		_bbData->UpdatePersistentKey<UBlackboardKeyType_Float>(_keyName);
		break;

	case EKeyRegister_Types::KRM_Int:
		_bbData->UpdatePersistentKey<UBlackboardKeyType_Int>(_keyName);
		break;

	case EKeyRegister_Types::KRM_Name:
		_bbData->UpdatePersistentKey<UBlackboardKeyType_Name>(_keyName);
		break;

	case EKeyRegister_Types::KRM_NativeEnum:
		_bbData->UpdatePersistentKey<UBlackboardKeyType_NativeEnum>(_keyName);
		break;

	case EKeyRegister_Types::KRM_Object:
		_bbData->UpdatePersistentKey<UBlackboardKeyType_Object>(_keyName);
		break;

	case EKeyRegister_Types::KRM_String:
		_bbData->UpdatePersistentKey<UBlackboardKeyType_String>(_keyName);
		break;

	case EKeyRegister_Types::KRM_Vector:
		_bbData->UpdatePersistentKey<UBlackboardKeyType_Vector>(_keyName);
		break;

	case EKeyRegister_Types::KRM_SOHandle:
		_bbData->UpdatePersistentKey<UBlackboardKeyType_SOClaimHandle>(_keyName);
		break;

	case EKeyRegister_Types::KRM_Default:
		_bbData->UpdatePersistentKey<UBlackboardKeyType_Object>("SelfActor");
		break;

	default:
		_bbData->UpdatePersistentKey<UBlackboardKeyType_Object>("SelfActor");
		break;
	}


	return false;
}