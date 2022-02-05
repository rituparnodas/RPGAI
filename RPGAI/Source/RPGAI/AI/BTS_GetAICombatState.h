// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_GetAICombatState.generated.h"

/**
 * 
 */
UCLASS()
class RPGAI_API UBTS_GetAICombatState : public UBTService
{
	GENERATED_BODY()
	
protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public :

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector CombatStateKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector TargetKey;
};
