// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/OverlayWidgetController.h"

#include "AbilitySystem/JozAttributeSet.h"

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UJozAttributeSet* AshAttributeSet = CastChecked<UJozAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AshAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AshAttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UJozAttributeSet* AshAttributeSet = CastChecked<UJozAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AshAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AshAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}