// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers\WintWidgetController.h"

void UWintWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& Params)
{
	PlayerController = Params.PlayerController;
	PlayerState = Params.PlayerState;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	AttributeSet = Params.AttributeSet;
}

void UWintWidgetController::BroadcastInitialValues()
{
}

void UWintWidgetController::BindCallbacksToDependencies()
{
}
