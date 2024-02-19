// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AbilityInfo.h"
#include "Aura.h"

const FAuraAbilityInfo FAuraAbilityInfo::Empty;


const FAuraAbilityInfo& UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (const FAuraAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Can't find Info for AbilityTag[%s] on AbilityInfo [%s]."), *AbilityTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAbilityInfo::Empty;
}
