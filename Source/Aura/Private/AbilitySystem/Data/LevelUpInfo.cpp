// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP) const
{
	int32 Level = 1;
	bool bSearching = true;

	while (bSearching)
	{
		if (LevelUpInformation.Num() - 1 <= Level) return Level;

		if (XP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}


	return Level;
}

void ULevelUpInfo::CreateData()
{
	LevelUpInformation.Reset();

	for (int32 Level = 1; Level <= MaxLevel; Level++)
	{
		FAuraLevelInfo Info;
		Info.LevelUpRequirement = FirstXP * Level;
		Info.AttributePointAward = FirstPoint * Level;
		Info.SpellPointAward = FirstPoint * Level;
		LevelUpInformation.Add(Info);
	}
}
