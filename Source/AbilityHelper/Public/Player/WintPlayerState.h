// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "WintPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

/**
 * PlayerState that implements the IAbilitySystemInterface to give flexibility to the Player
 * to retain ability system information.
 */
UCLASS()
class ABILITYHELPER_API AWintPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	AWintPlayerState();

	virtual UAbilitySystemComponent *GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	};

	UAttributeSet *GetAttributeSet() const
	{
		return AttributeSet;
	};
};
