// Fill out your copyright notice in the Description page of Project Settings.


#include "AICEnemy.h"
#include "AICharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"

AAICEnemy::AAICEnemy()
{
	AIPerceptioncomp = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AIPerceptionComp"));
}

void AAICEnemy::BeginPlay()
{
	Super::BeginPlay();
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
		}
	}
}