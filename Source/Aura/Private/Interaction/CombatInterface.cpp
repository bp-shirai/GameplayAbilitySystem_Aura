// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/CombatInterface.h"
#include "AuraGameplayTags.h"

// Add default functionality here for any ICombatInterface functions that are not pure virtual.

const FTaggedMontage FTaggedMontage::Empty;

int32 ICombatInterface::GetPlayerLevel() const
{
	return 0;
}

//FVector ICombatInterface::GetCombatSocketLocation() const
//{
//	return FVector();
//}


/*
bool ICombatInterface::IsNotFriend(const AActor* InActor)
{
	if (auto Target = Cast<ICombatInterface>(InActor))
	{
		const FGameplayTag& MyTeam = GetTeamTag();
		const FGameplayTag& TargetTeam = Target->GetTeamTag();
		if (MyTeam == TargetTeam)
		{
			return false;
		}
	}
	return true;
}*/
