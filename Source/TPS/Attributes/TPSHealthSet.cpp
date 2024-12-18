// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSHealthSet.h"

#include "Net/UnrealNetwork.h"

UTPSHealthSet::UTPSHealthSet():Super(),Health(100.0f),MaxHealth(100.0f)
{
}

void UTPSHealthSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UTPSHealthSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTPSHealthSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UTPSHealthSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTPSHealthSet, Health, OldValue);
}

void UTPSHealthSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTPSHealthSet, MaxHealth, OldValue);
}