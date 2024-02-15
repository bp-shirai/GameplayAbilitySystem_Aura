// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_FindNearestPlayer.h"

#include "AI/AuraAIController.h"
#include "Character/AuraCharacterBase.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "BehaviorTree/BTFunctionLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"

#include "Kismet/GameplayStatics.h"



UBTService_FindNearestPlayer::UBTService_FindNearestPlayer()
{
	//bNotifyTick = true;
	//bNotifyTaskFinished = true;
	//bCreateNodeInstance = false;

	NodeName = "Find Nearest Player";
	
	//DistanceToTargetSelector.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, DistanceToTargetSelector));
}

void UBTService_FindNearestPlayer::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (ensure(BBAsset))
	{
		TargetToFollowKey.ResolveSelectedKey(*BBAsset);
		DistanceToTargetKey.ResolveSelectedKey(*BBAsset);
	}
}

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//APawn* OwningPawn = AIOwner->GetPawn();
	AAuraCharacterBase* OwningPawn = Cast<AAuraCharacterBase>(AIOwner->GetPawn());
	if (IsValid(OwningPawn))
	{
		const bool IsPlayerTeam = OwningPawn->GetTeamTag_Implementation() == Team_Player;
		const FGameplayTag& TargetTeamTag = IsPlayerTeam ? Team_Enemy : Team_Player;

		TArray<AAuraCharacterBase*> ActorsWithTag;
		UAuraAbilitySystemLibrary::GetAllActorsWithTeamTag(OwningPawn, TargetTeamTag, ActorsWithTag);

		float ClosestDistance = TNumericLimits<float>::Max();
		AActor* ClosestActor = nullptr;
		const FVector Origin = OwningPawn->GetActorLocation();

		for (auto Actor : ActorsWithTag)
		{
			if (IsValid(Actor))
			{
				// Check Target Actor state
				if (Actor->IsDead_Implementation()) continue;
			
				const float Distance = (Origin - Actor->GetActorLocation()).SizeSquared();//const float Distance = OwningPawn->GetDistanceTo(Actor);
				if (Distance < ClosestDistance)
				{
					ClosestDistance = Distance;
					ClosestActor = Actor;
				}
			}
		}

		if (ClosestActor)
		{
			ClosestDistance = FMath::Sqrt(ClosestDistance);
		}

		//auto Blackboard = OwnerComp.GetBlackboardComponent();
		//Blackboard->GetOwner();
		//Blackboard->SetValue<UBlackboardKeyType_Float>(DistanceToTargetKey.GetSelectedKeyID(), ClosestDistance);

		UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetToFollowKey, ClosestActor);
		UBTFunctionLibrary::SetBlackboardValueAsFloat(this, DistanceToTargetKey, ClosestDistance);
	}
}

/*
AActor* NearestActor = nullptr;
float DistanceFromNearestActor = Distance = TNumericLimits<float>::Max();

for (AActor* ActorToCheck : ActorsToCheck)
{
	if (ActorToCheck)
	{
		const float DistanceFromActorToCheck = (Origin - ActorToCheck->GetActorLocation()).SizeSquared();
		if (DistanceFromActorToCheck < DistanceFromNearestActor)
		{
			NearestActor = ActorToCheck;
			DistanceFromNearestActor = DistanceFromActorToCheck;
		}
	}
}

if (NearestActor)
{
	Distance = FMath::Sqrt(DistanceFromNearestActor);
}
*/