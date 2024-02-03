// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerController.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController) // call from server
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AAuraCharacter::OnRep_PlayerState() // call from client
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the client
	InitAbilityActorInfo();
}

int32 AAuraCharacter::GetPlayerLevel() const
{
	const AAuraPlayerState* PS = GetPlayerStateChecked<AAuraPlayerState>();
	return PS->GetPlayerLevel();
}

void AAuraCharacter::InitializeDefaultAttributes() const
{	
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AAuraCharacter::InitAbilityActorInfo()
{	
	AAuraPlayerState* PS = GetPlayerStateChecked<AAuraPlayerState>(); // check(AuraPlayerState)

	UAuraAbilitySystemComponent* ASC = CastChecked<UAuraAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	ASC->AbilityActorInfoSet();
	ASC->InitAbilityActorInfo(PS, this);

	AbilitySystem = ASC;
	AttributeSet = PS->GetAttributeSet();

	InitializeDefaultAttributes();

	if (AAuraPlayerController* PC = GetController<AAuraPlayerController>())
	{
		if (AAuraHUD* HUD = PC->GetHUD<AAuraHUD>())
		{
			HUD->InitOverlay();// PC, PS, AbilitySystem, AttributeSet);
		}
	}
}
