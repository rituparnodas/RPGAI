// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "TeleportAbility.generated.h"


/**
 * 
 */
UCLASS()
class RPGAI_API ATeleportAbility : public AAbilityBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class UEnvQuery* MyQuery;
	
	//UFUNCTION()
	void MyQueryFinished(TSharedPtr<FEnvQueryResult> Result);
};
