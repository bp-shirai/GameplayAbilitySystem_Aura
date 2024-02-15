// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"


TArray<FVector> UAuraSummonAbility::GetSpawnLocations(bool bDrawDebug)
{
	AActor* Avatar = GetAvatarActorFromActorInfo();
	const FVector Forward = Avatar->GetActorForwardVector();
	const FVector Location = Avatar->GetActorLocation();
	const float DeltaSpread = SpawnSpread / FMath::Max(1.f ,NumMinions - 1);

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);
	const FVector RightOfSpread = Forward.RotateAngleAxis(SpawnSpread / 2.f, FVector::UpVector);

	//UKismetSystemLibrary::DrawDebugArrow(Avatar, Location + LeftOfSpread * MinSpawnDistance, Location + LeftOfSpread * MaxSpawnDistance, 4.f, FLinearColor::Green, 3.f, 2.f);
	//UKismetSystemLibrary::DrawDebugArrow(Avatar, Location + RightOfSpread * MinSpawnDistance, Location + RightOfSpread * MaxSpawnDistance, 4.f, FLinearColor::Green, 3.f, 2.f);

	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult Hit;
		const FVector TraceLength(0.f, 0.f, 400.f);
		GetWorld()->LineTraceSingleByChannel(Hit, ChosenSpawnLocation + TraceLength, ChosenSpawnLocation - TraceLength, ECC_Visibility);
		if (Hit.bBlockingHit)
		{
			ChosenSpawnLocation = Hit.ImpactPoint;
		}
		SpawnLocations.Add(ChosenSpawnLocation);	
		
		if (bDrawDebug)
		{
			UKismetSystemLibrary::DrawDebugArrow(Avatar, Location + Direction * MinSpawnDistance, Location + Direction * MaxSpawnDistance, 4.f, FLinearColor::Green, 3.f, 3.f);
			DrawDebugSphere(GetWorld(), ChosenSpawnLocation, 18.f, 12.f, FColor::Cyan, false, 3.f);
		}
	}
	return SpawnLocations;
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomMinionClass() const
{
	int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);
	return MinionClasses[Selection];
}
