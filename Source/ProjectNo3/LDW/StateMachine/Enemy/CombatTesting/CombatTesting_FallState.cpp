// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTesting_FallState.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_GetUpState.h"



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
	m_Character_EnemyCombatTestingREF->m_AnimInstanceREF_EnemyCombatTesting->m_FallingIndex = m_FallingIndex;
}

void UCombatTesting_FallState::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (b_HasLanded)
	{
		b_HasLanded = false;
		switch (m_FallingIndex)
		{
		case 0:
		{
			ChangeState("CombatTesting_IdleState");
			break;
		}
		case 1:
		{
			ChangeState("CombatTesting_LandAndGetUpState");
			break;
		}
		}
	}
}

void UCombatTesting_FallState::ExitState()
{
	Super::ExitState();
	b_HasLanded = false;

	// Reset m_FallingIndex in AnimInstance (AnimInstance_Enemy_CombatTesting)
	if (m_Character_EnemyCombatTestingREF->m_AnimInstanceREF_EnemyCombatTesting != nullptr)
	{
		m_Character_EnemyCombatTestingREF->m_AnimInstanceREF_EnemyCombatTesting->m_FallingIndex = 0;
		m_FallingIndex = 0;
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

void UCombatTesting_FallState::SetFallingIndex(int32 p_NewFallingIndex)
{
	if (m_Character_EnemyCombatTestingREF == nullptr) return;
	if (m_Character_EnemyCombatTestingREF->m_AnimInstanceREF_EnemyCombatTesting != nullptr) m_Character_EnemyCombatTestingREF->m_AnimInstanceREF_EnemyCombatTesting->m_FallingIndex = p_NewFallingIndex;
	if (m_Character_EnemyCombatTestingREF->m_LandAndGetUpStateREF != nullptr) m_Character_EnemyCombatTestingREF->m_LandAndGetUpStateREF->m_GetUpIndex = p_NewFallingIndex;
	m_FallingIndex = p_NewFallingIndex;
}