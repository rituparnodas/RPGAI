// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAI/AI/BTT_ActivateAbility.h"
#include "RPGAI/AICharacter.h"
#include "RPGAI/AICEnemy.h"
#include "RPGAI/AbilityBase.h"
#include "BehaviorTree/BlackboardComponent.h"

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

	AAICharacter* AICharacter{ Cast<AAICharacter>(AICEnemy->GetPawn()) };
	if (!AICharacter) return EBTNodeResult::Failed;

	UBlackboardComponent* BC = OwnerComp.GetBlackboardComponent();
	if (!BC) return EBTNodeResult::Failed;

	if (!AICharacter->OnAbilityCastStarted.IsBound() && !AICharacter->OnAbilityCastInterrupt.IsBound() && !AICharacter->OnAbilityCastEnded.IsBound())
	{
		AICharacter->OnAbilityCastStarted.AddDynamic(this, &UBTT_ActivateAbility::AbilityCastStarted);
		AICharacter->OnAbilityCastInterrupt.AddDynamic(this, &UBTT_ActivateAbility::AbilityCastInterrupted);
		AICharacter->OnAbilityCastEnded.AddDynamic(this, &UBTT_ActivateAbility::AbilityCastEnded);
	}
	

	AActor* Target = Cast<AActor>(BC->GetValueAsObject(TargetKey.SelectedKeyName));
	if (Target != nullptr)
	{
		AICharacter->ActivateAbility(AbilityClass, Target);
	}
	
	if (CurrentResult == EBTNodeResult::Type::Succeeded || CurrentResult == EBTNodeResult::Type::Failed)
	{
		CurrentResult = EBTNodeResult::Type::InProgress;
		UE_LOG(LogTemp, Warning, TEXT("InProgress"))
	}

	UE_LOG(LogTemp, Warning, TEXT("Executing"))

	return CurrentResult;
}

void UBTT_ActivateAbility::AbilityCastStarted()
{

}

void UBTT_ActivateAbility::AbilityCastInterrupted()
{
	CurrentResult = EBTNodeResult::Type::Succeeded;
	UE_LOG(LogTemp, Warning, TEXT("AbilityCastInterrupted"))
}

void UBTT_ActivateAbility::AbilityCastEnded()
{
	CurrentResult = EBTNodeResult::Type::Failed;
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