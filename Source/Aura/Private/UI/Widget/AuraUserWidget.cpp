// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/AuraUserWidget.h"



void UAuraUserWidget::SetWidgetController_Implementation(UObject* InWidgetController)
{
	WidgetController = InWidgetController;

	OnSetWidgetController();
}
