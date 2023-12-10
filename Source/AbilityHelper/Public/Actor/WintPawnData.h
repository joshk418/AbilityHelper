// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WintPawnData.generated.h"

class UWintAbilitySet;
class UWintInputConfig;
/**
 * PawnData for granting effects, abilities, and attributes to a pawn.
 */
UCLASS(BlueprintType, Const, meta=(DisplayName="Pawn Data"))
class ABILITYHELPER_API UWintPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystem|Input")
	TObjectPtr<UWintInputConfig> InputConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystem|Abilities")
	TArray<TObjectPtr<UWintAbilitySet>> AbilitySets;
};
