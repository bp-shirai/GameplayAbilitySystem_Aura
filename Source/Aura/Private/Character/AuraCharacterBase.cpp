// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Aura.h"
#include "AuraGameplayTags.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	//GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	//GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	// Another solution for firebolt missing hit on the dedicated server option.
	// GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = OwnedGameplayTags;
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

UAnimMontage* AAuraCharacterBase::GetHitReactMontage_Implementation() const
{
	return HitReactMontage;
}

void AAuraCharacterBase::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	Die_Multicast();
}

void AAuraCharacterBase::Die_Multicast_Implementation()
{
	bDead = true;

	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	if (GetMesh()->IsPlaying())GetMesh()->Stop();
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Dissolve();
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
}

TArray<FName> AAuraCharacterBase::GetSocketNames() const
{
	TArray<FName> SocketNames;
//#if WITH_EDITOR
	if (GetMesh() && GetMesh()->GetSkinnedAsset())
	{
		if (USkeleton* Skeletal = GetMesh()->GetSkinnedAsset()->GetSkeleton())
		{
			for (int32 BoneIdx = 0; BoneIdx < Skeletal->GetReferenceSkeleton().GetNum(); ++BoneIdx)
			{
				const FName BoneName = Skeletal->GetReferenceSkeleton().GetBoneName(BoneIdx);
				SocketNames.Add(BoneName);
			}
			for (USkeletalMeshSocket* Socket : Skeletal->Sockets)
			{
				SocketNames.Add(Socket->SocketName);
			}
		}
	}
//#endif
	return SocketNames;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AAuraCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& SocketTag)
{
	// TODO: Return correct socket based on MontageTag.
	//const FTaggedMontage& AttackMontage = GetAttackMontage(MontageTag);
	//if (AttackMontage.MontageTag == Montage_Attack_Weapon && IsValid(Weapon))
	if (SocketTag == CombatSocket_Weapon && IsValid(Weapon))
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	if (SocketTag == CombatSocket_LeftHand)
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (SocketTag == CombatSocket_RightHand)
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	if (SocketTag == CombatSocket_Tail)
	{
		return GetMesh()->GetSocketLocation(TailSocketName);
	}
	return GetActorLocation();
}

bool AAuraCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* AAuraCharacterBase::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage> AAuraCharacterBase::GetAttackMontages_Implementation() const
{
	return AttackMontages;
}
/*
const FTaggedMontage& AAuraCharacterBase::GetAttackMontage(const FGameplayTag& MontageTag) const
{
	for (const auto& AttackMontage : AttackMontages)
	{
		if (AttackMontage.MontageTag == MontageTag)
			return AttackMontage;
	}
	return AttackMontages[0];
}*/

UNiagaraSystem* AAuraCharacterBase::GetBloodEffect_Implementation() const
{
	return BloodEffect;
}

FTaggedMontage AAuraCharacterBase::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) const
{
	for (const auto& AttackMontage : AttackMontages)
	{
		if (AttackMontage.MontageTag == MontageTag)
		{
			return AttackMontage;
		}
	}
	return FTaggedMontage::Empty;
}

int32 AAuraCharacterBase::GetMinionCount_Implementation() const
{
	return MinionCount;
}

void AAuraCharacterBase::IncrementMinionCount_Implementation(int32 Amount)
{
	MinionCount += Amount;
}

FGameplayTag AAuraCharacterBase::GetTeamTag_Implementation() const
{
	return TeamTag;
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, float Level) const
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	check(IsValid(ASC));
	check(EffectClass);
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpec = ASC->MakeOutgoingSpec(EffectClass, Level, EffectContext);
	ASC->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data.Get(), ASC);
}



void AAuraCharacterBase::AddCharacterAbilities()
{
	if (HasAuthority())
	{
		UAuraAbilitySystemComponent* ASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystem);

		ASC->AddCharacterAbilities(StartupAbilities);

	}
}

void AAuraCharacterBase::Dissolve()
{
	if (IsValid(DissolveMaterial))
	{
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(DissolveMaterial, this);
		GetMesh()->SetMaterial(0, DynamicMaterial);
		StartDissolveTimeline(DynamicMaterial);
	}
	if (IsValid(WeaponDissolveMaterial))
	{
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(DissolveMaterial, this);
		Weapon->SetMaterial(0, DynamicMaterial);
		StartWeaponDissolveTimeline(DynamicMaterial);
	}
}




