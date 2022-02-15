// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AbilityBase.h"
#include "Kismet/GameplayStatics.h"

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

bool AAICharacter::GetIsCurrentlyInterrupted_Implementation()
{
	return IsInterrupt;
}

void AAICharacter::ActivateAbility(TSubclassOf<AAbilityBase> AbilityClass, AActor* Target)
{
	CurrentTargetForAbility = Target;
	CurrentAbilityClassToActivate = AbilityClass;
	OnAbilityCastStarted.Broadcast();
	
	float Delay = AbilityClass.GetDefaultObject()->CastTime * CastSpeed;
	FTimerHandle Handle_AbilityActivated;
	GetWorld()->GetTimerManager().SetTimer(Handle_AbilityActivated, this, &AAICharacter::AbilityActivated, Delay);
	
}

void AAICharacter::AbilityActivated()
{
	OnAbilityCastEnded.Broadcast();

	AAbilityBase* AbilityType = GetWorld()->SpawnActorDeferred<AAbilityBase>(CurrentAbilityClassToActivate, GetActorTransform(), this, this);
	if (AbilityType)
	{
		AbilityType->AITarget = CurrentTargetForAbility;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AbilityType Null"))
	}
	UGameplayStatics::FinishSpawningActor(AbilityType, GetActorTransform());
}

void AAICharacter::CancelAbilityActivation()
{
}

float AAICharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	IsInterrupt = true;
	OnAbilityCastInterrupt.Broadcast();
	FTimerHandle Handle_Interrupt;
	GetWorld()->GetTimerManager().SetTimer(Handle_Interrupt, this, &AAICharacter::SetUnInterrupted, 1.f);

	return DamageAmount;
}