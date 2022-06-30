// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_EnemyBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Library/Library_CustomMath.h"
#include "System/CombatSystem/System_CombatContainer.h"
#include "StateMachine/Enemy/EnemyBaseState.h"

/**
 * 
 */

ACharacter_EnemyBase::ACharacter_EnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// State Machine
	m_StateMachine_01 = CreateDefaultSubobject<UStateMachineComponent>(TEXT("State Machine 01"));
}



/**
 * Override functions
 */

void ACharacter_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
	InitTimelines();
}


void ACharacter_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickTimelines(DeltaTime);
	CalculateMovement();
}

void ACharacter_EnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacter_EnemyBase::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	if (m_Delegate_LandStart.IsBound())
	{
		m_Delegate_LandStart.Broadcast();
	}
}

void ACharacter_EnemyBase::ActivateEnemy(bool p_DoActivate)
{
	b_IsActive = p_DoActivate; 
}





/**
 * Interface functions
 */

void ACharacter_EnemyBase::TakeHit(FStruct_AttackDefinition& p_AttackDefinition)
{

}

const FGameplayTagContainer& ACharacter_EnemyBase::GetTagContainer()
{
	return m_TagContainer;
}

UEnemyBaseState* ACharacter_EnemyBase::GetCurrentState_EnemyBaseState()
{
	if (m_StateMachine_01->GetCurrentState() == nullptr) return nullptr;
	return Cast< UEnemyBaseState>(m_StateMachine_01->GetCurrentState());
}





/**
 * Public member functions
 */

void ACharacter_EnemyBase::MoveToLocation(const FVector& p_NewLocation, float p_BlendTime)
{
	m_SavedCurrentLocation = this->GetActorLocation();
	m_SavedNewLocation = p_NewLocation;
	if (p_BlendTime <= 0.0f)
	{
		SetActorLocation(p_NewLocation, true);
	}
	else
	{
		m_Timeline_LocationControl.SetPlayRate(1.0f / p_BlendTime);
		m_Timeline_LocationControl.PlayFromStart();
	}
}

void ACharacter_EnemyBase::RotateToRotation(const FRotator& p_NewRotation, float p_BlendTime)
{
	m_SavedCurrentRotator = GetActorRotation();
	m_SavedNextRotator = p_NewRotation;
	m_SavedNextRotator.Pitch = 0.0f;
	m_SavedNextRotator.Roll = 0.0f;
	if (p_BlendTime <= 0.0f)
	{
		SetActorRotation(m_SavedNextRotator);
	}
	else
	{
		m_Timeline_RotationControl.SetPlayRate(1.0f / p_BlendTime);
		m_Timeline_RotationControl.PlayFromStart();
	}
}

void ACharacter_EnemyBase::RotateToFaceActor(AActor* p_TargetActor, float p_BlendTime)
{
	if (p_TargetActor == nullptr) return;
	FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), p_TargetActor->GetActorLocation());
	RotateToRotation(LookAtRotator, 0.0f);
}

void ACharacter_EnemyBase::SetCapsuleSize(float p_NewCapsuleHalfHeight, float p_NewCapsuleRadius, float p_BlendTime)
{
	if (p_NewCapsuleHalfHeight <= 0.0f || p_NewCapsuleRadius <= 0.0f) return;
	m_SavedCapsuleHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	m_SavedCapsuleRadius = GetCapsuleComponent()->GetUnscaledCapsuleRadius();
	m_SavedNewCapsuleHalfHeight = p_NewCapsuleHalfHeight;
	m_SavedNewCapsuleRadius = p_NewCapsuleRadius;

	if (p_BlendTime <= 0.0f)
	{
		GetCapsuleComponent()->SetCapsuleSize(p_NewCapsuleRadius, p_NewCapsuleHalfHeight, true);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -p_NewCapsuleHalfHeight));
	}
	else
	{
		m_Timeline_CapsuleSizeControl.SetPlayRate(1.0f / p_BlendTime);
		m_Timeline_CapsuleSizeControl.PlayFromStart();
	}
}

void ACharacter_EnemyBase::ResetCapsuleSize(float p_BlendTime)
{
	SetCapsuleSize(m_DefaultCapsuleHalfHeight, m_DefaultCapsuleRadius, p_BlendTime);
}






/**
 * Private member functions
 */

void ACharacter_EnemyBase::InitTimelines()
{
	// Create timeline m_Timeline_LocationControl
	if (m_CurveFloat_AlphaEaseInOut == nullptr) return;
	FOnTimelineFloatStatic OnTimelineFloat_PositionControl_01;
	OnTimelineFloat_PositionControl_01.BindLambda([&](float p_Value)
		{
			FVector NextPosition = FMath::Lerp(m_SavedCurrentLocation, m_SavedNewLocation, p_Value);
			this->SetActorLocation(NextPosition, true);
		});
	m_Timeline_LocationControl.AddInterpFloat(m_CurveFloat_AlphaEaseInOut, OnTimelineFloat_PositionControl_01);
	m_Timeline_LocationControl.SetLooping(false);
	m_Timeline_LocationControl.SetTimelineLength(1.0f);

	// Create timeline m_Timeline_RotationControl
	FOnTimelineFloatStatic OnTimelineFloat_RotationControl_01;
	OnTimelineFloat_RotationControl_01.BindLambda([&](float p_Value)
		{
			FRotator NextRotator = FMath::Lerp(m_SavedCurrentRotator, m_SavedNextRotator, p_Value);
			this->SetActorRotation(NextRotator);
		});
	m_Timeline_RotationControl.AddInterpFloat(m_CurveFloat_AlphaEaseInOut, OnTimelineFloat_RotationControl_01);
	m_Timeline_RotationControl.SetLooping(false);
	m_Timeline_RotationControl.SetTimelineLength(1.0f);

	// Create timeline m_Timeline_CapsuleSizeControl
	FOnTimelineFloatStatic OnTimelineFloat_CapsuleSizeControl_01;
	OnTimelineFloat_CapsuleSizeControl_01.BindLambda([&](float p_Value)
		{
			float HalfHeight = FMath::Lerp(m_SavedCapsuleHalfHeight, m_SavedNewCapsuleHalfHeight, p_Value);
			float Radius = FMath::Lerp(m_SavedCapsuleRadius, m_SavedNewCapsuleRadius, p_Value);
			GetCapsuleComponent()->SetCapsuleSize(Radius, HalfHeight, true);
			GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -HalfHeight));
		});
	m_Timeline_CapsuleSizeControl.AddInterpFloat(m_CurveFloat_AlphaEaseInOut, OnTimelineFloat_CapsuleSizeControl_01);
	m_Timeline_CapsuleSizeControl.SetTimelineLength(1.0f);
	m_Timeline_CapsuleSizeControl.SetLooping(false);
}

void ACharacter_EnemyBase::TickTimelines(float p_DeltaTime)
{
	m_Timeline_LocationControl.TickTimeline(p_DeltaTime);
	m_Timeline_RotationControl.TickTimeline(p_DeltaTime);
	m_Timeline_CapsuleSizeControl.TickTimeline(p_DeltaTime);
}

void ACharacter_EnemyBase::CalculateMovement()
{
	b_IsInAir = GetCharacterMovement()->IsFalling();
	m_CurrentMovingSpeed = GetVelocity().Size();
}