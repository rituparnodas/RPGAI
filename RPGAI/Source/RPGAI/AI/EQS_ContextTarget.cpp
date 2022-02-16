// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAI/AI/EQS_ContextTarget.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "RPGAI/AICEnemy.h"

void UEQS_ContextTarget::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	UObject* QuerierObject = QueryInstance.Owner.Get();
	if (!QuerierObject) return;

	AActor* QuerierActor = Cast<AActor>(QuerierObject);
	if (!QuerierActor) return;

	AAICEnemy* AICEnemy{ Cast<AAICEnemy>(UAIBlueprintHelperLibrary::GetAIController(QuerierActor)) };
	if (!AICEnemy) return;

	AActor* ResultingActor = NULL;

	if (AICEnemy->EnemyTarget)
	{
		ResultingActor = AICEnemy->EnemyTarget;
	}
	else
	{
		ResultingActor = AICEnemy;
	}
	
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, ResultingActor);
}