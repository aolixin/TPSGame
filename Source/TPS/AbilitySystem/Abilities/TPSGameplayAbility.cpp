// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameplayAbility.h"

#include "Camera/CameraComponent.h"
#include "TPS/Character/TPSCharacter.h"

UTPSGameplayAbility::UTPSGameplayAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// ActivationPolicy = ETPSAbilityActivationPolicy::OnInputTriggered;
}


void UTPSGameplayAbility::SetCameraMode(TSubclassOf<UTPSCameraMode> CameraMode)
{
	TObjectPtr<ATPSCharacter> character = Cast<ATPSCharacter>(CurrentActorInfo->AvatarActor.Get());
	if (character == nullptr)return;
	TObjectPtr<UTPSCameraComponent> CameraComponent = character->FindComponentByClass<UTPSCameraComponent>();
	if (CameraComponent == nullptr)return;
	CameraComponent->SetCameraMode(CameraMode);
	UE_LOG(LogTemp, Log, TEXT("---------------------------------------"));
}

void UTPSGameplayAbility::ClearCameraMode()
{
	TObjectPtr<ATPSCharacter> character = Cast<ATPSCharacter>(CurrentActorInfo->AvatarActor.Get());
	if (character == nullptr)return;
	TObjectPtr<UTPSCameraComponent> CameraComponent = character->FindComponentByClass<UTPSCameraComponent>();
	if (CameraComponent == nullptr)return;
	CameraComponent->ClearCameraMode();
}

USkeletalMeshComponent* UTPSGameplayAbility::GetOwnerSkeletalMeshComponent()
{
	TObjectPtr<ATPSCharacter> character = Cast<ATPSCharacter>(CurrentActorInfo->AvatarActor.Get());
	if (character == nullptr)return nullptr;
	return character->GetMesh();
}

void UTPSGameplayAbility::StartWeaponTargeting()
{
	AActor* AvatarActor = CurrentActorInfo->AvatarActor.Get();
	UAbilitySystemComponent* ASC = CurrentActorInfo->AbilitySystemComponent.Get();
	if (AvatarActor == nullptr || ASC == nullptr)return;

	UTPSCameraComponent* CameraComponent = AvatarActor->FindComponentByClass<UTPSCameraComponent>();
	if (CameraComponent == nullptr)return;

	// print camera location
	// print player location
	UE_LOG(LogTemp, Warning, TEXT("Player Location: %s"), *AvatarActor->GetActorLocation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Camera Location: %s"), *CameraComponent->GetComponentLocation().ToString());


	FHitResult result;
	FTransform AdditiveOffsetTransform = CameraComponent->GetAdditiveOffsetTransform();
	FTransform CameraTransform = CameraComponent->GetComponentTransform();

	FVector Start = AdditiveOffsetTransform.TransformPosition(FVector(0, 0, 0));
	UE_LOG(LogTemp, Warning, TEXT("Start Location: %s"), *Start.ToString());

	Start = CameraTransform.TransformPosition(Start);
	UE_LOG(LogTemp, Warning, TEXT("Start Location: %s"), *Start.ToString());

	FVector dir = AdditiveOffsetTransform.TransformVector(FVector(1, 0, 0));
	dir = CameraTransform.TransformVector(dir);

	FVector End = Start + dir * 1000; // 1000 is the distance

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(AvatarActor); // 忽略自身

	bool bHit = GetWorld()->LineTraceSingleByChannel(result, Start, End, ECC_Visibility, CollisionParams);
	
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1, 0, 1);

	FGameplayAbilityTargetDataHandle targetData;
	if (bHit)
	{
		targetData.Add(new FGameplayAbilityTargetData_SingleTargetHit(result)); // 假设你使用单个目标
	}
	OnRangedWeaponTargetDataReady(targetData);
}
