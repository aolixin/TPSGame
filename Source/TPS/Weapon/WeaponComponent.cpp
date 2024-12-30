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


void UWeaponComponent::AttachWeapon(TSubclassOf<AWeaponInstance> Instance, FName SocketName) const
{
	if (Instance)
	{
		ATPSCharacter *Character = Cast<ATPSCharacter>(GetOwner());
		AWeaponInstance* Weapon = GetWorld()->SpawnActor<AWeaponInstance>( Instance);
		if (Weapon)
		{
			USkeletalMeshComponent* Mesh = Character->FindComponentByClass<USkeletalMeshComponent>();
			Weapon->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
			if (Weapon->AbilitySet)
			{
				UTPSAbilitySystemComponent *ASC = Character->GetTPSAbilitySystemComponent();
				Weapon->AbilitySet->GiveToAbilitySystem(ASC, nullptr, Weapon);
			}
		}

	}
}
