// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WintAbilitySet.h"
#include "AbilitySystemComponent.h"

void UWintAbilitySet::GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent) const
{
	
	if (!IsValid(AbilitySystemComponent))
	{
		return;
	}

	const AActor* Owner = AbilitySystemComponent->GetOwnerActor();
	if (!Owner)
	{
		return;
	}

	if (Owner->GetLocalRole() < ROLE_Authority)
	{
		return;
	}
	
	for (const FWintAbilitySet_GameplayAbility& Set : GrantedAbilities)
	{
		if (!IsValid(Set.Ability))
		{
			return;
		}
		
		FGameplayAbilitySpec AbilitySpec(Set.Ability, Set.AbilityLevel);
		AbilitySpec.DynamicAbilityTags.AddTag(Set.InputTag);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}

	for (const FWintAbilitySet_AttributeSet& Set : GrantedAttributes)
	{
		if (!IsValid(Set.AttributeSet))
		{
			return;
		}
		
		UAttributeSet* NewSet = NewObject<UAttributeSet>(AbilitySystemComponent->GetOwner(), Set.AttributeSet);
		AbilitySystemComponent->AddAttributeSetSubobject(NewSet);
	}

	for (const FWintAbilitySet_GameplayEffect& Set : GrantedEffects)
	{
		if (!IsValid(Set.GameplayEffect))
		{
			return;
		}
		
		FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
		ContextHandle.AddSourceObject(AbilitySystemComponent->GetOwner());

		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Set.GameplayEffect, Set.EffectLevel, ContextHandle);
		AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);
	}
}
