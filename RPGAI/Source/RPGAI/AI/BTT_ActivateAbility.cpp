// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAI/AI/BTT_ActivateAbility.h"
#include "RPGAI/AICharacter.h"
#include "RPGAI/AICEnemy.h"
#include "RPGAI/AbilityBase.h"

UBTT_ActivateAbility::UBTT_ActivateAbility()
{
	NodeName = "Activate Ability";
}

// Need Controller And Pawn
EBTNodeResult::Type UBTT_ActivateAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;

	AAICEnemy* AICEnemy{ Cast<AAICEnemy>(OwnerComp.GetAIOwner()) };
	if (!AICEnemy) return EBTNodeResult::Failed;

	AAICharacter* AICharacter{ Cast<AAICharacter>(AICEnemy) };
	if (!AICharacter) return EBTNodeResult::Failed;

	AICharacter->ActivateAbility(AbilityClass);
	
	AICharacter->OnAbilityCastStarted.AddDynamic(this, &UBTT_ActivateAbility::AbilityCastStarted);
	AICharacter->OnAbilityCastStarted.AddDynamic(this, &UBTT_ActivateAbility::AbilityCastInterrupted);
	AICharacter->OnAbilityCastStarted.AddDynamic(this, &UBTT_ActivateAbility::AbilityCastEnded);

	if (CurrentResult == EBTNodeResult::Type::Succeeded || CurrentResult == EBTNodeResult::Type::Failed)
	{
		CurrentResult = EBTNodeResult::Type::InProgress;
	}

	return CurrentResult;
}

void UBTT_ActivateAbility::AbilityCastStarted()
{

}

void UBTT_ActivateAbility::AbilityCastInterrupted()
{
	CurrentResult = EBTNodeResult::Type::Succeeded;
}

void UBTT_ActivateAbility::AbilityCastEnded()
{
	CurrentResult = EBTNodeResult::Type::Failed;
}

EBTNodeResult::Type UBTT_ActivateAbility::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	AAICEnemy* AICEnemy{ Cast<AAICEnemy>(OwnerComp.GetAIOwner()) };
	if (!AICEnemy) return EBTNodeResult::Failed;

	AAICharacter* AICharacter{ Cast<AAICharacter>(AICEnemy) };
	if (!AICharacter) return EBTNodeResult::Failed;

	AICharacter->CancelAbilityActivation();

	return EBTNodeResult::Succeeded;
}