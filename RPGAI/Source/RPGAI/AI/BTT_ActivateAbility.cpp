// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAI/AI/BTT_ActivateAbility.h"
#include "RPGAI/AICharacter.h"
#include "RPGAI/AICEnemy.h"
#include "RPGAI/AbilityBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTT_ActivateAbility::UBTT_ActivateAbility()
{
	NodeName = "Activate Ability";
}

bool bIsActive = true;

// Need Controller And Pawn
EBTNodeResult::Type UBTT_ActivateAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	_OwnerComponent = &OwnerComp;

	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;

	AAICEnemy* AICEnemy{ Cast<AAICEnemy>(OwnerComp.GetAIOwner()) };
	if (!AICEnemy) return EBTNodeResult::Failed;

	AAICharacter* AICharacter{ Cast<AAICharacter>(AICEnemy->GetPawn()) };
	if (!AICharacter) return EBTNodeResult::Failed;

	UBlackboardComponent* BC = OwnerComp.GetBlackboardComponent();
	if (!BC) return EBTNodeResult::Failed;

	AICharacter->OnAbilityCastStarted.RemoveAll(this);
	AICharacter->OnAbilityCastStarted.AddDynamic(this, &UBTT_ActivateAbility::AbilityCastStarted);

	AICharacter->OnAbilityCastInterrupt.RemoveAll(this);
	AICharacter->OnAbilityCastInterrupt.AddDynamic(this, &UBTT_ActivateAbility::AbilityCastInterrupted);

	AICharacter->OnAbilityCastEnded.RemoveAll(this);
	AICharacter->OnAbilityCastEnded.AddDynamic(this, &UBTT_ActivateAbility::AbilityCastEnded);

	AActor* Target = Cast<AActor>(BC->GetValueAsObject(TargetKey.SelectedKeyName));
	if (Target != nullptr)
	{
		AICharacter->ActivateAbility(AbilityClass, Target);
		CurrentResult = EBTNodeResult::Type::InProgress;
	}

	return EBTNodeResult::Type::InProgress;
}

void UBTT_ActivateAbility::AbilityCastStarted()
{
}

void UBTT_ActivateAbility::AbilityCastInterrupted()
{
	FinishLatentTask(*_OwnerComponent, EBTNodeResult::Type::Succeeded);
	UE_LOG(LogTemp, Warning, TEXT("AbilityCastInterrupted"))
}

void UBTT_ActivateAbility::AbilityCastEnded()
{
	FinishLatentTask(*_OwnerComponent, EBTNodeResult::Type::Succeeded);
	UE_LOG(LogTemp, Warning, TEXT("AbilityCastEnded"))
}

EBTNodeResult::Type UBTT_ActivateAbility::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	AAICEnemy* AICEnemy{ Cast<AAICEnemy>(OwnerComp.GetAIOwner()) };
	if (!AICEnemy) return EBTNodeResult::Failed;

	AAICharacter* AICharacter{ Cast<AAICharacter>(AICEnemy) };
	if (!AICharacter) return EBTNodeResult::Failed;

	AICharacter->CancelAbilityActivation();
	UE_LOG(LogTemp, Warning, TEXT("Succeeded"))
	return EBTNodeResult::Succeeded;
}