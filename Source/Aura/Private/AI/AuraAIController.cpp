// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AuraAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"


AAuraAIController::AAuraAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
	check(Blackboard);
	BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTree");
	check(BehaviorTree);
}

void AAuraAIController::InitializeBehaviorTree(const UBehaviorTree* InBehaviorTree)
{
	Blackboard->InitializeBlackboard(*InBehaviorTree->BlackboardAsset);

}
