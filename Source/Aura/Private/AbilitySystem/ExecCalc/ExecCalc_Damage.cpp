// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Interaction/CombatInterface.h"
#include "AuraAbilityTypes.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Aura.h"

/*
 * Struct to hold our attributes we want to access
*/
struct FAuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration)
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageResistance)


	FAuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, DamageResistance, Target, false);
	}
};

//A static so we can use the above struct without needing to make a new instance for it.
static const FAuraDamageStatics& DamageStatics()
{
	static FAuraDamageStatics Statics;
	return Statics;
}


UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent(); // このエフェクトを作成した所有者のアビリティ システム コンポーネントを返します。
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent(); // この効果の影響を受ける所有者の能力システム コンポーネントを返します。

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec(); // この実行を実行しているエフェクトの所有スペックを返します。

	// Grab the tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	const ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	const ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);
	const int32 SourcePlayerLevel = SourceCombatInterface->GetPlayerLevel();
	const int32 TargetPlayerLevel = TargetCombatInterface->GetPlayerLevel();

	// Setup our evaluate params
	FAggregatorEvaluateParameters EvalParams;
	EvalParams.SourceTags = SourceTags;
	EvalParams.TargetTags = TargetTags;

	// Get Damage Set By Caller Magnitude
	float Damage = 0.f;		//float Damage = Spec.GetSetByCallerMagnitude(DamageType_All);
	for (auto& DamageType : Spec.GetDynamicAssetTags())
	{
		Damage += Spec.GetSetByCallerMagnitude(DamageType);
	}

	// Capture BlockChance on Target, and determine if there was a successful Block if Block, halve the damage.
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvalParams, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(0.f, TargetBlockChance);
	//UE_LOG(LogAura, Log, TEXT("TargetBlockChance = %f"), TargetBlockChance);

	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;

	
	float DamageResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageResistanceDef, EvalParams, DamageResistance);
	DamageResistance = FMath::Max<float>(0.f, DamageResistance);
	
	//UE_LOG(LogAura, Log, TEXT("Source DamageType.Fire = %s"), TEXT_BOOL(EvalParams.SourceTags->HasTag(DamageType_Fire)));
	//UE_LOG(LogAura, Log, TEXT("Target DamageType.Fire = %s"), TEXT_BOOL(EvalParams.TargetTags->HasTag(DamageType_Fire)));
	//UE_LOG(LogAura, Log, TEXT("Target DamageResistance = %f"), DamageResistance);

	Damage = FMath::Max<float>(0.f, Damage - DamageResistance);


	// If Block, halve the damage.
	Damage = bBlocked ? Damage / 2.f : Damage;


	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvalParams, TargetArmor);
	TargetArmor = FMath::Max<float>(0.f, TargetArmor);
	float SourceArmorPenetration = 0.f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvalParams, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(0.f, SourceArmorPenetration);

	// Get CurveTable
	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve("ArmorPenetration", FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourcePlayerLevel);

	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve("EffectiveArmor", FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetPlayerLevel);

	const FRealCurve* EffectiveCriticalHitResistanceCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve("CriticalHitResistance", FString());
	const float EffectiveCriHitResCoefficient = EffectiveCriticalHitResistanceCurve->Eval(TargetPlayerLevel);

	// ArmorPenetration ignores a percentage of the Target's Armor.
	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;
	// Armor ignores a percentage of incoming Damage.
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;


	float CriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvalParams, CriticalHitChance);
	CriticalHitChance = FMath::Max<float>(0.f, CriticalHitChance);
	
	float CriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, EvalParams, CriticalHitResistance);
	CriticalHitResistance = FMath::Max<float>(0.f, CriticalHitResistance);

	float CriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvalParams, CriticalHitDamage);
	CriticalHitDamage = FMath::Max<float>(0.f, CriticalHitDamage);

	// Critical Hit Resistance reduces Critical Hit Chance by a certain percentage
	const float EffectiveCriticalHitChance = CriticalHitChance - CriticalHitResistance * EffectiveCriHitResCoefficient;
	const bool bCriticalHit = FMath::RandRange(1, 100) < EffectiveCriticalHitChance;

	
	// Using a custom effect context.
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(Spec.GetContext().Get()))
	{
		AuraEffectContext->SetIsBlockedHit(bBlocked);//UAuraAbilitySystemLibrary::SetIsBlockedHit(Spec.GetContext(), bBlocked);
		AuraEffectContext->SetIsCriticalHit(bCriticalHit);
	}

	// Double damage plus a bonus if critical hit
	Damage = bCriticalHit ? 2.f * Damage + CriticalHitDamage : Damage;


	const FGameplayModifierEvaluatedData EvalData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvalData);

}
