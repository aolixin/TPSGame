#pragma once
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "TPS/AbilitySystem/TPSAbilitySystemComponent.h"

#include "ATPSPlayerState.generated.h"

UCLASS(Blueprintable)
class ATPSPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATPSPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return GetTPSAbilitySystemComponent();
	}

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	virtual UTPSAbilitySystemComponent* GetTPSAbilitySystemComponent() const { return AbilitySystemComponent; }

	void PreInitializeComponents() override;

	// template <class T>
	// const T* GetPawnData() const { return Cast<T>(PawnData); }
	//
	// void SetPawnData(const UTPSPawnData* InPawnData);
	//
	// virtual void PostInitializeComponents() override;

protected:
	// UPROPERTY()
	// TObjectPtr<const UTPSPawnData> PawnData;
	UPROPERTY(VisibleAnywhere, Category = "PlayerState")
	TObjectPtr<UTPSAbilitySystemComponent> AbilitySystemComponent;
};
