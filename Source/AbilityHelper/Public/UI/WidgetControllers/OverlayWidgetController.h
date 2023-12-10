// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WintWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

/**
 * OverlayWidgetController is used by the OverlayWidget to access and display data from the Player.
 */
UCLASS(BlueprintType, Blueprintable)
class ABILITYHELPER_API UOverlayWidgetController : public UWintWidgetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData &Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData &Data) const;

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
};
