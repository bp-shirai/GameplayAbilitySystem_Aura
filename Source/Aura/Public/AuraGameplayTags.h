// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Strength)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Intelligence)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Resilience)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Vigor)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_Armor)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ArmorPenetration)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_BlockChance)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitChance)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitDamage)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitResistance)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_HealthRegeneration)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ManaRegeneration)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxHealth)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxMana)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MoveSpeed)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_Health)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Vital_Mana)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_LMB)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_RMB)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action1)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action2)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action3)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action4)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Damage)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_HitReact)


/**
 * AuraGameplayTags
 * 
 * Singleton containing native Gameplay Tags
 */
/*
struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;



protected:

private:
	static FAuraGameplayTags GameplayTags;
};
*/

/*
struct FAuraAttributeTags
{
public:

	static const FAuraAttributeTags& Get() { return Attributes; }

	static void InitializeNativeGameplayTags();

	struct FPrimary
	{
		FGameplayTag Strength;
		FGameplayTag Intelligence;
		FGameplayTag Resilience;
		FGameplayTag Vigor;
	};
	FPrimary Primary;

	struct FSecondary
	{
		FGameplayTag Armor;
		FGameplayTag ArmorPenetration;
		FGameplayTag BlockChance;
		FGameplayTag CriticalHitChance;
		FGameplayTag CriticalHitDamage;
		FGameplayTag CriticalHitResistance;
		FGameplayTag HealthRegeneration;
		FGameplayTag ManaRegeneration;
		FGameplayTag MaxHealth;
		FGameplayTag MaxMana;
		FGameplayTag Test;

	};
	FSecondary Secondary;

private:
	static FAuraAttributeTags Attributes;
};*/