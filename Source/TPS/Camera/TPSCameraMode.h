// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TPSCameraMode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TPS_API UTPSCameraMode : public UObject
{
	GENERATED_BODY()
public:
	UTPSCameraMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;
	
};
