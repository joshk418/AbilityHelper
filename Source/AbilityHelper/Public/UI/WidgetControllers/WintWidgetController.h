// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WintWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FOnAttributeChangeData;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams()
	{
	}

	FWidgetControllerParams(APlayerController *InPlayerController, APlayerState *InPlayerState, UAbilitySystemComponent *InAbilitySystemComponent, UAttributeSet *InAttributeSet)
	{
		PlayerController = InPlayerController;
		PlayerState = InPlayerState;
		AbilitySystemComponent = InAbilitySystemComponent;
		AttributeSet = InAttributeSet;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * WidgetController base class to act as a bridge between the UI and the Player.
 */
UCLASS()
class ABILITYHELPER_API UWintWidgetController : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController|Player")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController|Player")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController|AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController|AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	void SetWidgetControllerParams(const FWidgetControllerParams &Params);

	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();
};
