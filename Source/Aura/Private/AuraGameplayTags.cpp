// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"
#include "NativeGameplayTags.h"


UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Strength, "Attributes.Primary.Strength")
UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Intelligence, "Attributes.Primary.Intelligence")
UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Resilience, "Attributes.Primary.Resilience")
UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Vigor, "Attributes.Primary.Vigor")

UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_Armor, "Attributes.Secondary.Armor")
UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_ArmorPenetration, "Attributes.Secondary.ArmorPenetration")
UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_BlockChance, "Attributes.Secondary.BlockChance")
UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_CriticalHitChance, "Attributes.Secondary.CriticalHitChance")
UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_CriticalHitDamage, "Attributes.Secondary.CriticalHitDamage")
UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_CriticalHitResistance, "Attributes.Secondary.CriticalHitResistance")
UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_HealthRegeneration, "Attributes.Secondary.HealthRegeneration")
UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_ManaRegeneration, "Attributes.Secondary.ManaRegeneration")
UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_MaxHealth, "Attributes.Secondary.MaxHealth")
UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_MaxMana, "Attributes.Secondary.MaxMana")
UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_MoveSpeed, "Attributes.Secondary.MoveSpeed")

UE_DEFINE_GAMEPLAY_TAG(Attributes_Vital_Health, "Attributes.Vital.Health")
UE_DEFINE_GAMEPLAY_TAG(Attributes_Vital_Mana, "Attributes.Vital.Mana")

UE_DEFINE_GAMEPLAY_TAG(Input_LMB, "Input.LMB")
UE_DEFINE_GAMEPLAY_TAG(Input_RMB, "Input.RMB")
UE_DEFINE_GAMEPLAY_TAG(Input_Action1, "Input.Action1")
UE_DEFINE_GAMEPLAY_TAG(Input_Action2, "Input.Action2")
UE_DEFINE_GAMEPLAY_TAG(Input_Action3, "Input.Action3")
UE_DEFINE_GAMEPLAY_TAG(Input_Action4, "Input.Action4")

//UE_DEFINE_GAMEPLAY_TAG(Effect_Damage, "Effect.Damage")
//UE_DEFINE_GAMEPLAY_TAG(Effect_HitReact, "Effect.HitReact")
UE_DEFINE_GAMEPLAY_TAG(State_HitReact, "State.HitReact")
UE_DEFINE_GAMEPLAY_TAG(State_HitReact_BlockedHit, "State.HitReact.BlockedHit")
UE_DEFINE_GAMEPLAY_TAG(State_HitReact_CriticalHit, "State.HitReact.CriticalHit")
UE_DEFINE_GAMEPLAY_TAG(State_HitReact_Dead, "State.HitReact.Dead")

UE_DEFINE_GAMEPLAY_TAG(DamageType_All, "DamageType")
UE_DEFINE_GAMEPLAY_TAG(DamageType_Physical, "DamageType.Physical")
UE_DEFINE_GAMEPLAY_TAG(DamageType_Fire, "DamageType.Fire")
UE_DEFINE_GAMEPLAY_TAG(DamageType_Lightning, "DamageType.Lightning")
UE_DEFINE_GAMEPLAY_TAG(DamageType_Arcane, "DamageType.Arcane")

UE_DEFINE_GAMEPLAY_TAG(Event_EndAbility, "Event.EndAbility")


UE_DEFINE_GAMEPLAY_TAG(Team_Player, "Team.Player")
UE_DEFINE_GAMEPLAY_TAG(Team_Enemy, "Team.Enemy")

UE_DEFINE_GAMEPLAY_TAG(Message_All, "Message")

UE_DEFINE_GAMEPLAY_TAG(Abilities_Attack_Default, "Abilities.Attack.Default")
UE_DEFINE_GAMEPLAY_TAG(Abilities_Attack_Summon, "Abilities.Attack.Summon")

UE_DEFINE_GAMEPLAY_TAG(Montage_Attack_1, "Montage.Attack.1")
UE_DEFINE_GAMEPLAY_TAG(Montage_Attack_2, "Montage.Attack.2")
UE_DEFINE_GAMEPLAY_TAG(Montage_Attack_3, "Montage.Attack.3")
UE_DEFINE_GAMEPLAY_TAG(Montage_Attack_4, "Montage.Attack.4")


UE_DEFINE_GAMEPLAY_TAG(CombatSocket_Weapon, "CombatSocket.Weapon")
UE_DEFINE_GAMEPLAY_TAG(CombatSocket_LeftHand, "CombatSocket.LeftHand")
UE_DEFINE_GAMEPLAY_TAG(CombatSocket_RightHand, "CombatSocket.RightHand")
UE_DEFINE_GAMEPLAY_TAG(CombatSocket_Tail, "CombatSocket.Tail")


//FAuraGameplayTags FAuraGameplayTags::GameplayTags;


// For get variable name.
//#define TO_STRING(VariableName) # VariableName

//UE_DEFINE_GAMEPLAY_TAG_STATIC()

/*
void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

#define DEFINE_GAMEPLAY_NATIVE_TAG(PropertyName, TagName, DevComment) GameplayTags.PropertyName = Manager.AddNativeGameplayTag(FName(TagName), FString(DevComment));
	
	DEFINE_GAMEPLAY_NATIVE_TAG(Attributes_Primary_Strength,		"Attributes.Primary.Strength", "Increases physical damage");
	DEFINE_GAMEPLAY_NATIVE_TAG(Attributes_Primary_Intelligence, "Attributes.Primary.Intelligence", "Increases magical damage");
	DEFINE_GAMEPLAY_NATIVE_TAG(Attributes_Primary_Resilience,	"Attributes.Primary.Resilience", "Increases armor and armor penetration");
	DEFINE_GAMEPLAY_NATIVE_TAG(Attributes_Primary_Vigor,		"Attributes.Primary.Vigor", "Increases health");

	DEFINE_GAMEPLAY_NATIVE_TAG(Attributes_Secondary_Armor, "Attributes.Secondary.Armor", "Reduce damage taken, improves block chance");
	DEFINE_GAMEPLAY_NATIVE_TAG(Attributes_Secondary_ArmorPenetration, "Attributes.Secondary.ArmorPenetration", "Ignores percentage of enemy armor, increases critical hit chance");
	DEFINE_GAMEPLAY_NATIVE_TAG(Attributes_Secondary_BlockChance, "Attributes.Secondary.BlockChance", "Chance to cut incoming damage in half");
	DEFINE_GAMEPLAY_NATIVE_TAG(Attributes_Secondary_CriticalHitChance, "Attributes.Secondary.CriticalHitChance", "Chance to double damage plus critical hit bonus");
	DEFINE_GAMEPLAY_NATIVE_TAG(Attributes_Secondary_CriticalHitDamage, "Attributes.Secondary.CriticalHitDamage", "Bonus damage added when a critical hit is scored");
	DEFINE_GAMEPLAY_NATIVE_TAG(Attributes_Secondary_CriticalHitResistance, "Attributes.Secondary.CriticalHitResistance", "Reduces critical hit chance of attacking enemies");
	DEFINE_GAMEPLAY_NATIVE_TAG(Attributes_Secondary_HealthRegeneration, "Attributes.Secondary.HealthRegeneration", "Amount of health regenerated every 1 second");
	DEFINE_GAMEPLAY_NATIVE_TAG(Attributes_Secondary_ManaRegeneration, "Attributes.Secondary.ManaRegeneration", "Amount of mana regenerated every 1 second");
	DEFINE_GAMEPLAY_NATIVE_TAG(Attributes_Secondary_MaxHealth, "Attributes.Secondary.MaxHealth", "Maximum amount of health obtainable");
	DEFINE_GAMEPLAY_NATIVE_TAG(Attributes_Secondary_MaxMana, "Attributes.Secondary.MaxMana", "Maximum amount of mana obtainable");

	//Attributes_Secondary_Armor = Manager.AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken, improves block chance"));
#undef DEFINE_GAMEPLAY_NATIVE_TAG
}


FAuraAttributeTags FAuraAttributeTags::Attributes;


void FAuraAttributeTags::InitializeNativeGameplayTags() // Called from AuraAssetManager
{
	
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
#define DEFINE_GAMEPLAY_TAG(PropertyName) PropertyName = Manager.AddNativeGameplayTag(FName(TO_STRING(PropertyName)));\
	UE_LOG(LogTemp, Log, TEXT("[%s]"), PropertyName.GetTagName());
	
	DEFINE_GAMEPLAY_TAG(Attributes.Primary.Strength);
	DEFINE_GAMEPLAY_TAG(Attributes.Primary.Intelligence);
	DEFINE_GAMEPLAY_TAG(Attributes.Primary.Resilience);
	DEFINE_GAMEPLAY_TAG(Attributes.Primary.Vigor);
	DEFINE_GAMEPLAY_TAG(Attributes.Secondary.Armor);
	DEFINE_GAMEPLAY_TAG(Attributes.Secondary.ArmorPenetration);
	DEFINE_GAMEPLAY_TAG(Attributes.Secondary.BlockChance);
	DEFINE_GAMEPLAY_TAG(Attributes.Secondary.CriticalHitChance);
	DEFINE_GAMEPLAY_TAG(Attributes.Secondary.CriticalHitDamage);
	DEFINE_GAMEPLAY_TAG(Attributes.Secondary.CriticalHitResistance);
	DEFINE_GAMEPLAY_TAG(Attributes.Secondary.HealthRegeneration);
	DEFINE_GAMEPLAY_TAG(Attributes.Secondary.ManaRegeneration);
	DEFINE_GAMEPLAY_TAG(Attributes.Secondary.MaxHealth);
	DEFINE_GAMEPLAY_TAG(Attributes.Secondary.MaxMana);


#undef DEFINE_GAMEPLAY_TAG
}*/
