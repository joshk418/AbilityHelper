// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets\WintUserWidget.h"

void UWintUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
