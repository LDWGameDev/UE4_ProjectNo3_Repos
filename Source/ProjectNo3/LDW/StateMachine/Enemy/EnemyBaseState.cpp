// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseState.h"

/**
 * 
 */
UEnemyBaseState::UEnemyBaseState()
{

}



/**
 * Override functions
 */

void UEnemyBaseState::EnterState()
{
	Super::EnterState();
}

void UEnemyBaseState::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
}

void UEnemyBaseState::ExitState()
{
	Super::ExitState();
}



/**
 * Public member functions
 */

void UEnemyBaseState::InitState(UStateMachineComponent* p_StateMachineREF, AActor* p_CharacterEnemeyREF)
{
	m_StateMachineComponentREF = p_StateMachineREF;
}

void UEnemyBaseState::HandleAnimNotify_01()
{

}

void UEnemyBaseState::HandleAnimNotify_02()
{

}

void UEnemyBaseState::HandleAnimNotify_03()
{

}

void UEnemyBaseState::HandleEndMontage()
{

}