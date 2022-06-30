// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTesting_DamageInAirState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Library/Library_CustomMath.h"


/**
 * 
 */

UCombatTesting_DamageInAirState::UCombatTesting_DamageInAirState()
{
	m_StateID = TEXT("CombatTesting_DamageInAirState");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag(FName(TEXT("StateMachine.EnemyState.CombatTesting.Action.Damage.DamageInAir")), false);
}


void UCombatTesting_DamageInAirState::EnterState()
{
	Super::EnterState();
	PlayDamageMontage();
}

void UCombatTesting_DamageInAirState::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
}

void UCombatTesting_DamageInAirState::ExitState()
{
	Super::ExitState();
}

void UCombatTesting_DamageInAirState::HandleEndMontage()
{
	Super::HandleEndMontage();
	if (m_Character_EnemyCombatTestingREF->b_IsInAir)
	{
		ChangeState(TEXT("CombatTesting_FallState"));
	}
	else
	{
		ChangeState(TEXT("CombatTesting_IdleState"));
	}
}




/**
 * Private member functions
 */

void UCombatTesting_DamageInAirState::PlayDamageMontage()
{
	if (m_AttackDefinitionREF == nullptr || !m_AttackDefinitionREF->CheckValid()) return;
	if (m_Character_EnemyCombatTestingREF->m_AnimInstanceREF_EnemyCombatTesting != nullptr)
	{
		m_Character_EnemyCombatTestingREF->m_AnimInstanceREF_EnemyCombatTesting->m_FallingIndex = 1;
	}

	// Knock up no simulate
	if (m_AttackDefinitionREF->m_AttackerAttackStateREF->b_DoControlPostion == true)
	{
		// Knock up do control location
		m_Character_EnemyCombatTestingREF->PlayMontageFromTable_DamageMontage(FName("Damage_Knock_Up_FaceUp_01_Inplace"), m_AttackDefinitionREF->m_AttackerAttackStateREF->m_ControlPositionTime);
		FVector NextLocation = ULibrary_CustomMath::WorldLocationOfRelativeLocationToActor(m_AttackDefinitionREF->m_AttackerActor, m_AttackDefinitionREF->m_AttackerAttackStateREF->m_ControlPositionOffset);
		m_Character_EnemyCombatTestingREF->MoveToLocation(NextLocation, m_AttackDefinitionREF->m_AttackerAttackStateREF->m_ControlPositionTime);
	}
	else
	{
		// Play knock up AnimMontage has root motion to drive character up
	}
}
