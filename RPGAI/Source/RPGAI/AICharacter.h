// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGAICharacter.h"
#include "AICharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityCastStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityCastEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityCastInterrupt);


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

	virtual bool GetIsAlive_Implementation() override;
	virtual bool GetIsPlayer_Implementation() override;
	virtual bool GetIsCurrentlyInterrupted_Implementation() override;
	virtual float GetHealth_Implementation(float& MaxHealth) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AActor* PatrolRoute = nullptr;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<class AAbilityBase> CurrentAbilityClassToActivate;

	UPROPERTY(BlueprintReadWrite)
		AActor* CurrentTargetForAbility = nullptr;

	void ActivateAbility(TSubclassOf<class AAbilityBase> AbilityClass, AActor* Target);
	void AbilityActivated();
	void CancelAbilityActivation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySetup")
		float CastSpeed = 1.f;

	UPROPERTY(BlueprintAssignable)
		FOnAbilityCastStarted OnAbilityCastStarted;

	UPROPERTY(BlueprintAssignable)
		FOnAbilityCastEnded OnAbilityCastEnded;

	UPROPERTY(BlueprintAssignable)
		FOnAbilityCastInterrupt OnAbilityCastInterrupt;

	UPROPERTY(BlueprintReadWrite)
		bool IsInterrupt;

	void SetUnInterrupted() { IsInterrupt = false; }

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
