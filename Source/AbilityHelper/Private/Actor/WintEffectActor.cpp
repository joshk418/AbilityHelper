// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor\WintEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

AWintEffectActor::AWintEffectActor()
{

}

void AWintEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AWintEffectActor::OnOverlap(AActor* TargetActor)
{
	for (const FGameplayEffectPolicy& EffectWithPolicy : Effects)
	{
		if (EffectWithPolicy.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			if (ApplyEffectToTarget(TargetActor, EffectWithPolicy.EffectClass) && EffectWithPolicy.bDestroyOnApplication)
			{
				Destroy();
			}
		}
	}
}

void AWintEffectActor::OnEndOverlap(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetAbilitySystemComp = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetAbilitySystemComp)
	{
		return;
	}

	for (const FGameplayEffectPolicy& EffectWithPolicy : Effects)
	{
		if (EffectWithPolicy.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, EffectWithPolicy.EffectClass);
		}

		if (EffectWithPolicy.EffectClass.GetDefaultObject()->DurationPolicy != EGameplayEffectDurationType::Infinite)
		{
			continue;
		}

		if (EffectWithPolicy.RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			TArray<FActiveGameplayEffectHandle> RemovableHandles;
			for (TTuple<FActiveGameplayEffectHandle, FAbilitySystemEffectClassData> ActiveEffect : ActiveInfiniteEffects)
			{
				if (ActiveEffect.Value.AbilitySystemComponent == TargetAbilitySystemComp && ActiveEffect.Value.EffectClass == EffectWithPolicy.EffectClass)
				{
					TargetAbilitySystemComp->RemoveActiveGameplayEffect(ActiveEffect.Key, 1);

					if (EffectWithPolicy.bDestroyOnRemoval)
					{
						Destroy();
						return;
					}

					RemovableHandles.Add(ActiveEffect.Key);
				}
			}

			for (const FActiveGameplayEffectHandle& Handle : RemovableHandles)
			{
				ActiveInfiniteEffects.FindAndRemoveChecked(Handle);
			}
		}
	}
}

bool AWintEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass)
{
	UAbilitySystemComponent* TargetAbilitySystemComp = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetAbilitySystemComp)
	{
		return false;
	}

	if (!EffectClass)
	{
		return false;
	}

	FGameplayEffectContextHandle EffectContext = TargetAbilitySystemComp->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComp->MakeOutgoingSpec(EffectClass, 1, EffectContext);
	if (!EffectSpecHandle.IsValid())
	{
		return false;
	}

	FActiveGameplayEffectHandle EffectHandle = TargetAbilitySystemComp->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	if (EffectHandle.WasSuccessfullyApplied())
	{
		if (EffectClass.GetDefaultObject()->DurationPolicy == EGameplayEffectDurationType::Infinite)
		{
			FAbilitySystemEffectClassData EffectClassData;
			EffectClassData.AbilitySystemComponent = TargetAbilitySystemComp;
			EffectClassData.EffectClass = EffectClass;

			ActiveInfiniteEffects.Add(EffectHandle, EffectClassData);
		}

		return true;
	}

	return false;
}
