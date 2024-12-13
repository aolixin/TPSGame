#pragma once
#include "GameFramework/PlayerState.h"
#include "TPS/Character/TPSPawnData.h"
#include "ATPSPlayerState.generated.h"

UCLASS(Blueprintable)
class ATPSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	
	// template <class T>
	// const T* GetPawnData() const { return Cast<T>(PawnData); }
	//
	// void SetPawnData(const UTPSPawnData* InPawnData);
	//
	// virtual void PostInitializeComponents() override;
	
protected:
	// UPROPERTY()
	// TObjectPtr<const UTPSPawnData> PawnData;
};
