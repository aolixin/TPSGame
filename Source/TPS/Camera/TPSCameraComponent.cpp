// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCameraComponent.h"
#include "TPSCameraMode.h"
#include "TPS/Character/TPSCharacter.h"

void UTPSCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView)
{
	// UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *GetRelativeLocation().ToString());
	if (SrcCameraMode == nullptr)
	{
		InitCameraMode(DefaultCameraMode);
		Super::GetCameraView(DeltaTime, DesiredView);
		return;
	}
	if (DestCameraMode == nullptr)
	{
		Super::GetCameraView(DeltaTime, DesiredView);
		return;
	}
	if (SrcCameraMode == DestCameraMode)
	{
		DestCameraMode = nullptr;
		SwitchTime = 0;
		Super::GetCameraView(DeltaTime, DesiredView);
		return;
	}
	SwitchTime += DeltaTime * (float)dir;
	if (SwitchTime < 0)
	{
		SwitchTime = 0;
		ClearAdditiveOffset();
		AddAdditiveOffset(FTransform(SrcCameraMode->Location), 0);
		DestCameraMode = nullptr;
		Super::GetCameraView(DeltaTime, DesiredView);
		return;
	}
	else if (SwitchTime > SwitchDuration)
	{
		SwitchTime = SwitchDuration;
		ClearAdditiveOffset();
		AddAdditiveOffset(FTransform(DestCameraMode->Location), 0);
		Super::GetCameraView(DeltaTime, DesiredView);
		return;
	}

	FVector dis = DestCameraMode->Location - SrcCameraMode->Location;
	AddAdditiveOffset(FTransform(dis * DeltaTime / SwitchDuration * (float)dir), 0);

	Super::GetCameraView(DeltaTime, DesiredView);
}

void UTPSCameraComponent::InitCameraMode(TSubclassOf<UTPSCameraMode> CameraMode)
{
	SrcCameraMode = CameraMode.GetDefaultObject();
	DestCameraMode = nullptr;
	AddAdditiveOffset(FTransform(SrcCameraMode->Location), 0);
	SwitchTime = 0;
}

void UTPSCameraComponent::SetCameraMode(TSubclassOf<UTPSCameraMode> CameraMode)
{
	if (CameraMode == nullptr)return;
	DestCameraMode = CameraMode.GetDefaultObject();
	dir = 1;
}

void UTPSCameraComponent::ClearCameraMode()
{
	dir = -1;
}
