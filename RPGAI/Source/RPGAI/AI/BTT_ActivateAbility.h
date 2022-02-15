// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ActivateAbility.generated.h"

/**
 * 
 */
UCLASS()
class RPGAI_API UBTT_ActivateAbility : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTT_ActivateAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AAbilityBase> AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBlackboardKeySelector TargetKey;

	UFUNCTION()
	void AbilityCastStarted();

	UFUNCTION()
	void AbilityCastInterrupted();

	UFUNCTION()
	void AbilityCastEnded();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	EBTNodeResult::Type CurrentResult = EBTNodeResult::Type::Succeeded;
};
