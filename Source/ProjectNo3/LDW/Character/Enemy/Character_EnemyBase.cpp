// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_EnemyBase.h"
#include "Library/Library_CustomMath.h"
#include "System/CombatSystem/System_CombatContainer.h"


/**
 * 
 */

ACharacter_EnemyBase::ACharacter_EnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
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
}

void ACharacter_EnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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





/**
 * Public member functions
 */

void ACharacter_EnemyBase::MoveToLocation(const FVector& p_NewLocation, float p_BlendTime)
{
	m_SavedCurrentLocation = this->GetActorLocation();
	m_SavedNewLocation = p_NewLocation;

	if (p_BlendTime <= 0.0f)
	{
		this->SetActorLocation(p_NewLocation, true);
	}
	else
	{
		m_Timeline_LocationControl.SetPlayRate(1.0f / p_BlendTime);
		m_Timeline_LocationControl.PlayFromStart();
	}
}





/**
 * Private member functions*
 */

void ACharacter_EnemyBase::InitTimelines()
{
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
}

void ACharacter_EnemyBase::TickTimelines(float p_DeltaTime)
{
	m_Timeline_LocationControl.TickTimeline(p_DeltaTime);
}