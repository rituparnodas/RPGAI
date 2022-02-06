// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AbilityBase.h"

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

float AAICharacter::GetHealth_Implementation(float& MaxHealth)
{
	MaxHealth = MaximumHealth;
	return Health;
}

void AAICharacter::ActivateAbility(TSubclassOf<class AAbilityBase> AbilityClass)
{
	CurrentAbilityClassToActivate = AbilityClass;
	OnAbilityCastStarted.Broadcast();

	
}

void AAICharacter::AbilityActivated()
{
	OnAbilityCastEnded.Broadcast();

	//AAbilityBase* AbilityClass = GetWorld()->SpawnActor<AAbilityBase>(CurrentAbilityClassToActivate, )
}