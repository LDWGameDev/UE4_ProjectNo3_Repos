// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseState.h"
#include "StateMachineComponent.h"


UBaseState::UBaseState() 
{
	m_EnterStateTime = FDateTime::UtcNow();
	m_ExitStateTime = m_EnterStateTime;
	b_IsInState = false;
}


/**
 * Override functions
 */

void UBaseState::EnterState()
{
	m_EnterStateTime = FDateTime::UtcNow();
	b_IsInState = true;
}

void UBaseState::TickState(float p_DeltaTime)
{
	if (!b_IsInState) return;
}

void UBaseState::ExitState()
{
	m_ExitStateTime = FDateTime::UtcNow();
	b_IsInState = false;
}




/**
 * Get, set member functions
 */

const FString& UBaseState::GetStateID()
{
	return m_StateID;
}

const FDateTime& UBaseState::GetStateTime_Enter()
{
	return m_EnterStateTime;
}

const FDateTime& UBaseState::GetStateTime_Exit()
{
	return m_ExitStateTime;
}

float UBaseState::GetStateTime_LastDuration()
{
	return (m_ExitStateTime - m_EnterStateTime).GetTotalMilliseconds() / 1000.0f;
}

float UBaseState::GetStateTime_StartToNow()
{
	return (FDateTime::UtcNow() - m_EnterStateTime).GetTotalMilliseconds() / 1000.0f;
}

FGameplayTag* UBaseState::GetStateTag()
{
	if (m_StateGameplayTag.IsValid()) return &m_StateGameplayTag;
	return nullptr;
}





/**
 * Public member functions 
 */

void UBaseState::SetExitStateTimeToNow()
{
	m_ExitStateTime = FDateTime::UtcNow();
}

bool UBaseState::CheckForCooldownTime()
{
	FTimespan Timespan = FDateTime::UtcNow() - m_ExitStateTime;
	return Timespan.GetTotalSeconds() > m_CooldownTime;
}

bool UBaseState::CheckForHoldingAfterExit(float p_TimeToCheck)
{
	FTimespan Timespan = FDateTime::UtcNow() - m_ExitStateTime;
	return Timespan.GetTotalSeconds() < p_TimeToCheck;
}





/**
 * Protected member functions
 */

void UBaseState::ChangeState(FString p_NextStateID)
{
	if (m_StateMachineComponentREF != nullptr)
	{
		m_StateMachineComponentREF->ChangeState(p_NextStateID);
	}
}