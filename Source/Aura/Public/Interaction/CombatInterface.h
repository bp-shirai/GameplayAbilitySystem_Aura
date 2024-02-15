// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "CombatInterface.generated.h"

class UNiagaraSystem;
class UAnimInstance;


USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Montage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Montage"))
	FGameplayTag MontageTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "CombatSocket"))
	FGameplayTag SocketTag;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName TipSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundBase* ImpactSound = nullptr;

	static const FTaggedMontage Empty;
};

//UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()

public:

	virtual int32 GetPlayerLevel() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetCombatSocketLocation(const FGameplayTag& SocketTag);
	//FVector GetCombatSocketLocation(const FTaggedMontage& AttackMontage);

	//	virtual FVector GetCombatSocketLocation();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage() const;

	virtual void Die() = 0;

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Combat")
	//void OnDie();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetAvatar();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetCombatTarget(AActor* InCombatTarget);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetCombatTarget() const;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<FTaggedMontage> GetAttackMontages() const;

//	virtual const FTaggedMontage& GetAttackMontage(const FGameplayTag& MontageTag) const = 0;


	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)

	//UFUNCTION(BlueprintCallable)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FGameplayTag GetTeamTag() const;

	//UFUNCTION(BlueprintCallable)
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	//virtual bool IsNotFriend(const AActor* InActor);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UNiagaraSystem* GetBloodEffect() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FTaggedMontage GetTaggedMontageByTag(const FGameplayTag& MontageTag) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetMinionCount() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IncrementMinionCount(int32 Amount);

};
