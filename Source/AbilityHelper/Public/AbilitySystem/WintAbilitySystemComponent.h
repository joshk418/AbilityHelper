// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WintAbilitySystemComponent.generated.h"

struct FWintAbilitySet_GameplayAbility;
/**
 * Base class for Ability System Component customizations.
 */
UCLASS()
class ABILITYHELPER_API UWintAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityInputHeld(const FGameplayTag& InputTag);
	void AbilityInputReleased(const FGameplayTag& InputTag);

	void CancelAllActiveAbilities();
};
