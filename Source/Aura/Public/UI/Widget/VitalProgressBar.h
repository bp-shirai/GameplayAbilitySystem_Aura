// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/AuraUserWidget.h"
#include "AttributeSet.h"
#include "VitalProgressBar.generated.h"

class UImage;
class USizeBox;
/**
 * 
 */
UCLASS(Abstract)
class AURA_API UVitalProgressBar : public UAuraUserWidget
{
	GENERATED_BODY()
	
public:


	virtual void SetWidgetController_Implementation(UObject* InWidgetController) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnChangedAttribute(float OldValue);

protected:

	void SetPercent(float Percent);
	void InitPercent(float Percent);
	void ChangeGauge(float Value);
	void PlayAnim();
	void StopAnim();

	void SetBarPercent(float InValue, float InMaxValue, bool bInitSet=false);

	//virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct()override;
	virtual void NativeDestruct()override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime)override;



	UPROPERTY(EditDefaultsOnly)
	bool bCanHideBar;

	bool bProgressBarVisible;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<USizeBox> RootBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> Background;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> GhostBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> ProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ExposeOnSpawn = true))
	FGameplayAttribute CurrentAttribute;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ExposeOnSpawn = true))
	FGameplayAttribute MaxAttribute;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentPercent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float NewPercent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MaxValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AnimSpeed = 1.f;

	FDelegateHandle CurrentChangedHandle;
	FDelegateHandle MaxChangedHandle;


	bool bIsAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BoxWidth = 80.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BoxHeight = 10.f;

	void InitBarStyle(UImage* Image);
};
