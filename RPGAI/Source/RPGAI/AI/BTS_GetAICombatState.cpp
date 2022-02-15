// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAI/AI/BTS_GetAICombatState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RPGAI/AICharacter.h"
#include "RPGAI/AICEnemy.h"
#include "RPGAI/RPGAIGameMode.h"
#include "RPGAI/AIHelper.h"

void UBTS_GetAICombatState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAICEnemy* AIC = Cast<AAICEnemy>(OwnerComp.GetAIOwner());
	if (AIC != nullptr)
	{
		AAICharacter* AIChar = Cast<AAICharacter>(AIC->GetPawn());
		if (AIChar != nullptr)
		{			
			UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
			if (BlackboardComp != nullptr)
			{
				if (IAIHelper::Execute_GetIsCurrentlyInterrupted(AIChar))
				{
					BlackboardComp->SetValueAsEnum(CombatStateKey.SelectedKeyName, ECombatState::INTERRUPTED);
				}
				else
				{
					AActor* Actor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));
					if (!Actor)
					{
						ECombatState CombatState = AIChar->PatrolRoute ? ECombatState::PATROL : ECombatState::IDLE;
						BlackboardComp->SetValueAsEnum(CombatStateKey.SelectedKeyName, CombatState);
					}
					else
					{
						float CurrentDistance = AIChar->GetDistanceTo(Actor);
						float MaxRange, MinRange;
						IAIHelper::Execute_GetAttackRange(AIChar, MaxRange, MinRange);
					
						if (CurrentDistance > MaxRange)
						{
							BlackboardComp->SetValueAsEnum(CombatStateKey.SelectedKeyName, ECombatState::OUT_OF_RANGE);
						}
						else
						{
							if (CurrentDistance > MinRange)
							{
								BlackboardComp->SetValueAsEnum(CombatStateKey.SelectedKeyName, ECombatState::RANGED_ATTACK);
							}
							else
							{
								BlackboardComp->SetValueAsEnum(CombatStateKey.SelectedKeyName, ECombatState::MEEL_ATTACK);
							}
						}
					}
				}
			}
		}	
	}
}