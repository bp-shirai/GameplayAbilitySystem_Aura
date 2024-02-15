// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Aura.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Interaction/COMBATINTERFACE.H"

AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCanEverAffectNavigation(false);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = ProjectileMovement->InitialSpeed;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);

	//Sphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnSphereBeginOverlap);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereBeginOverlap);
	if (IsValid(GetInstigator()))
	{
		Sphere->IgnoreActorWhenMoving(GetInstigator(), true);
		UE_LOG(LogAura, Log, TEXT("%s::Instigator = %s"), *GetNameSafe(this), *GetNameSafe(GetInstigator()));
	}

	// Set the parameter bStopWhenAttachedToDestroyed = true
	if (LoopingSound)
		LoopingSoundAudio = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());

	/*
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer,
		FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Count=%d"), this->Count++));
			}),
		1.f, true);*/
}

void AAuraProjectile::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		PlayHitEffects();
		bHit = true;
	}
	Super::Destroyed();
}

void AAuraProjectile::LifeSpanExpired()
{
	if (IsValid(LoopingSoundAudio) && LoopingSoundAudio->IsPlaying())
		LoopingSoundAudio->Stop();
	Super::LifeSpanExpired();
}

void AAuraProjectile::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	FGameplayEffectSpec* EffectSpec = DamageEffectSpecHandle.Data.Get();
	AActor* EffectCauser = EffectSpec ? EffectSpec->GetContext().GetEffectCauser() : nullptr;

	if (EffectCauser == OtherActor || EffectSpec == nullptr || !IsValid(OtherActor))
	{
		return;
	}

	// Friendly Fire
	if (UAuraAbilitySystemLibrary::IsTeamFriend(OtherActor, EffectCauser))
	{
		return;
	}

	if (OtherActor->Implements<UCombatInterface>())
	{
		if (ICombatInterface::Execute_IsDead(OtherActor)) return;
	}

	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (!bHit)
	{
		PlayHitEffects();
		bHit = true;
	}

	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpec);
		}
		Destroy();
	}
}

void AAuraProjectile::PlayHitEffects()
{	
	if (IsValid(LoopingSoundAudio) && LoopingSoundAudio->IsPlaying())
		LoopingSoundAudio->Stop();
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
}


