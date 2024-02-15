// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystemComponent.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/HUD/AuraHUD.h"
#include "Game/AuraGameModeBase.h"
#include "AuraAbilityTypes.h"
#include "Aura.h"
#include "EngineUtils.h"
#include "GameplayTagAssetInterface.h"
#include "Interaction/CombatInterface.h"
#include "BlueprintGameplayTagLibrary.h"
#include "AuraGameplayTags.h"
#include "Character/AuraCharacterBase.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject) 
{
	if (const APlayerController* PC = GetFirstPlayerController(WorldContextObject))
	{
		if (AAuraHUD* AuraHUD = PC->GetHUD<AAuraHUD>())
		{
			return AuraHUD->GetOverlayWidgetController();
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (const APlayerController* PC = GetFirstPlayerController(WorldContextObject))
	{
		if (AAuraHUD* AuraHUD = PC->GetHUD<AAuraHUD>())
		{
			return AuraHUD->GetAttributeMenuWidgetController();
		}
	}
	return nullptr;
}

APlayerController* UAuraAbilitySystemLibrary::GetFirstPlayerController(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return nullptr;
	}

	return World->GetFirstPlayerController();
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	if (const UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject))
	{
		const FCharacterClassDefaultInfo DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
		
		const AActor* AvatarActor = ASC->GetAvatarActor();
		FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
		Context.AddSourceObject(AvatarActor);

		const FGameplayEffectSpecHandle PrimaryAttributesSpec = ASC->MakeOutgoingSpec(DefaultInfo.PrimaryAttributes, Level, Context);
		ASC->BP_ApplyGameplayEffectSpecToSelf(PrimaryAttributesSpec);

		const FGameplayEffectSpecHandle SecondaryAttributesSpec = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, Context);
		ASC->BP_ApplyGameplayEffectSpecToSelf(SecondaryAttributesSpec);

		const FGameplayEffectSpecHandle VitalAttributesSpec = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, Context);
		ASC->BP_ApplyGameplayEffectSpecToSelf(VitalAttributesSpec);

		for (auto& CommonEffect : CharacterClassInfo->CommonEffects)
		{
			const FGameplayEffectSpecHandle CommonSpec = ASC->MakeOutgoingSpec(CommonEffect, Level, Context);
			ASC->BP_ApplyGameplayEffectSpecToSelf(CommonSpec);
		}
	}
}

void UAuraAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	if (const UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject))
	{
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor());
		int32 CharacterLevel = CombatInterface ? CombatInterface->GetPlayerLevel() : 1;

		for (auto& AbilityClass : CharacterClassInfo->CommonAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, CharacterLevel);
			ASC->GiveAbility(AbilitySpec);
		}

		const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
		for (auto& AbilityClass : DefaultInfo.StartupAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, CharacterLevel);
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

UCharacterClassInfo* UAuraAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	if (const AAuraGameModeBase* GameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		return GameMode->CharacterClassInfo;
	}
	return nullptr;
}

bool UAuraAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->IsBlockedHit();
	}
	return false;
}

bool UAuraAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->IsCriticalHit();
	}
	return false;
}

void UAuraAbilitySystemLibrary::SetIsBlockedHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetIsBlockedHit(bInIsBlockedHit);
		//UE_LOG(LogAura, Log, TEXT("SetIsBlockedHit = %s"), TEXT_BOOL(bInIsBlockedHit));
	}
}

void UAuraAbilitySystemLibrary::SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetIsCriticalHit(bInIsCriticalHit);
		//UE_LOG(LogAura, Log, TEXT("SetIsCriticalHit = %s"), TEXT_BOOL(bInIsCriticalHit));

	}
}

void UAuraAbilitySystemLibrary::GetLivePlayersWithRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, UPARAM(ref) TArray<AActor*>& IgnoreActors, float Radius, const FVector& SphereOrigin)
{
	//UGameplayStatics::ApplyRadialDamageWithFalloff
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(IgnoreActors);

	TArray<FOverlapResult> Overlaps;
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		for (auto& Overlap : Overlaps)
		{
			AActor* Actor = Overlap.GetActor();
			ICombatInterface* Combat = Cast<ICombatInterface>(Actor);
			if (Combat && IsValid(Actor))
			{
				//const bool bIsCombat = Actor->Implements<UCombatInterface>();
				//const bool IsDead = ICombatInterface::Execute_IsDead(Actor);
				if (!Combat->Execute_IsDead(Actor))
				{
					OutOverlappingActors.AddUnique(Combat->Execute_GetAvatar(Actor));
				}
			}
		}
	}
}




const FGameplayTagContainer& UAuraAbilitySystemLibrary::GetAbilityTags(const UGameplayAbility* GameplayAbility)
{
	return GameplayAbility->AbilityTags;
}

void UAuraAbilitySystemLibrary::GetAllActorsOfClassMatchingTag(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, const FGameplayTag GameplayTag, TArray<AActor*>& OutActors)
{
	//OutActors.Empty();

	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	// We do nothing if not class provided, rather than giving ALL actors!
	if (ActorClass && World)
	{
		bool bHasLoggedMissingInterface = false;
		for (TActorIterator<AActor> It(World, ActorClass); It; ++It)
		{
			AActor* Actor = *It;
			check(Actor != nullptr);
			if (IsValid(Actor))
			{
				const IGameplayTagAssetInterface* GameplayTagAssetInterface = Cast<IGameplayTagAssetInterface>(Actor);
				if (GameplayTagAssetInterface != nullptr)
				{
					FGameplayTagContainer OwnedGameplayTags;
					GameplayTagAssetInterface->GetOwnedGameplayTags(OwnedGameplayTags);

					if (OwnedGameplayTags.HasTag(GameplayTag))
					{
						OutActors.Add(Actor);
					}
				}
				else
				{
					if (!bHasLoggedMissingInterface)
					{
						UE_LOG(LogGameplayTags, Warning,
							TEXT("At least one actor (%s) of class %s does not implement IGameplTagAssetInterface.  Unable to find owned tags, so cannot determine if actor matches gameplay tag query.  Presuming it does not."),
							*Actor->GetName(), *ActorClass->GetName());
						bHasLoggedMissingInterface = true;
					}
				}
			}
		}
	}
}

void UAuraAbilitySystemLibrary::GetAllActorsWithTeamTag(const UObject* WorldContextObject, const FGameplayTag TeamTag, TArray<AAuraCharacterBase*>& OutActors)
{
	OutActors.Reset();
	
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	
	if (World)
	{
		for (TActorIterator<AActor> It(World, AAuraCharacterBase::StaticClass()); It; ++It)
		{
			AActor* Actor = *It;
			check(Actor != nullptr);
			if (IsValid(Actor))
			{
				AAuraCharacterBase* AuraCharacter = Cast<AAuraCharacterBase>(Actor);
				if (AuraCharacter != nullptr)
				{
					const FGameplayTag& TargetTeamTag = AuraCharacter->GetTeamTag_Implementation();

					if (TargetTeamTag == TeamTag)
					{
						OutActors.Add(AuraCharacter);
					}
				}
			}
		}
	}
}

FGameplayTagContainer UAuraAbilitySystemLibrary::GetActorTags(const AActor* InActor)
{
	const IGameplayTagAssetInterface* GameplayTagAssetInterface = Cast<IGameplayTagAssetInterface>(InActor);
	if (GameplayTagAssetInterface != nullptr)
	{
		FGameplayTagContainer OwnedGameplayTags;
		GameplayTagAssetInterface->GetOwnedGameplayTags(OwnedGameplayTags);
		return OwnedGameplayTags;
	}
	return FGameplayTagContainer::EmptyContainer;
}

//UBlueprintGameplayTagLibrary::GetAllActorsOfClassMatchingTagQuery
bool UAuraAbilitySystemLibrary::HasActorTag(const AActor* InActor, const FGameplayTag Tag, bool bExactMatch)
{
	const FGameplayTagContainer& ActorTags = GetActorTags(InActor);
	return bExactMatch ? ActorTags.HasTagExact(Tag) : ActorTags.HasTag(Tag);
}

FGameplayTag UAuraAbilitySystemLibrary::GetTeamTag(const AActor* InActor)
{
	if (InActor->Implements<UCombatInterface>())
	{
		return ICombatInterface::Execute_GetTeamTag(InActor);
	}
	return FGameplayTag::EmptyTag;
}

bool UAuraAbilitySystemLibrary::HasTeamTag(const AActor* InActor, const FGameplayTag& TeamTag)
{
	return GetTeamTag(InActor) == TeamTag;
}

bool UAuraAbilitySystemLibrary::IsTeamFriend(const AActor* FirstActor, const AActor* SecondActor)
{
	if (FirstActor->Implements<UCombatInterface>() && SecondActor->Implements<UCombatInterface>())
	{
		return ICombatInterface::Execute_GetTeamTag(FirstActor) == ICombatInterface::Execute_GetTeamTag(SecondActor);
	}
	return false;
}
