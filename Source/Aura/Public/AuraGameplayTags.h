// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

// Tag_Attribute
// Tag_Ability
// Tag_Event
// Tag_State
// Tag_DamageType
// Tag_Montage
// Tag_Socket
// Tag_Input
// Tag_Team
// Tag_Message



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

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_All)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_LMB)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_RMB)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action1)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action2)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action3)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action4)

//UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Damage)
//UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_HitReact)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_HitReact)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_HitReact_BlockedHit)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_HitReact_CriticalHit)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_HitReact_Dead)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(DamageType_All)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(DamageType_Physical)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(DamageType_Fire)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(DamageType_Lightning)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(DamageType_Arcane)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_EndAbility)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Team_Player)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Team_Enemy)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_All)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_All)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Attack_Default)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Attack_Summon)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Abilities_Attack_Fire_FireBolt)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cooldown_Attack_Fire_FireBolt)


UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_Attack_1)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_Attack_2)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_Attack_3)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_Attack_4)


UE_DECLARE_GAMEPLAY_TAG_EXTERN(CombatSocket_Weapon)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(CombatSocket_RightHand)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(CombatSocket_LeftHand)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(CombatSocket_Tail)


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