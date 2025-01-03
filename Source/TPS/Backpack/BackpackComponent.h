// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TPS/Weapon/WeaponInstance.h"
#include "BackpackComponent.generated.h"

// 全局可访问的枚举
UENUM(BlueprintType)
enum class BackpackTimeType : uint8
{
	Gun   UMETA(DisplayName = "Gun"),
	Grenade   UMETA(DisplayName = "Grenade")
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPS_API UBackpackComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBackpackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Backpack")
	TMap<BackpackTimeType,TObjectPtr<AWeaponInstance>>Backpack;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Backpack")
	TMap<BackpackTimeType,TSubclassOf<AWeaponInstance>>Backpack_Init;

};
