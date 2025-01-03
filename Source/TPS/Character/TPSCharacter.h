// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AbilitySystemInterface.h"
#include "GameplayCueInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Character.h"
#include "TPS/AbilitySystem/TPSAbilitySystemComponent.h"
#include "TPS/Backpack/BackpackComponent.h"
#include "TPS/input/TPSInputComponent.h"
#include "TPS/Camera/TPSCameraComponent.h"
#include "TPS/Weapon/WeaponComponent.h"

#include "TPSCharacter.generated.h"

class UTPSAbilitySet;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UTPSPawnExtensionComponent;
class UWeaponComponent;

struct FGameplayTagContainer;
struct FGameplayTag;


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class TPS_API ATPSCharacter : public ACharacter, public IAbilitySystemInterface, public IGameplayCueInterface,
                              public IGameplayTagAssetInterface
{
	GENERATED_BODY()

	// Ability sets to grant to this pawn's ability system.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities", Meta=(AllowPrivateAccess="true"))
	TObjectPtr<UTPSAbilitySet> AbilitySet;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponComponent>WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBackpackComponent>BackpackComponent;

public:
	ATPSCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UTPSAbilitySystemComponent* GetTPSAbilitySystemComponent() const;
	

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void GiveAbility(TSubclassOf<UGameplayAbility> Ability);

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	// virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	// virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	// virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void InitASC(UTPSAbilitySystemComponent* InASC, AActor* InOwnerActor);

protected:

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<UTPSAbilitySystemComponent> AbilitySystemComponent;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);

protected:


	// To add mapping context
	virtual void BeginPlay();

public:

};
