// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/DamageTextComponent.h"

UDamageTextComponent::UDamageTextComponent()
{
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawAtDesiredSize(true);
	SetInitialSharedLayerName("HUD");
	SetInitialLayerZOrder(0);
}
