// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/VitalProgressBar.h"
#include "UI/WidgetController/AuraWidgetController.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/OverlaySlot.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

void UVitalProgressBar::SetPercent(float Percent)
{
	NewPercent = Percent;
	PlayAnim();
}

void UVitalProgressBar::InitPercent(float Percent)
{
	NewPercent = Percent;
	CurrentPercent = Percent;
	ChangeGauge(CurrentPercent);
}

void UVitalProgressBar::ChangeGauge(float Percent)
{
	if (ProgressBar) ProgressBar->SetRenderScale({ Percent, 1.f });
}

void UVitalProgressBar::PlayAnim()
{
	bIsAnimation = true;
}

void UVitalProgressBar::StopAnim()
{
	bIsAnimation = false;
}

void UVitalProgressBar::SetBarPercent(float InValue, float InMaxValue, bool bInitSet)
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


void UVitalProgressBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (RootBox)
	{
		RootBox->SetWidthOverride(BoxWidth);
		RootBox->SetHeightOverride(BoxHeight);
	}

	if (ProgressBar) InitBarStyle(ProgressBar);
	if (GhostBar) InitBarStyle(GhostBar);
	if (Background) InitBarStyle(Background);

	// TODO: Set Bar Style
}

void UVitalProgressBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void UVitalProgressBar::NativeDestruct()
{
	auto ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Cast<AActor>(WidgetController));

	ASC->AbilityCommittedCallbacks.AddLambda([this](UGameplayAbility* Ability) 
	{
			//OnAbilityCommited(Ability);
			// BP Func :  CooldownDurarion = CooldownLeft Ability->GetCooldownTimeRemainnig()
	});

	if (IsValid(ASC))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(CurrentAttribute).Remove(CurrentChangedHandle);
		ASC->GetGameplayAttributeValueChangeDelegate(MaxAttribute).Remove(MaxChangedHandle);
	}
	Super::NativeDestruct();
}

void UVitalProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsAnimation)
	{
		float Speed = AnimSpeed * InDeltaTime;

		CurrentPercent += (NewPercent - CurrentPercent) * Speed;

		if (FMath::IsNearlyEqual(CurrentPercent, NewPercent, 0.001f))
		{
			CurrentPercent = NewPercent;
			ChangeGauge(CurrentPercent);
			StopAnim();
		}
		else
		{
			ChangeGauge(CurrentPercent);
			PlayAnim();
		}
	}
}



void UVitalProgressBar::SetWidgetController_Implementation(UObject* InWidgetController)
{
	Super::SetWidgetController_Implementation(InWidgetController);

	auto ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Cast<AActor>(WidgetController));
	if (!IsValid(ASC)) return;

	if (CurrentChangedHandle.IsValid() || MaxChangedHandle.IsValid()) return;
	
	CurrentChangedHandle= ASC->GetGameplayAttributeValueChangeDelegate(CurrentAttribute).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			CurrentValue = Data.NewValue;
			SetBarPercent(CurrentValue, MaxValue);
			OnChangedAttribute(Data.OldValue);
		});

	MaxChangedHandle= ASC->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			MaxValue = Data.NewValue;
			SetBarPercent(CurrentValue, MaxValue);
		});

	CurrentValue = ASC->GetNumericAttribute(CurrentAttribute);
	MaxValue = ASC->GetNumericAttribute(MaxAttribute);
	SetBarPercent(CurrentValue, MaxValue, true);

	OnChangedAttribute(CurrentValue);
}



void UVitalProgressBar::InitBarStyle(UImage* Image)
{
	if (UWidgetLayoutLibrary::SlotAsOverlaySlot(Image))
	{
		UWidgetLayoutLibrary::SlotAsOverlaySlot(Image)->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		UWidgetLayoutLibrary::SlotAsOverlaySlot(Image)->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	}
	Image->SetRenderTransformPivot({ 0.f, 0.5f });
}
