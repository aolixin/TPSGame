// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "TPSInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FTPSInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

UCLASS()
class TPS_API UTPSInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FTPSInputAction> NativeInputActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FTPSInputAction> AbilityInputActions;
};
