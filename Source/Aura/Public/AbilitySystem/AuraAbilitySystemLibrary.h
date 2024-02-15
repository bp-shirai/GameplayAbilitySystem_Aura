// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "GameplayTagContainer.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UOverlayWidgetController;
class UAttributeMenuWidgetController;
class UAbilitySystemComponent;
//class AAuraPlayerController;

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController", meta = (WorldContext = "WorldContextObject"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController", meta = (WorldContext = "WorldContextObject"))
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);


	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController", meta = (WorldContext = "WorldContextObject"))
	static APlayerController* GetFirstPlayerController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|CharacterClass", meta = (WorldContext = "WorldContextObject"))
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|CharacterClass", meta = (WorldContext = "WorldContextObject"))
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|CharacterClass", meta = (WorldContext = "WorldContextObject"))
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);
	

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|GameplayMechanics", meta = (WorldContext = "WorldContextObject"))
	static void GetLivePlayersWithRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, UPARAM(ref) TArray<AActor*>& IgnoreActors, float Radius, const FVector& SphereOrigin);



	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayTag")
	static const FGameplayTagContainer& GetAbilityTags(const UGameplayAbility* GameplayAbility);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|GameplayTag", meta = (WorldContext = "WorldContextObject"))
	static void GetAllActorsOfClassMatchingTag(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, const FGameplayTag GameplayTag, TArray<AActor*>& OutActors);
	
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|GameplayTag", meta = (WorldContext = "WorldContextObject", GameplayTagFilter = "Team"))
	static void GetAllActorsWithTeamTag(const UObject* WorldContextObject, const FGameplayTag TeamTag, TArray<AAuraCharacterBase*>& OutActors);


	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayTag")//meta = (ReturnDisplayName = "GameplayTagContainer")
	static FGameplayTagContainer GetActorTags(const AActor* InActor);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayTag")
	static bool HasActorTag(const AActor* InActor, const FGameplayTag Tag, bool bExactMatch = true);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayTag")
	static FGameplayTag GetTeamTag(const AActor* InActor);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayTag")
	static bool HasTeamTag(const AActor* InActor, const FGameplayTag& TeamTag);


	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayMechanics")
	static bool IsTeamFriend(const AActor* FirstActor, const AActor* SecondActor);

};