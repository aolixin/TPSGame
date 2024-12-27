// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCameraComponent.h"
#include "TPSCameraMode.h"
#include "TPS/Character/TPSCharacter.h"

void UTPSCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView)
{
	if (SrcCameraMode == nullptr)
	{
		InitCameraMode(DefaultCameraMode);
		Super::GetCameraView(DeltaTime, DesiredView);
		return;
	}
	if (DestCameraMode == nullptr)
	{
		DesiredView.Location = SrcCameraMode->Location;
		Super::GetCameraView(DeltaTime, DesiredView);
		return;
	}
	if (SrcCameraMode == DestCameraMode)
	{
		DestCameraMode = nullptr;
		Super::GetCameraView(DeltaTime, DesiredView);
		return;
	}
	SwitchTime += DeltaTime;
	if (SwitchTime >= SwitchDuration)
	{
		SrcCameraMode = DestCameraMode;
		DesiredView.Location = SrcCameraMode->Location;
		DestCameraMode = nullptr;
		SwitchTime = 0;
	}
	else
	{
		float Alpha = SwitchTime / SwitchDuration;
		DesiredView.Location = FMath::Lerp(SrcCameraMode->Location, DestCameraMode->Location, Alpha);
	}
	Super::GetCameraView(DeltaTime, DesiredView);
}

void UTPSCameraComponent::InitCameraMode(TSubclassOf<UTPSCameraMode> CameraMode)
{
	SrcCameraMode = CameraMode.GetDefaultObject();
	DestCameraMode = nullptr;
	SwitchTime = 0;
}

void UTPSCameraComponent::SetCameraMode(TSubclassOf<UTPSCameraMode> CameraMode)
{
	if (CameraMode == nullptr)return;
	DestCameraMode = CameraMode.GetDefaultObject();
	SwitchTime = 0;
}

void UTPSCameraComponent::ClearCameraMode()
{
	DestCameraMode = nullptr;
	SwitchTime = 0;
}