// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponInstance.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


UCLASS()
class TPS_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void AttachWeapon(TSubclassOf<AWeaponInstance> Instance, FName SocketName);

	UFUNCTION(BlueprintCallable)
	AWeaponInstance* GetCurrentWeapon();

	UFUNCTION()
	FTransform GetWeaponTransform(FName SocketName);
	
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<AWeaponInstance> CurrentWeapon;
};
