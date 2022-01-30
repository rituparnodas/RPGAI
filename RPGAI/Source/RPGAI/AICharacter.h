// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGAICharacter.h"
#include "AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class RPGAI_API AAICharacter : public ARPGAICharacter
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AISetup")
		class UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AISetup")
		float Mana;

	bool GetIsAlive_Implementation();
	bool GetIsPlayer_Implementation();
};
