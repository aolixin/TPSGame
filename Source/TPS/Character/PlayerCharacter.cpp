// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "TPS/TPSGameplayTags.h"
#include "TPS/Player/ATPSPlayerState.h"


// Sets default values
APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UTPSCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// FollowCamera->SetupAttachment(RootComponent);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	// FollowCamera->InitCameraMode(DefaultCameraMode);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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

		if (InputConfig == nullptr)
		{
			InputConfig.LoadSynchronous();
		}
		check(InputConfig);
		
		
		tpsInputComponent->BindNativeAction(InputConfig.Get(), TPSGameplayTags::InputTag_Move, ETriggerEvent::Triggered,
											this, &ThisClass::Move, true);

		tpsInputComponent->BindNativeAction(InputConfig.Get(), TPSGameplayTags::InputTag_Look_Mouse,
											ETriggerEvent::Triggered, this, &ThisClass::Look, true);

		tpsInputComponent->BindNativeAction(InputConfig.Get(), TPSGameplayTags::InputTag_Jump,
											ETriggerEvent::Triggered, this, &ThisClass::Jump, true);

		TArray<uint32> BindHandles;
		tpsInputComponent->BindAbilityActions(InputConfig.Get(), this, &ThisClass::Input_AbilityInputTagPressed,
											  &ThisClass::Input_AbilityInputTagReleased, BindHandles);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
			   TEXT(
				   "'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
			   ), *GetNameSafe(this));
	}
}

UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	return Cast<ATPSPlayerState>(GetPlayerState())->GetAbilitySystemComponent();
}

UTPSAbilitySystemComponent* APlayerCharacter::GetTPSAbilitySystemComponent()const
{
	return Cast<UTPSAbilitySystemComponent>(GetAbilitySystemComponent());
}

void APlayerCharacter::InitASC(UTPSAbilitySystemComponent* InASC, AActor* InOwnerActor)
{
	InASC->InitAbilityActorInfo(InOwnerActor, this);
}

void APlayerCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	Super::GetOwnedGameplayTags(TagContainer);
	TagContainer.AddTag(TPSGameplayTags::Actor_Character_Player);
}