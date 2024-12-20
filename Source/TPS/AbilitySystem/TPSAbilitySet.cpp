// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSAbilitySet.h"

#include "GameplayAbilitySpec.h"
#include "TPSAbilitySystemComponent.h"
#include "Abilities/TPSGameplayAbility.h"


void FTPSAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}
}


UTPSAbilitySet::UTPSAbilitySet(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

void UTPSAbilitySet::GiveToAbilitySystem(UTPSAbilitySystemComponent* ASC,
                                         FTPSAbilitySet_GrantedHandles* OutGrantedHandles,
                                         UObject* SourceObject) const
{
	check(ASC);
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
		const FTPSAbilitySet_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];

		if (!IsValid(AbilityToGrant.Ability))
		{
			UE_LOG(LogTemp, Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex,
			       *GetNameSafe(this));
			continue;
		}

		UTPSGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<UTPSGameplayAbility>();

		FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

		const FGameplayAbilitySpecHandle AbilitySpecHandle = ASC -> GiveAbility(AbilitySpec);

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		}
	}
}
