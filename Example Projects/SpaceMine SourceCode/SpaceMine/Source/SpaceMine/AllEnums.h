#pragma once

UENUM()
enum class EEnemyState : uint8
{
	ES_Idle,
	ES_WalkToTarget,
	ES_WalkToGoal,
	ES_Attacking
};

UENUM()
enum class EEnemyType : uint8
{
	ET_None,
	ET_Normal,
	ET_Crystal
};

UENUM()
enum class EDamageType : uint8
{
	DT_Normal,
	DT_Crystal
};

UENUM()
enum class ETowerState : uint8
{
	TS_Dormant,
	TS_AttackingEnemy
};

UENUM()
enum class ETowerUpgradeVisualStatus : uint8
{
	TUS_Normal,
	TUS_Once
};


UENUM()
enum class EStructureBuildType : uint8
{
	SBT_Default,
	SBT_Barrier,
	SBT_BoltTurret,
	SBT_FlamethrowerTurret,
	SBT_Drill,
	SBT_MainDrill,
	SBT_UpgradedBoltTurret,
	SBT_Repair,
	SBT_Generator
};

UENUM()
enum class ECurrentGamePhase : uint8
{
	CGP_Default,
	CGP_Build,
	CGP_Fight
};

UENUM()
enum class EEnemyTargetType : uint8
{
	ETT_Default,
	ETT_Player,
	ETT_Structure
};

UENUM(BlueprintType)
enum class EGameDifficulty : uint8
{
	GD_Default,
	GD_Easy,
	GD_Normal,
	GD_Hard,
	GD_EmployeeOfTheMonth
};