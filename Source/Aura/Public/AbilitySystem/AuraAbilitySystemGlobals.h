// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "AuraAbilitySystemGlobals.generated.h"




/**
 *	DefaultGame.ini
 *	[/Script/GameplayAbilities.AbilitySystemGlobals]
 *	+AbilitySystemGlobalsClassName="/Script/Aura.AuraAbilitySystemGlobals"
 */
UCLASS()
class AURA_API UAuraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
