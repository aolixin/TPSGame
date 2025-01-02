// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

#include "TPS/Character/TPSCharacter.h"


// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UWeaponComponent::AttachWeapon(TSubclassOf<AWeaponInstance> Instance, FName SocketName)
{
	if (Instance)
	{
		ATPSCharacter *Character = Cast<ATPSCharacter>(GetOwner());
		CurrentWeapon = GetWorld()->SpawnActor<AWeaponInstance>( Instance);
		if (CurrentWeapon)
		{
			USkeletalMeshComponent* Mesh = Character->FindComponentByClass<USkeletalMeshComponent>();
			CurrentWeapon->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
			if (CurrentWeapon->AbilitySet)
			{
				UTPSAbilitySystemComponent *ASC = Character->GetTPSAbilitySystemComponent();
				CurrentWeapon->AbilitySet->GiveToAbilitySystem(ASC, nullptr, CurrentWeapon);
			}
		}
	}
}

AWeaponInstance* UWeaponComponent::GetCurrentWeapon()
{
	return CurrentWeapon.Get();
}

FTransform UWeaponComponent::GetWeaponTransform(FName SocketName)
{
	if (CurrentWeapon == nullptr)return FTransform::Identity;
	USkeletalMeshComponent* Mesh = CurrentWeapon->FindComponentByClass<USkeletalMeshComponent>();
	return Mesh->GetSocketTransform(SocketName);
}
