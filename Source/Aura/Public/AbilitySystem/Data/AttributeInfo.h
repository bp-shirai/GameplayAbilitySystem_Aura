// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeSet.h"
#include "AttributeInfo.generated.h"



USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	//UPROPERTY(BlueprintReadOnly)
	//float AttributeValue = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttribute AttributeGetter;
};


/**
 * 
 */
UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	const FAuraAttributeInfo& FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = true) const;

	const FAuraAttributeInfo* FindAttributeInfo(const FGameplayTag& AttributeTag) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "{AttributeTag}"))
	TArray<FAuraAttributeInfo> AttributeInformation;


	UPROPERTY(EditDefaultsOnly, meta = (ForceInlineRow))
	TMap<FGameplayTag, FAuraAttributeInfo> AttributeInfoMap;

private:

};
