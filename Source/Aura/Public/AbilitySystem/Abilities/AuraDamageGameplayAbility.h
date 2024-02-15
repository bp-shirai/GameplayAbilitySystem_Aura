// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraDamageGameplayAbility.generated.h"


USTRUCT(BlueprintType)
struct FDamageRange
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat DamageMin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat DamageMax;
};

/**
 * 
 */
UCLASS(Abstract)
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

	UFUNCTION(BlueprintPure)
	const FTaggedMontage& GetRandomTaggedMontageFormArray(const TArray<FTaggedMontage>& TaggedMontages) const;

protected:

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults|Damage")
	//FScalableFloat Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults|Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults|Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
