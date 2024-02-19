// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AttributeInfo.h"
#include "Aura.h"

static const FAuraAttributeInfo EmptyInfo;

const FAuraAttributeInfo& UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{

	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}
	return EmptyInfo;
}

const FAuraAttributeInfo* UAttributeInfo::FindAttributeInfo(const FGameplayTag& AttributeTag) const
{
	const FAuraAttributeInfo* Info = AttributeInfoMap.Find(AttributeTag);
	if (Info == nullptr)
	{
		UE_LOG(LogAura, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfoMap [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}
	return Info;
}
