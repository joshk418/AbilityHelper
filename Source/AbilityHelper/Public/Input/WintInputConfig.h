// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "WintInputConfig.generated.h"

/**
 * InputAction struct to hold a reference to an InputAction and a GameplayTag to use for input binding.
 */
USTRUCT(BlueprintType)
struct FWintInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * Configuration Asset to hold a list of InputActions and GameplayTags to use for input binding.
 */
UCLASS()
class ABILITYHELPER_API UWintInputConfig : public UDataAsset
{
	GENERATED_BODY()	

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FWintInputAction> AbilityInputActions;
	
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
};
