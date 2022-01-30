// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "BehaviorTree/BehaviorTree.h"

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

bool AAICharacter::GetIsAlive_Implementation()
{
	return Health > 0.f;
}

bool AAICharacter::GetIsPlayer_Implementation()
{
	return false;
}
