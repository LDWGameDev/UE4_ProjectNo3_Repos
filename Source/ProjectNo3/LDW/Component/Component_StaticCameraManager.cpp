// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_StaticCameraManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Library/Library_CustomMath.h"



UComponent_StaticCameraManager::UComponent_StaticCameraManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}




/**
 * Override functions
 */

void UComponent_StaticCameraManager::CreateCameraInstances()
{
	m_CameraActor_01 = GetWorld()->SpawnActor<ACameraActor>();
	m_CameraActor_02 = GetWorld()->SpawnActor<ACameraActor>();
	(m_CameraActor_01->GetCameraComponent())->bConstrainAspectRatio = false;
	(m_CameraActor_02->GetCameraComponent())->bConstrainAspectRatio = false;
}

void UComponent_StaticCameraManager::BeginPlay()
{
	Super::BeginPlay();
}

void UComponent_StaticCameraManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



/**
 * Public member functions
 */

void UComponent_StaticCameraManager::SetStaticCamera_01(const FVector& p_Location, const FRotator& p_Rotation)
{
	if (m_CameraActor_01 == nullptr) return;
	m_CameraActor_01->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	m_CameraActor_01->SetActorLocationAndRotation(p_Location, p_Rotation);
}

void UComponent_StaticCameraManager::SetStaticCamera_01(const FVector& p_Location, const FVector& p_LocationToLookAt)
{
	if (m_CameraActor_01 == nullptr) return;
	m_CameraActor_01->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(p_Location, p_LocationToLookAt);
	m_CameraActor_01->SetActorLocationAndRotation(p_Location, Rotation);
}

void UComponent_StaticCameraManager::SetStaticCamera_01(const FVector& p_Location, const FVector& p_LocationToLookAt, AActor* p_ActorToAttach)
{
	if (m_CameraActor_01 == nullptr || p_ActorToAttach == nullptr) return;
	m_CameraActor_01->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(p_Location, p_LocationToLookAt);
	m_CameraActor_01->SetActorLocationAndRotation(p_Location, Rotation);
	m_CameraActor_01->AttachToActor(p_ActorToAttach, FAttachmentTransformRules::KeepWorldTransform);
}

void UComponent_StaticCameraManager::SetStaticCamera_01(const AActor* p_ActorToLookAt, const FVector& p_RelativeLocation, const FRotator& p_RotationOffsetToTarget)
{
	if (m_CameraActor_01 == nullptr || p_ActorToLookAt == nullptr) return;
	m_CameraActor_01->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	FVector Location =  ULibrary_CustomMath::WorldLocationOfRelativeLocationToActor(p_ActorToLookAt, p_RelativeLocation);
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Location, p_ActorToLookAt->GetActorLocation());
	Rotation = UKismetMathLibrary::ComposeRotators(Rotation, p_RotationOffsetToTarget);
	m_CameraActor_01->SetActorLocationAndRotation(Location, Rotation);
}

void UComponent_StaticCameraManager::SetStaticCamera_02(const FVector& p_Location, const FVector& p_LocationToLookAt)
{
	if (m_CameraActor_02 == nullptr) return;
	m_CameraActor_02->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(p_Location, p_LocationToLookAt);
	m_CameraActor_02->SetActorLocationAndRotation(p_Location, Rotation);
}
