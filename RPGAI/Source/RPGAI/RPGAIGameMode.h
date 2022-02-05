// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPGAIGameMode.generated.h"

UENUM(BlueprintType)
enum ECombatState
{
	IDLE,
	PATROL,
	RANGED_ATTACK,
	MEEL_ATTACK,
	OUT_OF_RANGE
};


UCLASS(minimalapi)
class ARPGAIGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARPGAIGameMode();
};



