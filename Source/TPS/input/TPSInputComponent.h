// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "TPSInputConfig.h"


#include "TPSInputComponent.generated.h"


UCLASS(Config = Input)
class TPS_API UTPSInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTPSInputComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


	template <class UserClass, typename FuncType>
	void BindNativeAction(const UTPSInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent,
	                      UserClass* Object, FuncType Func, bool bLogIfNotFound);

	template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const UTPSInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc,
	                        ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles);
	
};


template <class UserClass, typename FuncType>
void UTPSInputComponent::BindNativeAction(const UTPSInputConfig* InputConfig, const FGameplayTag& InputTag,
										  ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func,
										  bool bLogIfNotFound)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag, bLogIfNotFound))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}



template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UTPSInputComponent::BindAbilityActions(const UTPSInputConfig* InputConfig, UserClass* Object,
											PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc,
											TArray<uint32>& BindHandles)
{
	check(InputConfig);

	for (const FTPSInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, PressedFunc,
										   Action.InputTag).GetHandle());
			}

			if (ReleasedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc,
										   Action.InputTag).GetHandle());
			}
		}
	}
}
