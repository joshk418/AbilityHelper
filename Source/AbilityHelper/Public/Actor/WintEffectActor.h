// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WintEffectActor.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;

UENUM(Blueprinttype)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(Blueprinttype)
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

/**
 * Struct for storing effect class and removal/application policies.
 */
USTRUCT(BlueprintType)
struct FGameplayEffectPolicy
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TSubclassOf<UGameplayEffect> EffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	EEffectApplicationPolicy ApplicationPolicy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	EEffectRemovalPolicy RemovalPolicy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	bool bDestroyOnApplication;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	bool bDestroyOnRemoval;
};

/**
 * Struct for storing effect class and ability system component.
 */
USTRUCT(BlueprintType)
struct FAbilitySystemEffectClassData
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TSubclassOf<UGameplayEffect> EffectClass;
};

/**
 * Class for applying effects to actors based on policies.
 */
UCLASS()
class ABILITYHELPER_API AWintEffectActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TArray<FGameplayEffectPolicy> Effects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
	TMap<FActiveGameplayEffectHandle, FAbilitySystemEffectClassData> ActiveInfiniteEffects;

public:
	AWintEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor *TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor *TargetActor);

	UFUNCTION(BlueprintCallable)
	bool ApplyEffectToTarget(AActor *TargetActor, TSubclassOf<UGameplayEffect> EffectClass);
};
