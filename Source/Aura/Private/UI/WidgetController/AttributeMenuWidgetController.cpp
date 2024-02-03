// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"


void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	//const UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	// The DataAsset
	check(AttributeInfo);
	

	for (const auto& Info : AttributeInfo->AttributeInformation)
	{
		BroadcastAttributeInfo(Info);
	}

	//for (const auto& Pair : AttributeInfo->AttributeInfoMap)
	//{
	//	BroadcastAttributeInfo(Pair.Value);
	//}
}

int32 UAttributeMenuWidgetController::GetBindFunctionCount() const
{
	auto Objects = OnAttributeValueChanged.GetAllObjects();
	return Objects.Num();
}

bool UAttributeMenuWidgetController::IsBindFunctions() const
{
	return OnAttributeValueChanged.IsBound();
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	check(AttributeInfo);
	for (const auto& Info : AttributeInfo->AttributeInformation)
	{
		AbilitySystem->GetGameplayAttributeValueChangeDelegate(Info.AttributeGetter).AddLambda(
			[this, Info](const FOnAttributeChangeData& Data) {
				BroadcastAttributeInfo(Info);
			}
		);
	}
	/*
	for (const auto& Info : AttributeInfo->AttributeInformation)
	{
		AbilitySystem->GetGameplayAttributeValueChangeDelegate(Info.AttributeGetter).AddLambda(
			[this, Info](const FOnAttributeChangeData& Data) {
				BroadcastAttributeInfoFromTag(Info.AttributeTag);
			}
		);
	}
*/
	/*
	for (const auto& Pair : AttributeInfo->AttributeInfoMap)
	{
		const FGameplayTag& Tag = Pair.Key;
		const FAuraAttributeInfo* Info = AttributeInfo->FindAttributeInfo(Tag);

		AbilitySystem->GetGameplayAttributeValueChangeDelegate(Pair.Value.AttributeGetter).AddLambda(
			[this, Info](const FOnAttributeChangeData& Data)
			{
				float AttributeValue = Info->AttributeGetter.GetNumericValue(AttributeSet);
				OnAttributeValueChanged.Broadcast(*Info, AttributeValue);
			}
		);
	}*/
}

void UAttributeMenuWidgetController::BroadcastAttributeInfoForTag(const FGameplayTag& Tag) const
{
	// Getting info from DataAsset based on the gameplay tag match.
	const FAuraAttributeInfo& Info = AttributeInfo->FindAttributeInfoForTag(Tag);
	float AttributeValue = Info.AttributeGetter.GetNumericValue(AttributeSet);
	// Broadcast for those who subscribe. IE the attribute menu widget in blueprint
	OnAttributeValueChanged.Broadcast(Info, AttributeValue);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FAuraAttributeInfo& Info) const
{
	float AttributeValue = Info.AttributeGetter.GetNumericValue(AttributeSet);
	OnAttributeValueChanged.Broadcast(Info, AttributeValue);
}
