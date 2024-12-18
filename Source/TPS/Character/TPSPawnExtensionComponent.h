#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitySystemComponent.h"

#include "TPSPawnExtensionComponent.generated.h"

UCLASS()
class TPS_API UTPSPawnExtensionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTPSPawnExtensionComponent(const FObjectInitializer& ObjectInitializer);

	/** Gets the current ability system component, which may be owned by a different actor */
	UFUNCTION(BlueprintPure, Category = "Lyra|Pawn")
	UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }

	void InitializeAbilitySystem(UAbilitySystemComponent* InASC, AActor* InOwnerActor);

	void UninitializeAbilitySystem();
	
	
protected:
	UPROPERTY(Transient)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
