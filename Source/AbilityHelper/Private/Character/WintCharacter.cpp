// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\WintCharacter.h"

#include "Net/UnrealNetwork.h"

AWintCharacter::AWintCharacter()
{

}

void AWintCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWintCharacter::OnRep_PawnData()
{
	
}

void AWintCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWintCharacter, PawnData);
}

void AWintCharacter::SetPawnData(const UWintPawnData* InPawnData)
{
	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	if (PawnData)
	{
		UE_LOG(LogTemp, Error, TEXT("Trying to set PawnData [%s] on character [%s] that already has valid PawnData [%s]."), *GetNameSafe(InPawnData), *GetNameSafe(this), *GetNameSafe(PawnData));
		return;
	}

	PawnData = InPawnData;

	ForceNetUpdate();
}

