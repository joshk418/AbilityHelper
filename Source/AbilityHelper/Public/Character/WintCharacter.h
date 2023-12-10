// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Actor/WintPawnData.h"
#include "WintCharacter.generated.h"

class UWintPawnData;
struct FWintAbilitySet_GameplayAbility;
class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

/**
 * Base character that implements the IAbilitySystemInterface to give flexibility to the player and AI.
 *\n\n
 * AWintPlayerState is recommended to be used for the player's ability system component and attribute set.
 */
UCLASS()
class ABILITYHELPER_API AWintCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, ReplicatedUsing=OnRep_PawnData)
	TObjectPtr<const UWintPawnData> PawnData;

public:
	AWintCharacter();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRep_PawnData();
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual UAbilitySystemComponent *GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	};

	template<class T>
	const T* GetPawnData() const
	{
		return Cast<T>(PawnData);
	}

	void SetPawnData(const UWintPawnData* InPawnData);
};
