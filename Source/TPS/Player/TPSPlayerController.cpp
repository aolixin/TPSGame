// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"

#include "ATPSPlayerState.h"

class UTPSAbilitySystemComponent;

ATPSPlayerController::ATPSPlayerController(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}


void ATPSPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);

	TObjectPtr<ATPSPlayerState> ps = Cast<ATPSPlayerState>(PlayerState);

	if (UTPSAbilitySystemComponent* ASC = ps->GetTPSAbilitySystemComponent())
	{
		ASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}
}
