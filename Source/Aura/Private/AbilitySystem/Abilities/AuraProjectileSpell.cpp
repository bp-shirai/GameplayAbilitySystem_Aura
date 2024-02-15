// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"


void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

//	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Activate Ability (C++) [%s]"), *GetNameSafe(this)));



}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride)
{	
	AActor* OwnerActor = GetOwningActorFromActorInfo();
	APawn* AvatarActor = Cast<APawn>(GetAvatarActorFromActorInfo());
	//ICombatInterface* CombatInterface = Cast<ICombatInterface>(AvatarActor);

	if (AvatarActor && AvatarActor->HasAuthority()&& AvatarActor->Implements<UCombatInterface>())
	{
		//TODO: Set the projectile rotation.
		const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(AvatarActor, SocketTag);
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		if (bOverridePitch)
		{
			Rotation.Pitch = PitchOverride;
		}

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
	

		//Cast<APawn>(OwnerActor)
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, OwnerActor, AvatarActor, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//TODO: Give the projectile a GameplayEffectSpec for causing damage.

		const UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo();
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());


		//	const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());
		//	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Effect_Damage, ScaledDamage);

		for (auto& Pair : DamageTypes)
		{
			// Assign DamageType DataTag
			const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());// CT_Damage
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
			// Add DamageType AssetTag
			UAbilitySystemBlueprintLibrary::AddAssetTag(SpecHandle, Pair.Key);
		}

		Projectile->DamageEffectSpecHandle = SpecHandle;

		Projectile->FinishSpawning(SpawnTransform);

		//	}
	}
}
