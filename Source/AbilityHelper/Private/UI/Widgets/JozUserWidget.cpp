// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/JozUserWidget.h"

void UJozUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
