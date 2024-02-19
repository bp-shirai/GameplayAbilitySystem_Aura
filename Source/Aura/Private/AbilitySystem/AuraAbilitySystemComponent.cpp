// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraGameplayTags.h"
#include "Aura.h"


void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::OnGameplayEffectAppliedToSelf_Client);
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{

	for (const TSubclassOf<UGameplayAbility> AbilityClass : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
		//GiveAbilityAndActivateOnce(AbilitySpec);
	}

	OnAbilitiesGiven.Broadcast();
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid() == false) return; // TagName == "None"

	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec); //Spec.InputPressed = true;
			if (AbilitySpec.IsActive() == false)
			{
				TryActivateAbility(AbilitySpec.Handle);
				//UE_LOG(LogAura, Log, TEXT("Input ID = %d"), AbilitySpec.InputID);
			}
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid() == false) return;

	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec); //Spec.InputPressed = false;
		}
	}
}

void UAuraAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);

	OnGiveAbilityCallbacks.Broadcast(AbilitySpec);

	//UE_LOG(LogAura, Warning, TEXT("%s : %s : %s"), TEXT(__FUNCTION__), *GetNameSafe(this->GetOwnerActor()), *AbilitySpec.GetDebugString());
}

void UAuraAbilitySystemComponent::OnGameplayEffectAppliedToSelf_Client_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	OnAssetTagsApplied.Broadcast(TagContainer);
}

const FGameplayTag& UAuraAbilitySystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec) const
{
	if (AbilitySpec.Ability)
	{
		for (auto& Tag : AbilitySpec.Ability.Get()->AbilityTags)
		{
			if (Tag.MatchesTag(Abilities_All))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag::EmptyTag;
}

const FGameplayTag& UAuraAbilitySystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec) const
{
	if (AbilitySpec.Ability)
	{
		for (auto& Tag : AbilitySpec.DynamicAbilityTags)
		{
			if (Tag.MatchesTag(Input_All))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag::EmptyTag;
}


void UAuraAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	OnAbilitiesGiven.Broadcast();

	//UE_LOG(LogAura, Warning, TEXT("%s : %s"), TEXT(__FUNCTION__), *GetNameSafe(GetOwnerActor()));
}

int32 UAuraAbilitySystemComponent::GetInputID(const TSubclassOf<UGameplayAbility> AbilityClass) const
{
	int32 InputID = -1;

	if (auto AuraAbility = Cast<UAuraGameplayAbility>(AbilityClass->GetDefaultObject()))
	{
		InputID = static_cast<int32>(AuraAbility->AbilityInputID);
	}

	return InputID;
}
