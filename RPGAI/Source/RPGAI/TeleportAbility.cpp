// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportAbility.h"
#include "EnvironmentQuery/EnvQuery.h"

void ATeleportAbility::BeginPlay()
{
	Super::BeginPlay();

    FEnvQueryRequest QueryRequest = FEnvQueryRequest(MyQuery, GetOwner());
    QueryRequest.Execute(EEnvQueryRunMode::RandomBest5Pct, this, &ATeleportAbility::MyQueryFinished);
}


void ATeleportAbility::MyQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
    TArray<FVector> OutLocations;
    Result->GetAllAsLocations(OutLocations);
    if (OutLocations.Num())
    {
        if (GetOwner())
        {
            GetOwner()->TeleportTo(OutLocations[0], FRotator::ZeroRotator);
        }
    }
}