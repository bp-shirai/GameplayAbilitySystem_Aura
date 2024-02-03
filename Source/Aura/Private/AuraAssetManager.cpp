// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "AbilitySystemGlobals.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	UAuraAssetManager* Singleton = Cast<UAuraAssetManager>(GEngine->AssetManager);

	if (Singleton)
	{
		return *Singleton;
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Cannot use AuraAssetManager if no AssetManagerClassName is defined!"));
		return *NewObject<UAuraAssetManager>(); // never calls this
	}
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	// This is required to use Target Data!
	// it is not necessary in 5.3.
	// UAbilitySystemGlobals::Get().InitGlobalData();
}
