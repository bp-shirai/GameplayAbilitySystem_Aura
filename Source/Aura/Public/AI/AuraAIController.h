// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AuraAIController.generated.h"


class UBlackboardComponent;
class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS(Abstract)
class AURA_API AAuraAIController : public AAIController
{
	GENERATED_BODY()

public:

	AAuraAIController();

	void InitializeBehaviorTree(const UBehaviorTree* InBehaviorTree);

protected:

	//UPROPERTY()
	//TObjectPtr<UBlackboardComponent> MyBlackboard;

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTree;

};
