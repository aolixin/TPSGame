// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"


// Sets default values
AAICharacter::AAICharacter(const FObjectInitializer& ObjectInitializer ):Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// init ability system component
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UTPSAbilitySystemComponent>(
		this, TEXT("AbilitySystemComponent"));

	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* AAICharacter::GetAbilitySystemComponent() const 
{
	return AbilitySystemComponent;
}
UTPSAbilitySystemComponent* AAICharacter::GetTPSAbilitySystemComponent() const 
{
	return Cast<UTPSAbilitySystemComponent>(AbilitySystemComponent);
}

void AAICharacter::InitASC(UTPSAbilitySystemComponent* InASC, AActor* InOwnerActor)
{
	InASC->InitAbilityActorInfo(this, this);
}