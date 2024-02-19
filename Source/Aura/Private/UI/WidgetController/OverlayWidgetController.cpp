// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/LevelUpInfo.h"

#include "Aura.h"
#include "Player/AuraPlayerState.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AS->GetHealth());
	OnMaxHealthChanged.Broadcast(AS->GetMaxHealth());
	OnManaChanged.Broadcast(AS->GetMana());
	OnMaxManaChanged.Broadcast(AS->GetMaxMana());

	OnAbilitiesGiven();// OnInitializeStartupAbilities()
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	AAuraPlayerState* PS = CastChecked<AAuraPlayerState>(PlayerState);

	PS->OnXPChangedDelegate.AddUObject(this, &ThisClass::OnXPChanged);

#define BIND_CALLBACK(AttributeName) AbilitySystem->GetGameplayAttributeValueChangeDelegate(AS->Get##AttributeName##Attribute()).AddLambda(\
	[this](const FOnAttributeChangeData& Data) { On##AttributeName##Changed.Broadcast(Data.NewValue); } );

	BIND_CALLBACK(Health);
	BIND_CALLBACK(MaxHealth);
	BIND_CALLBACK(Mana);
	BIND_CALLBACK(MaxMana);

#undef BIND_CALLBACK


	UAuraAbilitySystemComponent* ASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystem);

	ASC->OnAbilitiesGiven.AddUObject(this, &ThisClass::OnAbilitiesGiven); // OnInitializeStartupAbilities()

	ASC->OnAssetTagsApplied.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			//static const auto MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			for (const FGameplayTag& Tag : AssetTags)
			{
				if (Tag.MatchesTag(Message_All))
				{
					// TODO: Broadcast the tag to the widget controller
				
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					OnMessageWidgetRow.Broadcast(*Row);
				}
			}
		});
}

void UOverlayWidgetController::OnAbilitiesGiven()// OnInitializeStartupAbilities()
{
	UAuraAbilitySystemComponent* ASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystem);

	for (const auto& AbilitySpec : ASC->GetActivatableAbilities())
	{
		auto& AbilityTag = ASC->GetAbilityTagFromSpec(AbilitySpec);
		auto& InputTag = ASC->GetInputTagFromSpec(AbilitySpec);
		auto& Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);

		OnGiveAbilityInfo.Broadcast(Info, InputTag);
		//UE_LOG(LogAura, Warning, TEXT("%s : %s"), *AbilityTag.GetTagName().ToString(), *InputTag.GetTagName().ToString());
	}
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP) const
{
	const AAuraPlayerState* PS = CastChecked<AAuraPlayerState>(PlayerState);
	const ULevelUpInfo* LevelUpInfo = PS->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("Unable to find LevelUpInfo. Please fill out AuraPlayerState Blueprint"));

	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);

		OnXPPercentChanged.Broadcast(XPBarPercent);
	}

}

