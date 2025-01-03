// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPSCharacter.h"

#include "AbilitySystemComponent.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"
#include "TPS/TPSGameplayTags.h"
#include "TPS/AbilitySystem/TPSAbilitySet.h"
#include "TPS/Player/ATPSPlayerState.h"
#include "TPS/TPSGameplayTags.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATPSCharacter

ATPSCharacter::ATPSCharacter(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	AbilitySystemComponent = nullptr;

	// TestComp = CreateDefaultSubobject<UTestSceneComponent>(TEXT("TestComp"));
	// TestComp->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	WeaponComponent->SetupAttachment(RootComponent);

	BackpackComponent = CreateDefaultSubobject<UBackpackComponent>(TEXT("BackpackComponent"));
	BackpackComponent->SetupAttachment(RootComponent);
}

void ATPSCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////
// Input


void ATPSCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATPSCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}


UAbilitySystemComponent* ATPSCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
	// return Cast<ATPSPlayerState>(GetPlayerState())->GetAbilitySystemComponent();
}

UTPSAbilitySystemComponent* ATPSCharacter::GetTPSAbilitySystemComponent() const
{
	return nullptr;
	// return Cast<UTPSAbilitySystemComponent>(GetAbilitySystemComponent());
}

void ATPSCharacter::GiveAbility(TSubclassOf<UGameplayAbility> Ability)
{
	if (!AbilitySystemComponent)return;
	if (Ability)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, 0));
	}
	// AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ATPSCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.Reset();
	TagContainer.AddTag(TPSGameplayTags::Actor_Character);
}



void ATPSCharacter::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	// get ability system
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityInputTagPressed(InputTag);
	}
}

void ATPSCharacter::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	// get ability system
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityInputTagReleased(InputTag);
	}
}

void ATPSCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ATPSPlayerState* ps = GetPlayerState<ATPSPlayerState>();
	if (ps == nullptr)return;
	AbilitySystemComponent = ps->GetTPSAbilitySystemComponent();
	if (AbilitySystemComponent == nullptr)return;

	InitASC(AbilitySystemComponent, ps);
	if (AbilitySet != nullptr)
		AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr, this);
}

void ATPSCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	TObjectPtr<ATPSPlayerState> ps = GetPlayerState<ATPSPlayerState>();
	AbilitySystemComponent = ps->GetTPSAbilitySystemComponent();
	InitASC(AbilitySystemComponent, ps);
}

void ATPSCharacter::InitASC(UTPSAbilitySystemComponent* InASC, AActor* InOwnerActor)
{
	InASC->InitAbilityActorInfo(InOwnerActor, this);
}
