// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTesting_IdleState.h"

UCombatTesting_IdleState::UCombatTesting_IdleState()
{
	m_StateID = TEXT("CombatTesting_IdleState");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag(FName(TEXT("StateMachine.EnemyState.CombatTesting.Locomotion.Idle")), false);
}

void UCombatTesting_IdleState::EnterState()
{
	Super::EnterState();
}

void UCombatTesting_IdleState::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
}

void UCombatTesting_IdleState::ExitState()
{
	Super::ExitState();
}
