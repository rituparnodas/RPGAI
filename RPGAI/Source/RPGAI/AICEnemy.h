// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AICEnemy.generated.h"

/**
 * 
 */
UCLASS()
class RPGAI_API AAICEnemy : public AAIController
{
	GENERATED_BODY()
	
public:

	class AAICharacter* EnemyAI = nullptr;

protected:

	AAICEnemy();

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UAIPerceptionComponent* AIPerceptioncomp = nullptr;

};
