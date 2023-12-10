// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUDs\WintHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/WidgetControllers/OverlayWidgetController.h"
#include "UI/Widgets\WintUserWidget.h"

void AWintHUD::BeginPlay()
{
	Super::BeginPlay();
}

UOverlayWidgetController *AWintHUD::GetOverlayWidgetController(const FWidgetControllerParams &Params)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(Params);
		OverlayWidgetController->BindCallbacksToDependencies();
	}

	return OverlayWidgetController;
}

void AWintHUD::InitOverlay(APlayerController *PC, APlayerState *PS, UAbilitySystemComponent *ASC, UAttributeSet *AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is null"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is null"));

	UWintUserWidget *Widget = CreateWidget<UWintUserWidget>(PC, OverlayWidgetClass);
	OverlayWidget = Widget;

	const FWidgetControllerParams WidgetControllerParams = FWidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController *WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}
