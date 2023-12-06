// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/JozWidgetController.h"

void UJozWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& Params)
{
	PlayerController = Params.PlayerController;
	PlayerState = Params.PlayerState;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	AttributeSet = Params.AttributeSet;
}

void UJozWidgetController::BroadcastInitialValues()
{
}

void UJozWidgetController::BindCallbacksToDependencies()
{
}
