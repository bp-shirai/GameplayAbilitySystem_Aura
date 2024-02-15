// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"
//#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AuraGameplayTags.h"
//#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"

//#include "Components/SphereComponent.h"


/*
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());

}

void AAuraEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		auto AuraAttributeSet = Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));	
		auto MutableAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		MutableAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 20.f);

		Destroy();
	}
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);

}*/

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = OwnedGameplayTags;
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass)
{
	if (IsApplyActor(TargetActor) == false) return;

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(TargetASC)) return;

	FGameplayEffectContextHandle Context = TargetASC->MakeEffectContext();
	Context.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(EffectClass, ActorLevel, Context);
	const FGameplayEffectSpec* Spec = SpecHandle.Data.Get();
	//FGameplayTagContainer& CapturedSourceTags = Spec->CapturedSourceTags.GetSpecTags();
	//CapturedSourceTags.AppendTags(OwnedGameplayTags);

	const FActiveGameplayEffectHandle ActiveEffect = TargetASC->ApplyGameplayEffectSpecToSelf(*Spec);

	const bool bIsInfinite = Spec->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffect, TargetASC);
	}

	if (!bIsInfinite)
	{
		Destroy();
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (IsApplyActor(TargetActor) == false) return;

	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (IsApplyActor(TargetActor) == false) return;

	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteEffectClass);
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (IsValid(TargetASC))
		{
			/*
			FGameplayEffectQuery EffectQuery;
			EffectQuery.EffectSource = this;
			TArray<FActiveGameplayEffectHandle> ActiveEffects = TargetASC->GetActiveEffects(EffectQuery);
			for (FActiveGameplayEffectHandle EffectHandle : ActiveEffects)
			{
				TargetASC->RemoveActiveGameplayEffect(EffectHandle, 1);
			}*/

			/*
			TArray<FActiveGameplayEffectHandle> HandlesToRemove;
			for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
			{
				if (TargetASC == HandlePair.Value)
				{
					TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1); // stacks to remove
					HandlesToRemove.Add(HandlePair.Key);
				}
			}
			for (auto& Handle : HandlesToRemove)
			{
				ActiveEffectHandles.FindAndRemoveChecked(Handle);
			}
			*/


			for (auto HandlePair = ActiveEffectHandles.CreateIterator(); HandlePair; ++HandlePair)
			{
				if (TargetASC == HandlePair->Value)
				{
					TargetASC->RemoveActiveGameplayEffect(HandlePair->Key, 1);
					HandlePair.RemoveCurrent();
				}
			}

			//const FActiveGameplayEffectHandle* ActiveEffectHandle = ActiveEffectHandles.FindKey(TargetASC);
			//TargetASC->RemoveActiveGameplayEffect(*ActiveEffectHandle, 1);
			//ActiveEffectHandles.FindAndRemoveChecked(*ActiveEffectHandle);
		}
	}
}

bool AAuraEffectActor::IsApplyActor(const AActor* TargetActor) const
{
	if (!bApplyEffectsToEnemies && UAuraAbilitySystemLibrary::HasTeamTag(TargetActor, Team_Enemy)) return false;
	return true;
}


