// Fill out your copyright notice in the Description page of Project Settings.


#include "AICEnemy.h"
#include "AICharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig.h"
#include "AICharacter.h"
#include "AIHelper.h"
#include "BehaviorTree/BlackBoardComponent.h"

AAICEnemy::AAICEnemy()
{
	AIPerceptioncomp = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AIPerceptioncomp"));

	AIPerceptioncomp->SetDominantSense(UAISense_Sight::StaticClass());
}

void AAICEnemy::BeginPlay()
{
	Super::BeginPlay();

	AIPawn = Cast<AAICharacter>(GetPawn());
}

void AAICEnemy::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	EnemyAI = Cast<AAICharacter>(InPawn);
	if (EnemyAI)
	{
		UBehaviorTree* BT = EnemyAI->BehaviorTree;
		if (BT)
		{
			RunBehaviorTree(BT);

			GetWorld()->GetTimerManager().SetTimer(Handle_UpdatePerception, this, &AAICEnemy::UpdatePerception, 0.5f, true);
		}
	}
}

void AAICEnemy::UpdatePerception()
{
	if (AIPawn != nullptr)
	{
		if (!IAIHelper::Execute_GetIsAlive(AIPawn))
		{
			GetWorld()->GetTimerManager().ClearTimer(Handle_UpdatePerception);
		}
		else
		{
			TArray<AActor*> PerceivedActors;
			AIPerceptioncomp->GetKnownPerceivedActors(AISense, PerceivedActors);

			for (AActor* PActor : PerceivedActors)
			{
				if (PActor != nullptr)
				{
					if (IAIHelper::Execute_GetIsAlive(PActor))
					{
						if (IAIHelper::Execute_GetIsPlayer(PActor))
						{
							Target = PActor;
							break;
						}
					}
				}
			}
			if (GetBlackboardComponent())
			{
				GetBlackboardComponent()->SetValueAsObject(EnemyTargetKey, Target);
			}
		}
	}
}