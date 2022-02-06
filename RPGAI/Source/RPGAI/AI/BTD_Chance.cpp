// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAI/AI/BTD_Chance.h"

UBTD_Chance::UBTD_Chance()
{
	NodeName = "Chance";
}

bool UBTD_Chance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bSuccess = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (!bSuccess) return false;

	return FMath::RandRange(0, 100) < Chance;
}