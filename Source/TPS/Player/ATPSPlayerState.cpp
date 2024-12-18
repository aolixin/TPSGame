
#include "ATPSPlayerState.h"

#include "AbilitySystemComponent.h"


//
// void ATPSPlayerState::SetPawnData(const UTPSPawnData* InPawnData)
// {
// 	check(InPawnData);
//
// 	if (PawnData)
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("Trying to set PawnData [%s] on player state [%s] that already has valid PawnData [%s]."), *GetNameSafe(InPawnData), *GetNameSafe(this), *GetNameSafe(PawnData));
// 		return;
// 	}
// 	PawnData = InPawnData;
//
// 	
// }
//
// void ATPSPlayerState::PostInitializeComponents()
// {
// 	Super::PostInitializeComponents();
//
// 	UWorld* World = GetWorld();
// 	if (World && World->IsGameWorld() && World->GetNetMode() != NM_Client)
// 	{
// 		AGameStateBase* GameState = GetWorld()->GetGameState();
// 		check(GameState);
//
// 		if (ATPSGameMode* TPSGameMode = GetWorld()->GetAuthGameMode<ATPSGameMode>())
// 		if (const UTPSPawnData* NewPawnData = TPSGameMode->GetPawnDataForController(GetOwningController()))
// 		{
// 			SetPawnData(NewPawnData);
// 		}
// 		else
// 		{
// 			UE_LOG(LogTemp, Error, TEXT("ALyraPlayerState::OnExperienceLoaded(): Unable to find PawnData to initialize player state [%s]!"), *GetNameSafe(this));
// 		}
// 	}
// }

ATPSPlayerState::ATPSPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// init ability system component
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}


void ATPSPlayerState::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	// AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());
}
