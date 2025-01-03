#include "ATPSPlayerState.h"

#include "AbilitySystemComponent.h"




ATPSPlayerState::ATPSPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// init ability system component
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UTPSAbilitySystemComponent>(
		this, TEXT("AbilitySystemComponent"));

	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}


void ATPSPlayerState::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	// AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());
}
