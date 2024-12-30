// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponInstance.h"


// Sets default values
AWeaponInstance::AWeaponInstance()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeaponInstance::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

