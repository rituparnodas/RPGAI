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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName EnemyTargetKey;

protected:

	AAICEnemy();

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UAIPerceptionComponent* AIPerceptioncomp = nullptr;

	void UpdatePerception();

	FTimerHandle Handle_UpdatePerception;

	AAICharacter* AIPawn = nullptr;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UAISense> AISense;

	AActor* Target = nullptr;
};
