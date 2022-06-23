// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Enemy_CombatTesting.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "System/CombatSystem/System_CombatContainer.h"


ACharacter_Enemy_CombatTesting::ACharacter_Enemy_CombatTesting()
{
	// Set CapsuleComponent defaults
	GetCapsuleComponent()->InitCapsuleSize(40.0f, 86.0f);

	// Set CharacterMovement defaults
	GetCharacterMovement()->GravityScale = 2.5f;

}

void ACharacter_Enemy_CombatTesting::BeginPlay()
{
	Super::BeginPlay();
	InitTimelines();
}

void ACharacter_Enemy_CombatTesting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickTimelines(DeltaTime);
}





/**
 * Interface functions
 */

void ACharacter_Enemy_CombatTesting::TakeHit(FStruct_AttackDefinition& p_AttackDefinition)
{
	Super::TakeHit(p_AttackDefinition);
	if (!p_AttackDefinition.CheckValid()) return;

	switch ((p_AttackDefinition.m_AttackerAttackStateREF)->m_HitType)
	{
	case EHitType::LightAttack:
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy_CombatTesting TakeHit()     LightAttack"));
		break;
	}
	case EHitType::Knock:
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy_CombatTesting TakeHit()     Knock"));
		break;
	}
	}
}




/**
 * Private member functions
 */

void ACharacter_Enemy_CombatTesting::InitTimelines()
{
	if (m_CurveFloat_AlphaEaseInOut == nullptr) return;
	FOnTimelineFloatStatic OnTimelineFloat_PositionControl_01;
	OnTimelineFloat_PositionControl_01.BindLambda([&](float p_Value) 
		{
			FVector NextPosition = FMath::Lerp(m_SavedCurrentPosition, m_SavedNewPosition, p_Value);
			this->SetActorLocation(NextPosition, true);
		});
	m_Timeline_PositionControl.AddInterpFloat(m_CurveFloat_AlphaEaseInOut, OnTimelineFloat_PositionControl_01);
	m_Timeline_PositionControl.SetLooping(false);
	m_Timeline_PositionControl.SetTimelineLength(1.0f);
}

void ACharacter_Enemy_CombatTesting::TickTimelines(float p_DeltaTime)
{
	m_Timeline_PositionControl.TickTimeline(p_DeltaTime);
}