// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTesting_GetUpState.h"

UCombatTesting_GetUpState::UCombatTesting_GetUpState()
{

}

void UCombatTesting_GetUpState::EnterState()
{
	Super::EnterState();
}

void UCombatTesting_GetUpState::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
}

void UCombatTesting_GetUpState::ExitState()
{
	Super::ExitState();
}

void UCombatTesting_GetUpState::InitState(UStateMachineComponent* p_StateMachineREF, AActor* p_CharacterEnemeyREF)
{
	Super::InitState(p_StateMachineREF, p_CharacterEnemeyREF);
}
