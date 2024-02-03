// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AuraWidgetController.h"
#include "Player/AuraPlayerState.h"

/*
void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystem = WCParams.AbilitySystem;
	AttributeSet = WCParams.AttributeSet;
}*/

void UAuraWidgetController::SetOwnerController(APlayerController* InPlayerController)
{
	check(InPlayerController);

	AAuraPlayerState* PS = CastChecked<AAuraPlayerState>(InPlayerController->PlayerState);
	AbilitySystem = PS->GetAbilitySystemComponent();
	AttributeSet = PS->GetAttributeSet();
	PlayerController = InPlayerController;
	PlayerState = InPlayerController->PlayerState;
	
	check(AbilitySystem);
	check(AttributeSet);
	check(PlayerState);
}

void UAuraWidgetController::BroadcastInitialValues()
{
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
}
