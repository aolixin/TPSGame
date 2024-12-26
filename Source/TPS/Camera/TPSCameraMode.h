// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TPSCameraMode.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable)
class TPS_API UTPSCameraMode : public UObject
{
	GENERATED_BODY()
public:
	UTPSCameraMode();
	
	FVector Location;
	
};
