// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AIHelper.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAIHelper : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPGAI_API IAIHelper
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetIsAlive();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		bool GetIsPlayer();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void GetAttackRange(float& MaxRange, float& MinRange);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		float GetHealth(float& MaxHealth);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		bool GetIsCurrentlyInterrupted();
};
