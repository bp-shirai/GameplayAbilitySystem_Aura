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

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{	
	AActor* OwnerActor = GetOwningActorFromActorInfo();
	APawn* AvatarActor = Cast<APawn>(GetAvatarActorFromActorInfo());
	
	if (AvatarActor && AvatarActor->HasAuthority())
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(AvatarActor))
		{
			//TODO: Set the projectile rotation.

			const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
			FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
			Rotation.Pitch = 0.f;

			FTransform SpawnTransform;
			SpawnTransform.SetLocation(SocketLocation);
			SpawnTransform.SetRotation(Rotation.Quaternion());

			//Cast<APawn>(OwnerActor)
			AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, OwnerActor, AvatarActor, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			//TODO: Give the projectile a GameplayEffectSpec for causing damage.

			const UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo();
			const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
			
			// Assign DamageTag
			const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel() + 10);

			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Effect_Damage, ScaledDamage);
			
			Projectile->DamageEffectSpecHandle = SpecHandle;

			Projectile->FinishSpawning(SpawnTransform);
		}
	}
}
