// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "WidgetController")
	void SetWidgetController(UObject* InWidgetController);
	virtual void SetWidgetController_Implementation(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UObject> WidgetController;

	UFUNCTION(BlueprintImplementableEvent, Category = "WidgetController")
	void OnSetWidgetController();
};
