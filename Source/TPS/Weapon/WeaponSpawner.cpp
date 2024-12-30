// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSpawner.h"

#include "WeaponComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AWeaponSpawner::AWeaponSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CollisionVolume = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionVolume"));
	CollisionVolume->InitCapsuleSize(80.f, 80.f);
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AWeaponSpawner::OnOverlapBegin);


	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);

	// WeaponMeshRotationSpeed = 40.0f;
	// CoolDownTime = 30.0f;
	// CheckExistingOverlapDelay = 0.25f;
	// bIsWeaponAvailable = true;
	bReplicates = true;
}

// Called when the game starts or when spawned
void AWeaponSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	APawn* OverlappingPawn = Cast<APawn>(OtherActor);
	if (OverlappingPawn != nullptr)
	{
		UWeaponComponent *WeaponComponent = OverlappingPawn->FindComponentByClass<UWeaponComponent>();
		if (WeaponComponent != nullptr)
		{
			WeaponComponent->AttachWeapon(InstanceClass, "hand_rSocket");
			Destroy();
		}
	}
}
