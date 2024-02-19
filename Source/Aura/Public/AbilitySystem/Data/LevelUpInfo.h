// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"


USTRUCT(BlueprintType)
struct FAuraLevelInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 LevelUpRequirement = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 AttributePointAward = 1;

	UPROPERTY(EditDefaultsOnly)
	int32 SpellPointAward = 1;
};


/**
 * 
 */
UCLASS()
class AURA_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	TArray<FAuraLevelInfo> LevelUpInformation;

	int32 FindLevelForXP(int32 XP) const;


	UFUNCTION(CallInEditor, Category = "Edit")
	void CreateData();

	UPROPERTY(EditDefaultsOnly, Category = "Edit")
	int32 MaxLevel = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Edit")
	int32 FirstXP = 50;

	UPROPERTY(EditDefaultsOnly, Category = "Edit")
	int32 FirstPoint = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Edit")
	float XPScaleFactor = 2.f;

	UPROPERTY(EditDefaultsOnly, Category = "Edit")
	float PointAwardFactor = 1.5f;
};
