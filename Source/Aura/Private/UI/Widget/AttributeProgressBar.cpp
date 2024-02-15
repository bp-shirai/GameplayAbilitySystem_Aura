// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/AttributeProgressBar.h"

#include "UI/WidgetController/AuraWidgetController.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/OverlaySlot.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"



void UAttributeProgressBar::PlayAnim()
{
	bIsAnimation = true;
}

void UAttributeProgressBar::StopAnim()
{
	bIsAnimation = false;
}

void UAttributeProgressBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (RootBox)
	{
		RootBox->SetWidthOverride(BoxWidth);
		RootBox->SetHeightOverride(BoxHeight);
	}
	// TODO: Set Bar Style
	if (ProgressBar)InitBarStyle(ProgressBar, ProgressBarMaterial);
	if (GhostBar) InitBarStyle(GhostBar, GhostBarMaterial);
	if (Background) InitBarStyle(Background, nullptr);
}

void UAttributeProgressBar::NativeDestruct()
{
	auto ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Cast<AActor>(WidgetController));
	if (IsValid(ASC))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(CurrentAttribute).Remove(CurrentChangedHandle);
		ASC->GetGameplayAttributeValueChangeDelegate(MaxAttribute).Remove(MaxChangedHandle);
	}
	Super::NativeDestruct();
}

void UAttributeProgressBar::SetPercent(float Percent)
{
	NewPercent = Percent;
	if (ProgressBar) ProgressBar->SetRenderScale({ NewPercent, 1.f });

	// Using Delay
	if (auto World = GetWorld())
	{
		StopAnim();
		World->GetTimerManager().ClearTimer(WaitTimerHandle);
		World->GetTimerManager().SetTimer(WaitTimerHandle, [this]() { PlayAnim(); }, WaitTime, false);
		if (bCanHideProgressBar) {
			World->GetTimerManager().ClearTimer(HideTimerHandle);
			World->GetTimerManager().SetTimer(HideTimerHandle, [this]() { SetBarVisibility(false); }, HideTime, false);
		}
	}

	SetBarVisibility(true);
}

void UAttributeProgressBar::InitPercent(float Percent)
{
	NewPercent = Percent;
	if (ProgressBar) ProgressBar->SetRenderScale({ NewPercent, 1.f });
	CurrentPercent = Percent;
	ChangeGauge(CurrentPercent);

	SetBarVisibility(false);
}

void UAttributeProgressBar::ChangeGauge(float Percent)
{
	if (GhostBar) GhostBar->SetRenderScale({ Percent, 1.f });
}

void UAttributeProgressBar::SetBarPercent(float InValue, float InMaxValue, bool bInitSet)
{
	float Percent = UKismetMathLibrary::SafeDivide(InValue, InMaxValue);

	if (!bInitSet)
	{
		SetPercent(Percent);
	}
	else
	{
		InitPercent(Percent);
	}
}

void UAttributeProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (bIsAnimation)
	{
		Super::NativeTick(MyGeometry, InDeltaTime); // remove call pos

		//float Speed = AnimSpeed * InDeltaTime;
		//CurrentPercent += (NewPercent - CurrentPercent) * Speed;
		CurrentPercent = FMath::FInterpTo(CurrentPercent, NewPercent, InDeltaTime, InterpSpeed);

		if (FMath::IsNearlyEqual(CurrentPercent, NewPercent, 0.00001f))
		{
			CurrentPercent = NewPercent;
			ChangeGauge(CurrentPercent);
			StopAnim();
			if (CurrentPercent == 0.f)
			{
				SetBarVisibility(false);
			}
		}
		else
		{
			ChangeGauge(CurrentPercent);
			PlayAnim();
		}
	}
}



void UAttributeProgressBar::SetWidgetController_Implementation(UObject* InWidgetController)
{
	Super::SetWidgetController_Implementation(InWidgetController);

	auto ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Cast<AActor>(WidgetController));
	if (!IsValid(ASC)) return;

	if (CurrentChangedHandle.IsValid() || MaxChangedHandle.IsValid()) return;

	CurrentChangedHandle = ASC->GetGameplayAttributeValueChangeDelegate(CurrentAttribute).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			CurrentValue = Data.NewValue;
			SetBarPercent(CurrentValue, MaxValue);
			//OnChangedAttribute(Data.OldValue);
		});

	MaxChangedHandle = ASC->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			MaxValue = Data.NewValue;
			SetBarPercent(CurrentValue, MaxValue);
		});

	CurrentValue = ASC->GetNumericAttribute(CurrentAttribute);
	MaxValue = ASC->GetNumericAttribute(MaxAttribute);

	SetBarPercent(CurrentValue, MaxValue, true);

	//OnChangedAttribute(CurrentValue);
}



void UAttributeProgressBar::InitBarStyle(UImage* Image, UMaterialInterface* Material)
{
	if (Image)
	{
		Image->SetRenderTransformPivot({ 0.f, 0.5f });
		if (Material) Image->SetBrushFromMaterial(Material);
	}

	if (auto OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(Image))
	{
		OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	}
}

void UAttributeProgressBar::SetBarVisibility(bool bVisible)
{
	if (bCanHideProgressBar && bProgressBarVisible != bVisible)
	{
		bProgressBarVisible = bVisible;
		SetVisibility(bProgressBarVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}
