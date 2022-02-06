// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_HealthLessThan.generated.h"

/**
 * 
 */
UCLASS()
class RPGAI_API UBTD_HealthLessThan : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTD_HealthLessThan();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HealthThreshold;

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
