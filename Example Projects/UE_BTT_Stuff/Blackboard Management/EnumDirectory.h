#pragma once

UENUM()
enum class EKeyRegister_Types : uint8
{
	KRM_Default,
	KRM_Bool,
	KRM_Class,
	KRM_Enum,
	KRM_Float,
	KRM_Int,
	KRM_Name,
	KRM_NativeEnum,
	KRM_Object,
	KRM_String,
	KRM_Vector,
	KRM_SOHandle,
};

UENUM()
enum class EKeyRegister_Names : uint8
{
	KRN_Default,
	KRN_O_SelfActor,
	KRN_O_TargetActor,

	KRN_SO_ClaimHandle,

	KRN_V_MoveToLocation,

	KRN_B_HasLineOfSight,
	KRN_B_HasEnviAction,
	KRN_B_IsGrounded,
	KRN_B_PlayerInAttackRange,
	KRN_B_CanHearPlayer,
	KRN_B_IsFlying,
};