// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem\WintAbilitySystemComponent.h"
#include "AbilitySystem/WintAbilitySet.h"

void UWintAbilitySystemComponent::AbilityInputHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(Spec);

			if (!Spec.IsActive())
			{
				TryActivateAbility(Spec.Handle);
			}
		}
	}
}

void UWintAbilitySystemComponent::AbilityInputReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(Spec);
		}
	}
}

void UWintAbilitySystemComponent::CancelAllActiveAbilities()
{
	const FGameplayAbilityActorInfo* Info = AbilityActorInfo.Get();
	for (const FGameplayAbilitySpec Ability : GetActivatableAbilities())
	{
		if (Ability.IsActive())
		{
			for (UGameplayAbility* Instance : Ability.GetAbilityInstances())
			{
				Instance->CancelAbility(Ability.Handle, Info, Ability.ActivationInfo, true);
			}
		}
	}
}
