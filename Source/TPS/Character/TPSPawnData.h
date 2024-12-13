// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TPSPawnData.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UTPSPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UTPSPawnData(const FObjectInitializer& ObjectInitializer);
	
	// Class to instantiate for this pawn (should usually derive from ALyraPawn or ALyraCharacter).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	TSubclassOf<APawn> PawnClass;
};
