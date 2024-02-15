// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"



void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	const float AbilityLevel = GetAbilityLevel();
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, AbilityLevel);
	for (const auto& Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(AbilityLevel);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, Pair.Key, ScaledDamage);
		UAbilitySystemBlueprintLibrary::AddAssetTag(DamageSpecHandle, Pair.Key);
	}

	UAbilitySystemComponent* SourceGAS = GetAbilitySystemComponentFromActorInfo();
	UAbilitySystemComponent* TargetGAS = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	SourceGAS->BP_ApplyGameplayEffectSpecToTarget(DamageSpecHandle, TargetGAS);
}

const FTaggedMontage& UAuraDamageGameplayAbility::GetRandomTaggedMontageFormArray(const TArray<FTaggedMontage>& TaggedMontages) const
{
	if (TaggedMontages.Num() == 1)
	{
		return TaggedMontages[0];
	}
	if (TaggedMontages.Num() > 0)
	{
		const int32 Selection = FMath::RandRange(0, TaggedMontages.Num() - 1);
		return TaggedMontages[Selection];
	}
	return FTaggedMontage::Empty;
}
