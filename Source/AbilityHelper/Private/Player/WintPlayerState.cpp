// Fill out your copyright notice in the Description page of Project Settings.

#include "Player\WintPlayerState.h"

#include "AbilitySystem\WintAbilitySystemComponent.h"
#include "AbilitySystem\WintAttributeSet.h"

AWintPlayerState::AWintPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UWintAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UWintAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100;
}
