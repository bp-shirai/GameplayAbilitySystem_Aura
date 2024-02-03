// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FAuraAttributeInfo;
struct FGameplayTag;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeValueChanged, const FAuraAttributeInfo&, Info, float, AttributeValue);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:

	virtual void BindCallbacksToDependencies() override;

	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeValueChanged OnAttributeValueChanged;

	UFUNCTION(BlueprintCallable)
	int32 GetBindFunctionCount() const;

	UFUNCTION(BlueprintCallable)
	bool IsBindFunctions() const;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	TObjectPtr<UAttributeInfo> AttributeInfo; // DataAsset
	
	// Helper function to broadcast attributes
	void BroadcastAttributeInfoForTag(const FGameplayTag& Tag) const;

	void BroadcastAttributeInfo(const FAuraAttributeInfo& Info) const;
};
