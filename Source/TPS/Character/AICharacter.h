﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPSCharacter.h"
#include "AICharacter.generated.h"

UCLASS()
class TPS_API AAICharacter : public ATPSCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UTPSAbilitySystemComponent* GetTPSAbilitySystemComponent() const override;

	virtual void InitASC(UTPSAbilitySystemComponent* InASC, AActor* InOwnerActor) override;
};
