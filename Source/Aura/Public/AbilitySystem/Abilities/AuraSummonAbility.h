// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class AURA_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations(bool bDrawDebug);

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	int32 NumMinions = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UFUNCTION(BlueprintPure)
	TSubclassOf<APawn> GetRandomMinionClass() const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float MinSpawnDistance = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float MaxSpawnDistance = 250.f;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float SpawnSpread = 90.f;

};
