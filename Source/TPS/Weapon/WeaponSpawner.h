// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "WeaponSpawner.generated.h"


UCLASS()
class TPS_API AWeaponSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponSpawner();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponPickup")
	TObjectPtr<UCapsuleComponent> CollisionVolume;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponPickup")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponPickup")
	TSubclassOf<AWeaponInstance> InstanceClass;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
