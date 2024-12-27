// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ObjectMacros.h"
#include "Components/SceneComponent.h"
#include "TestSceneComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class UTestSceneComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SwitchTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SwitchDuration;
};
