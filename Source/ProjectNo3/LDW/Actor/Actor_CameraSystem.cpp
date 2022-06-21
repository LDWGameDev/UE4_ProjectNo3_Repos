// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_CameraSystem.h"
#include "Camera/CameraComponent.h"


AActor_CameraSystem::AActor_CameraSystem()
{
	PrimaryActorTick.bCanEverTick = true;
	m_SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root Component"));
	this->SetRootComponent(m_SceneRootComponent);

	m_SpringArm_Camera_01 = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm Camera 01"));
	m_SpringArm_Camera_01->SetupAttachment(m_SceneRootComponent);
	m_SpringArm_Camera_02 = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm Camera 02"));
	m_SpringArm_Camera_02->SetupAttachment(m_SceneRootComponent);
	m_SpringArm_Camera_03 = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm Camera 03"));
	m_SpringArm_Camera_03->SetupAttachment(m_SceneRootComponent);
}

void AActor_CameraSystem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (m_SpringArm_Camera_01 == nullptr || m_SpringArm_Camera_02 == nullptr || m_SpringArm_Camera_03 == nullptr) return;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	m_CameraActor_Camera_01 = GetWorld()->SpawnActor<ACameraActor>(SpawnParams);
	m_CameraActor_Camera_01->AttachToComponent(m_SpringArm_Camera_01, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	(m_CameraActor_Camera_01->GetCameraComponent())->bConstrainAspectRatio = false;

	m_CameraActor_Camera_02 = GetWorld()->SpawnActor<ACameraActor>(SpawnParams);
	m_CameraActor_Camera_02->AttachToComponent(m_SpringArm_Camera_02, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	(m_CameraActor_Camera_02->GetCameraComponent())->bConstrainAspectRatio = false;

	m_CameraActor_Camera_03 = GetWorld()->SpawnActor<ACameraActor>(SpawnParams);
	m_CameraActor_Camera_03->AttachToComponent(m_SpringArm_Camera_03, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	(m_CameraActor_Camera_03->GetCameraComponent())->bConstrainAspectRatio = false;
}

void AActor_CameraSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AActor_CameraSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}




/**
 * Public member function
 */

void AActor_CameraSystem::SetViewTargetToActorSequence_Implementation(const FName& p_ActorSequenceID, APlayerController* p_PlayerControllerToSetView)
{
	if (p_PlayerControllerToSetView == nullptr) return;
	m_SavedPlayerController = p_PlayerControllerToSetView;
}

void AActor_CameraSystem::ReturnViewTarget()
{
	if (m_Delegate_ReturnViewTarget.IsBound()) m_Delegate_ReturnViewTarget.Broadcast();
}

void AActor_CameraSystem::SetViewTargetToCameraActor(int32 p_CameraID, float p_BlendTime /* = 0.0f */, EViewTargetBlendFunction p_BlendFunction /* = EViewTargetBlendFunction::VTBlend_EaseInOut */, float p_BlendExp /* = 1.0f */, bool p_LockToCameraView /* = true */)
{
	if (m_SavedPlayerController == nullptr) return;
	switch (p_CameraID)
	{
	case 0:
	{
		m_SavedPlayerController->SetViewTargetWithBlend(m_CameraActor_Camera_01, p_BlendTime, p_BlendFunction, p_BlendExp, p_LockToCameraView);
		break;
	}
	case 1:
	{
		m_SavedPlayerController->SetViewTargetWithBlend(m_CameraActor_Camera_02, p_BlendTime, p_BlendFunction, p_BlendExp, p_LockToCameraView);
		break;
	}
	case 2:
	{
		m_SavedPlayerController->SetViewTargetWithBlend(m_CameraActor_Camera_03, p_BlendTime, p_BlendFunction, p_BlendExp, p_LockToCameraView);
		break;
	}
	}
}