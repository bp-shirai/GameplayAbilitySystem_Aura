// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "GameplayTagAssetInterface.h"
#include "AuraCharacterBase.generated.h"



class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class UNiagaraSystem;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	UFUNCTION(NetMulticast, Reliable)
	virtual void Die_Multicast();

	/***** Combat Interface *****/ 
	virtual void Die();	
	virtual UAnimMontage* GetHitReactMontage_Implementation() const override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& SocketTag) override;
	//virtual FVector GetCombatSocketLocation_Implementation(const FTaggedMontage& AttackMontage) override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() const override;
//	virtual const FTaggedMontage& GetAttackMontage(const FGameplayTag& MontageTag) const override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() const override;
	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) const override;
	virtual int32 GetMinionCount_Implementation() const override;
	virtual void IncrementMinionCount_Implementation(int32 Amount) override;
	/** End CombatInterface */

	virtual FGameplayTag GetTeamTag_Implementation() const override;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults|Combat")
	TArray<FTaggedMontage> AttackMontages;

	UFUNCTION(CallInEditor)
	TArray<FName> GetSocketNames() const;

	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "Defaults|Combat")//meta = (AnimNotifyBoneName = "true")
	FName WeaponTipSocketName;
	UPROPERTY(EditAnywhere, Category = "Defaults|Combat")
	FName LeftHandSocketName;
	UPROPERTY(EditAnywhere, Category = "Defaults|Combat")
	FName RightHandSocketName;
	UPROPERTY(EditAnywhere, Category = "Defaults|Combat")
	FName TailSocketName;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, float Level) const;

	void AddCharacterAbilities();

	// Dissolve Effects
	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults|Dissolve")
	TObjectPtr<UMaterialInstance> DissolveMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults|Dissolve")
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults|Effects")
	TObjectPtr<UNiagaraSystem> BloodEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults|Effects")
	TObjectPtr<USoundBase> DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Tag")
	FGameplayTagContainer OwnedGameplayTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Tag", meta = (Categories = "Team"))
	FGameplayTag TeamTag;



	int32 MinionCount = 0;

private:

	UPROPERTY(EditAnywhere, Category = "Defaults")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY(EditAnywhere, Category = "Defaults|Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;

	bool bDead = false;
};
