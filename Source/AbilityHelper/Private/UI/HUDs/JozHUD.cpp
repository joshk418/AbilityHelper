// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDs/JozHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/WidgetControllers/OverlayWidgetController.h"
#include "UI/Widgets/JozUserWidget.h"

void AJozHUD::BeginPlay()
{
	Super::BeginPlay();
}

UOverlayWidgetController* AJozHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(Params);
		OverlayWidgetController->BindCallbacksToDependencies();
	}

	return OverlayWidgetController;
}

void AJozHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is null"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is null"));

	UJozUserWidget* Widget = CreateWidget<UJozUserWidget>(PC, OverlayWidgetClass);
	OverlayWidget = Widget;

	const FWidgetControllerParams WidgetControllerParams = FWidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}
