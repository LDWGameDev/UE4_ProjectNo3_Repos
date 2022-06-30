// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTesting_BaseState.h"


/**
 * 
 */

UCombatTesting_BaseState::UCombatTesting_BaseState()
{

}



/**
 * Override functions
 */

void UCombatTesting_BaseState::EnterState()
{
	Super::EnterState();
	if (m_Character_EnemyCombatTestingREF == nullptr) return;
}

void UCombatTesting_BaseState::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (m_Character_EnemyCombatTestingREF == nullptr) return;
}

void UCombatTesting_BaseState::ExitState()
{
	Super::ExitState();
	if (m_Character_EnemyCombatTestingREF == nullptr) return;
}

void UCombatTesting_BaseState::InitState(UStateMachineComponent* p_StateMachineREF, AActor* p_CharacterEnemeyREF)
{
	Super::InitState(p_StateMachineREF, p_CharacterEnemeyREF);
	m_Character_EnemyCombatTestingREF = Cast<ACharacter_Enemy_CombatTesting>(p_CharacterEnemeyREF);

}




/**
 * 
 */