// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/OverlayWidgetController.h"

#include "AbilitySystem\WintAttributeSet.h"

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
	const UWintAttributeSet* AshAttributeSet = CastChecked<UWintAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AshAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AshAttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UWintAttributeSet* AshAttributeSet = CastChecked<UWintAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AshAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AshAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}