// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilityBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityEnded);

UCLASS()
class RPGAI_API AAbilityBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbilityBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(BlueprintAssignable)
		FOnAbilityStarted OnAbilityStarted;

	UPROPERTY(BlueprintAssignable)
		FOnAbilityEnded OnAbilityEnded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CastTime = 4.f;
};
