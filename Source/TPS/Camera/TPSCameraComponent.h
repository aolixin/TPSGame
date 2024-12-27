// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPSCameraMode.h"
#include "Camera/CameraComponent.h"
#include "TPSCameraComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))

class TPS_API UTPSCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:
	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) override;

	void InitCameraMode(TSubclassOf<UTPSCameraMode> CameraMode);
	void SetCameraMode(TSubclassOf<UTPSCameraMode> CameraMode);
	void ClearCameraMode();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= CameraMode)
	TSubclassOf<UTPSCameraMode> DefaultCameraMode;

	UPROPERTY()
	TObjectPtr<UTPSCameraMode> SrcCameraMode;

	UPROPERTY()
	TObjectPtr<UTPSCameraMode> DestCameraMode;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= CameraMode)
	float SwitchTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= CameraMode)
	float SwitchDuration;
	
	UPROPERTY()
	int dir = 1;
};
