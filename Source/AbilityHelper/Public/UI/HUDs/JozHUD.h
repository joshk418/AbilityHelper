// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JozHUD.generated.h"

class UJozUserWidget;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class ABILITYHELPER_API AJozHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<UJozUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

public:
	TObjectPtr<UJozUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;

public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& Params);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
};
