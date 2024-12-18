// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPSCharacter.h"

#include "AbilitySystemComponent.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "TPS/TPSGameplayTags.h"
#include "TPS/input/TPSInputComponent.h"
#include "TPS/Player/ATPSPlayerState.h"

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

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	AbilitySystemComponent = nullptr;
}

void ATPSCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Set up action bindings
	if (TObjectPtr<UTPSInputComponent> tpsInputComponent = Cast<UTPSInputComponent>(PlayerInputComponent))
	{
		// Jumping
		// InputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		// InputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		//
		// // Moving
		// tpsInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Move);
		//
		// // Looking
		// InputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Look);
		//
		// // Fire
		// InputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Fire);

		tpsInputComponent->BindNativeAction(InputConfig.Get(), TPSGameplayTags::InputTag_Move, ETriggerEvent::Triggered,
		                                    this, &ThisClass::Move, true);

		tpsInputComponent->BindNativeAction(InputConfig.Get(), TPSGameplayTags::InputTag_Look_Mouse,
		                                    ETriggerEvent::Triggered, this, &ThisClass::Look, true);

		tpsInputComponent->BindNativeAction(InputConfig.Get(), TPSGameplayTags::InputTag_Jump,
		                                    ETriggerEvent::Triggered, this, &ThisClass::Jump, true);

		TArray<uint32> BindHandles;
		tpsInputComponent->BindAbilityActions(InputConfig.Get(), this, &ThisClass::Input_AbilityInputTagPressed,
		                                      Input_AbilityInputTagReleased, BindHandles);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

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
	return Cast<ATPSPlayerState>(GetPlayerState())->GetAbilitySystemComponent();
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
}

bool ATPSCharacter::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return false;
}

bool ATPSCharacter::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return false;
}

bool ATPSCharacter::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return false;
}


void ATPSCharacter::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	// get ability system
	if (AbilitySystemComponent)
	{
	}
}

void ATPSCharacter::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
}


void ATPSCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	TObjectPtr<ATPSPlayerState> ps = Cast<ATPSPlayerState>(GetPlayerState());
	AbilitySystemComponent = ps->GetAbilitySystemComponent();
	InitASC(AbilitySystemComponent, ps);
}

void ATPSCharacter::InitASC(UAbilitySystemComponent* InASC, AActor* InOwnerActor)
{
	InASC->InitAbilityActorInfo(InOwnerActor, this);
}
