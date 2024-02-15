// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Aura.h"


UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController()
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetOwnerController(GetOwningPlayerController());
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController()
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetOwnerController(GetOwningPlayerController());
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

// Call from AAuraCharacter::InitAbilityActorInfo()
void AAuraHUD::InitOverlay() 
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass uninitialized, please fill out B_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass uninitialized, please fill out B_AuraHUD"));

	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);


	UOverlayWidgetController* OverlayWC = GetOverlayWidgetController();

	OverlayWidget->SetWidgetController(OverlayWC);
	OverlayWC->BroadcastInitialValues();

	OverlayWidget->AddToViewport();
}

void AAuraHUD::ShowFloatingDamage(const FVector& Target, float Damage)
{
	if (!IsValid(FloatingWidgetClass)) return;

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), FloatingWidgetClass);
	const APlayerController* PC = GetOwningPlayerController();
	FVector2D ScreenLocation;
	PC->ProjectWorldLocationToScreen(Target, ScreenLocation);
	
	Widget->AddToViewport();
	Widget->SetPositionInViewport(ScreenLocation);
}


