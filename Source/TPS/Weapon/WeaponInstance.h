// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPS/AbilitySystem/TPSAbilitySet.h"
#include "WeaponInstance.generated.h"

UCLASS()
class TPS_API AWeaponInstance : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponInstance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities", Meta=(AllowPrivateAccess="true"))
	TObjectPtr<UTPSAbilitySet> AbilitySet;
};
