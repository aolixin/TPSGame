// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TPS/Camera/TPSCameraMode.h"
// #include "TPS/Character/TPSCharacter.h"
#include "TPSGameplayAbility.generated.h"

class ATPSCharacter;


UENUM(BlueprintType)
enum class ETPSAbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,

	// Continually try to activate the ability while the input is active.
	WhileInputActive,

	// Try to activate the ability when an avatar is assigned.
	OnSpawn
};

UCLASS()
class TPS_API UTPSGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UTPSGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	ETPSAbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }

protected:
	// Defines how this ability is meant to activate.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Activation")
	ETPSAbilityActivationPolicy ActivationPolicy;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void SetCameraMode(TSubclassOf<UTPSCameraMode> CameraMode);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void ClearCameraMode();

	UFUNCTION(BlueprintCallable, Category = "Ability")
	USkeletalMeshComponent* GetOwnerSkeletalMeshComponent();

	UFUNCTION(BlueprintCallable)
	void StartWeaponTargeting();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnRangedWeaponTargetDataReady(const FGameplayAbilityTargetDataHandle& TargetData);
	
	UFUNCTION(BlueprintCallable)
	ATPSCharacter* GetTPCCharacter();

};
