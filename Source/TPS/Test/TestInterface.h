// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TestInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UTestInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class TPS_API ITestInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION()
	virtual void TestFunc0() = 0;

	UFUNCTION()
	virtual void TestFunc1();
};
