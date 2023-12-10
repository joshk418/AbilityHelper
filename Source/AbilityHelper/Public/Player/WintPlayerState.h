// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "WintPlayerState.generated.h"

class UWintPawnData;
class UAttributeSet;
class UAbilitySystemComponent;

/**
 * PlayerState that implements the IAbilitySystemInterface to give flexibility to the Player
 * to retain ability system information.
 */
UCLASS()
class ABILITYHELPER_API AWintPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, ReplicatedUsing=OnRep_PawnData)
	TObjectPtr<const UWintPawnData> PawnData;

protected:
	UFUNCTION()
	void OnRep_PawnData();

public:
	AWintPlayerState();

protected:
	virtual void BeginPlay() override;

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

	void InitPawnData();
	void SetPawnData(const UWintPawnData* InPawnData);
};
