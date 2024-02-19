// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/AuraUserWidget.h"
#include "AttributeSet.h"
#include "AttributeProgressBar.generated.h"


class UImage;
class USizeBox;
class UMaterialInterface;

/**
 * 
 */
UCLASS(Abstract)
class AURA_API UAttributeProgressBar : public UAuraUserWidget
{
	GENERATED_BODY()
public:


	virtual void SetWidgetController_Implementation(UObject* InWidgetController) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnAttributeChanged(float OldValue);

protected:

	void SetPercent(float Percent);
	void InitPercent(float Percent);
	void ChangeGauge(float Percent);
	void PlayAnim();
	void StopAnim();

	void SetBarPercent(float InValue, float InMaxValue, bool bInitSet = false);

	//virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	//virtual void NativeConstruct()override;
	virtual void NativeDestruct()override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime)override;


	UPROPERTY(EditDefaultsOnly)
	bool bCanHideProgressBar;

	bool bProgressBarVisible = true;

	UPROPERTY(Transient, meta = (BindWidgetOptional))
	TObjectPtr<USizeBox> RootBox;

	UPROPERTY(Transient, meta = (BindWidgetOptional))
	TObjectPtr<UImage> Background;

	UPROPERTY(Transient, meta = (BindWidgetOptional))
	TObjectPtr<UImage> GhostBar;

	UPROPERTY(Transient, meta = (BindWidgetOptional))
	TObjectPtr<UImage> ProgressBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)//Meta = (ExposeOnSpawn = true)
	FGameplayAttribute CurrentAttribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) //Meta = (ExposeOnSpawn = true)
	FGameplayAttribute MaxAttribute;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInterface> ProgressBarMaterial;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInterface> GhostBarMaterial;

	UPROPERTY()
	float CurrentPercent;

	UPROPERTY()
	float NewPercent;

	UPROPERTY()
	float MaxValue;

	UPROPERTY()
	float CurrentValue;

	UPROPERTY(EditDefaultsOnly)
	float InterpSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly)
	float WaitTime = 1.f;

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "bCanHideProgressBar"))
	float HideTime = 6.f;

	FDelegateHandle CurrentChangedHandle;
	FDelegateHandle MaxChangedHandle;
	FTimerHandle WaitTimerHandle;
	FTimerHandle HideTimerHandle;

	bool bIsAnimation;

	UPROPERTY(EditDefaultsOnly)
	float BoxWidth = 80.f;

	UPROPERTY(EditDefaultsOnly)
	float BoxHeight = 10.f;

//	UPROPERTY(EditDefaultsOnly)
//	bool bUseGhostBar = true;

	UPROPERTY(EditDefaultsOnly)
	bool bUseMaterialParameter;


	//UPROPERTY(Transient)
	//TObjectPtr<UMaterialInstanceDynamic> ProgressBarDynamicMaterial;
	//UPROPERTY(Transient)
	//TObjectPtr<UMaterialInstanceDynamic> GhostBarDynamicMaterial;

	void InitBarStyle(UImage* Image, UMaterialInterface* Material);

	void SetBarVisibility(bool bVisible);

	/*
	UFUNCTION()
	TArray<FString> GetNames() const
	{
		return { "", "One", "Two" ,"Three" ,"Four" };
	}

	UPROPERTY(EditAnywhere, meta = (GetOptions = "GetNames"))
	FName Names;
*/
};
