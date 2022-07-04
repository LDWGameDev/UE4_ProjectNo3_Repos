// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTesting_DamageUpAndInAir.h"
#include "Kismet/KismetMathLibrary.h"
#include "Library/Library_CustomMath.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_FallState.h"


/**
 *
 */

UCombatTesting_DamageUpAndInAir::UCombatTesting_DamageUpAndInAir()
{
	m_StateID = TEXT("CombatTesting_DamageUpAndInAirState");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag(FName(TEXT("StateMachine.EnemyState.CombatTesting.Action.Damage.DamageUpAndInAir")), false);
}




/**
 * Override functions
 */

void UCombatTesting_DamageUpAndInAir::EnterState()
{
	Super::EnterState();
	PlayDamageMontage();
}

void UCombatTesting_DamageUpAndInAir::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
}

void UCombatTesting_DamageUpAndInAir::ExitState()
{
	Super::ExitState();
}

void UCombatTesting_DamageUpAndInAir::HandleEndMontage()
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

void UCombatTesting_DamageUpAndInAir::PlayDamageMontage()
{
	if (m_AttackDefinitionREF == nullptr || !m_AttackDefinitionREF->CheckValid()) return;
	if (m_Character_EnemyCombatTestingREF->m_FallStateREF != nullptr)m_Character_EnemyCombatTestingREF->m_FallStateREF->SetFallingIndex(1);
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

