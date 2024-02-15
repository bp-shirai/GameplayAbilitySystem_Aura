// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AI/AuraAIController.h"
#include "AuraEnemy.generated.h"


class UWidgetComponent;
class UBehaviorTree;
class AAuraAIController;

/**
 * 
 */
UCLASS(Abstract)
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemy();

	virtual void PossessedBy(AController* NewController) override;

	virtual void HighlightActor() override;

	virtual void UnHighlightActor() override;

	//UPROPERTY(BlueprintReadOnly, Category = "Combat")
	//bool bHighlighted = false;

	// Combat Interface
	virtual int32 GetPlayerLevel() const override;


	UPROPERTY(BlueprintAssignable, Category = "WidgetController")
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "WidgetController")
	FOnAttributeChanged OnMaxHealthChanged;

	UFUNCTION()
	void OnHitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = "Defaults|Combat")
	bool bHitReacting = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults|Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults|Combat")
	float LifeSpan = 5.f;

	virtual void Die() override;

	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "Defaults|Combat")
	TObjectPtr<AActor> CombatTarget;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	virtual void InitializeDefaultAttributes() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defaults")
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category = "Defaults|AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;

	UFUNCTION(BlueprintPure)
	ECharacterClass GetCharacterClass() const { return CharacterClass; }
};
