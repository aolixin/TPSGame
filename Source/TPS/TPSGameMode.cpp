// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPSGameMode.h"
#include "Character/TPSCharacter.h"
#include "Character/TPSPawnData.h"
#include "Player/ATPSPlayerState.h"
#include "UObject/ConstructorHelpers.h"

ATPSGameMode::ATPSGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UE_LOG(LogTemp,Warning,TEXT("ATPSGameMode() ObjectInitializer Call"));
	DefaultPawnClass = ATPSCharacter::StaticClass();
	PlayerStateClass = ATPSPlayerState::StaticClass();
}

// const UTPSPawnData* ATPSGameMode::GetPawnDataForController(const AController* InController) const
// {
// 	if (InController != nullptr)
// 	{
// 		if (const ATPSPlayerState* LyraPS = InController->GetPlayerState<ATPSPlayerState>())
// 		{
// 			if (const UTPSPawnData* PawnData = LyraPS->GetPawnData<UTPSPawnData>())
// 			{
// 				return PawnData;
// 			}
// 		}
// 	}
// 	return nullptr;
// }
//
// UClass* ATPSGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
// {
// 	if (const UTPSPawnData* PawnData = GetPawnDataForController(InController))
// 	{
// 		if (PawnData->PawnClass)
// 		{
// 			return PawnData->PawnClass;
// 		}
// 	}
//
// 	return Super::GetDefaultPawnClassForController_Implementation(InController);
// }
