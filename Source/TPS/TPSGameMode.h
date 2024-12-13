// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/TPSPawnData.h"
#include "GameFramework/GameModeBase.h"
#include "TPSGameMode.generated.h"

UCLASS(minimalapi)
class ATPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATPSGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// UFUNCTION(BlueprintCallable, Category = "Pawn")
	// const UTPSPawnData* GetPawnDataForController(const AController* InController) const;
	//
	// virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
};



