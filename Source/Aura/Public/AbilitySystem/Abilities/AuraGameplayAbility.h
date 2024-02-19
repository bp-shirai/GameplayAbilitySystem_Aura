// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None,
	LMB,
	RMB,
	Action1,
	Action2,
	Action3,
	Action4,

	Attack,
	Aim,
	Reload,
	NextWeapon,
	PrevWeapon,
	DropWeapon,
	EquipWeapon,
	UnEquipWeapon,

	Cancel,
	Sprint,
	Jump,
	Crouch,
	Confirm,
};


/**
 * 
 */
UCLASS(Abstract)
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
	EAbilityInputID AbilityInputID = EAbilityInputID::None;


};
