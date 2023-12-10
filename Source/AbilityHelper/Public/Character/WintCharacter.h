// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "WintCharacter.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

/**
 * Base character that implements the IAbilitySystemInterface to give flexibility to the player and AI.
 *\n\n
 * AJKPlayerState is recommended to be used for the player's ability system component and attribute set.
 */
UCLASS()
class ABILITYHELPER_API AWintCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void BeginPlay() override;

public:
	AWintCharacter();

	virtual UAbilitySystemComponent *GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	};

	UAttributeSet *GetAttributeSet() const
	{
		return AttributeSet;
	};
};
