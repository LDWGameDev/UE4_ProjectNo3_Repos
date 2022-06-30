// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTesting_FallState.h"



/**
 * 
 */

UCombatTesting_FallState::UCombatTesting_FallState()
{
	m_StateID = TEXT("CombatTesting_FallState");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag(FName(TEXT("StateMachine.EnemyState.CombatTesting.Action.Fall")), false);
}



/**
 * Override functions
 */

void UCombatTesting_FallState::EnterState()
{
	Super::EnterState();
}

void UCombatTesting_FallState::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (b_HasLanded) ChangeState("CombatTesting_IdleState");
}

void UCombatTesting_FallState::ExitState()
{
	Super::ExitState();
	b_HasLanded = false;

	// Reset m_FallingIndex in AnimInstance (AnimInstance_Enemy_CombatTesting)
	if (m_Character_EnemyCombatTestingREF->m_AnimInstanceREF_EnemyCombatTesting != nullptr)
	{
		m_Character_EnemyCombatTestingREF->m_AnimInstanceREF_EnemyCombatTesting->m_FallingIndex = 0;
	}
}

void UCombatTesting_FallState::InitState(UStateMachineComponent* p_StateMachineREF, AActor* p_CharacterEnemeyREF)
{
	Super::InitState(p_StateMachineREF, p_CharacterEnemeyREF);
	if (m_Character_EnemyCombatTestingREF == nullptr) return;
	m_LandStart_DelegateREF = &(m_Character_EnemyCombatTestingREF->m_Delegate_LandStart);

	if (m_LandStart_DelegateREF != nullptr) m_LandStart_DelegateREF->AddUObject(this, &UCombatTesting_FallState::HandleDelegate_LandStart);
}

void UCombatTesting_FallState::HandleDelegate_LandStart()
{
	if (!b_IsInState) return;
	b_HasLanded = true;
}