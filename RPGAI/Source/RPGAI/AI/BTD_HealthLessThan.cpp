// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAI/AI/BTD_HealthLessThan.h"
#include "RPGAI/AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RPGAI/AICEnemy.h"
#include "RPGAI/AIHelper.h"

UBTD_HealthLessThan::UBTD_HealthLessThan()
{
	NodeName = "Health Less Than";
}

bool UBTD_HealthLessThan::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bSuccess = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (!bSuccess) return false;

	AAICEnemy* AICEnemy = Cast<AAICEnemy>(OwnerComp.GetAIOwner());
	if (!AICEnemy) return false;

	AAICharacter* AIPawn = Cast<AAICharacter>(AICEnemy->GetPawn());
	if (!AIPawn) return false;

	float MaximumHealth; 
	float Health = IAIHelper::Execute_GetHealth(AIPawn, MaximumHealth);

	return (((int32)Health / (int32)MaximumHealth) * 100.f) < HealthThreshold;
}