// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WintUserWidget.generated.h"

/**
 * Base class for all widgets that are used with a WidgetController.
 */
UCLASS()
class ABILITYHELPER_API UWintUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	// Event that is called when the WidgetController is set.
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject *InWidgetController);
};
