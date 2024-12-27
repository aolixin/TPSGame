// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameplayAbility.h"

#include "Camera/CameraComponent.h"
#include "TPS/Character/TPSCharacter.h"

UTPSGameplayAbility::UTPSGameplayAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// ActivationPolicy = ETPSAbilityActivationPolicy::OnInputTriggered;
}


void UTPSGameplayAbility::SetCameraMode(TSubclassOf<UTPSCameraMode> CameraMode)
{
	TObjectPtr<ATPSCharacter> character = Cast<ATPSCharacter>(CurrentActorInfo->AvatarActor.Get());
	if (character == nullptr)return;
	TObjectPtr<UTPSCameraComponent> CameraComponent = character->FindComponentByClass<UTPSCameraComponent>();
	if (CameraComponent == nullptr)return;
	CameraComponent->SetCameraMode(CameraMode);
	UE_LOG(LogTemp, Log, TEXT("---------------------------------------"));
	
}

void UTPSGameplayAbility::ClearCameraMode()
{
	TObjectPtr<ATPSCharacter> character = Cast<ATPSCharacter>(CurrentActorInfo->AvatarActor.Get());
	if (character == nullptr)return;
	TObjectPtr<UTPSCameraComponent> CameraComponent = character->FindComponentByClass<UTPSCameraComponent>();
	if (CameraComponent == nullptr)return;
	CameraComponent->ClearCameraMode();
	
}