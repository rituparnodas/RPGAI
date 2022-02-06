// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_Chance.generated.h"

/**
 * 
 */
UCLASS()
class RPGAI_API UBTD_Chance : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	UBTD_Chance();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", ClampMax = "100"))
		int32 Chance;

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
