// Fill out your copyright notice in the Description page of Project Settings.

#include "Player\WintPlayerState.h"
#include "AbilitySystem\WintAbilitySet.h"
#include "Actor\WintPawnData.h"
#include "AbilitySystem\WintAbilitySystemComponent.h"
#include "AbilitySystem\WintAttributeSet.h"
#include "Net/UnrealNetwork.h"


AWintPlayerState::AWintPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UWintAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	NetUpdateFrequency = 100;
}

void AWintPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void AWintPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWintPlayerState, PawnData);
}

void AWintPlayerState::OnRep_PawnData()
{
}

void AWintPlayerState::InitPawnData()
{
	if (PawnData)
	{
		for (const UWintAbilitySet* Set : PawnData->AbilitySets)
		{
			if (Set)
			{
				Set->GiveAbilities(AbilitySystemComponent);
			}
		}
	}
}

void AWintPlayerState::SetPawnData(const UWintPawnData* InPawnData)
{
	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	if (PawnData)
	{
		UE_LOG(LogTemp, Error, TEXT("Trying to set PawnData [%s] on player state [%s] that already has valid PawnData [%s]."), *GetNameSafe(InPawnData), *GetNameSafe(this), *GetNameSafe(PawnData));
		return;
	}

	PawnData = InPawnData;

	for (const UWintAbilitySet* Set : PawnData->AbilitySets)
	{
		if (Set)
		{
			Set->GiveAbilities(AbilitySystemComponent);
		}
	}

	ForceNetUpdate();
}
