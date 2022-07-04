// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTesting_GetUpState.h"

UCombatTesting_GetUpState::UCombatTesting_GetUpState()
{
	m_StateID = TEXT("CombatTesting_LandAndGetUpState");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag(FName(TEXT("StateMachine.EnemyState.CombatTesting.Action.GetUp.LandAndGetUp")), false);
}

void UCombatTesting_GetUpState::EnterState()
{
	Super::EnterState();
	switch (m_GetUpIndex)
	{
	case 1:
	{
		m_Character_EnemyCombatTestingREF->PlayMontageFromTable_DamageMontage(FName(TEXT("Damage_LandAndGetUp_FaceUp_01")));
		break;
	}
	}
}

void UCombatTesting_GetUpState::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
}

void UCombatTesting_GetUpState::ExitState()
{
	Super::ExitState();
	m_GetUpIndex = 0;
}

void UCombatTesting_GetUpState::HandleEndMontage()
{
	Super::HandleEndMontage();
	ChangeState(TEXT("CombatTesting_IdleState"));
}