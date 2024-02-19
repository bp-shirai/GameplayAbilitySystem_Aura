// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAssetTagsApplied, const FGameplayTagContainer& /*AssetTags*/);

DECLARE_MULTICAST_DELEGATE(FOnAbilitiesGiven);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGiveAbility, const FGameplayAbilitySpec& /*AbilitySpec*/);


/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AbilityActorInfoSet();

	FOnAssetTagsApplied OnAssetTagsApplied;
	FOnAbilitiesGiven OnAbilitiesGiven;
	FOnGiveAbility OnGiveAbilityCallbacks;

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);


	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;

	const FGameplayTag& GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec) const;
	const FGameplayTag& GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec) const;

	int32 GetInputID(const TSubclassOf<UGameplayAbility> AbilityClass) const;

protected:
	// COND_ReplayOrOwner
	virtual void OnRep_ActivateAbilities() override; 

	UFUNCTION(Client, Reliable)
	void OnGameplayEffectAppliedToSelf_Client(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};