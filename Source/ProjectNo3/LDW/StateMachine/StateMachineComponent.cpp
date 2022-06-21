// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineComponent.h"
#include "GameplayTagContainer.h"


/**
 * Override Functions
 */
UStateMachineComponent::UStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	m_CurrentState = nullptr;
}


void UStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();
	m_StatesHistory.Reserve(m_NumberHistoryStates);
}


void UStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (m_bIsActive && m_CurrentState != nullptr) 
	{
		m_CurrentState->TickState(DeltaTime);
	}
}



/**
 * Get, Set Functions
 */

TArray<UBaseState*>* UStateMachineComponent::GetAvailableStatesList()
{
	return &m_AvailableStatesList;
}

UBaseState* UStateMachineComponent::GetCurrentState()
{
	return m_CurrentState;
}

UBaseState* UStateMachineComponent::GetState_ByID(const FString& p_StateID)
{
	for (UBaseState* State : m_AvailableStatesList)
	{
		if ((State->GetStateID()).Equals(p_StateID)) return State;
	}
	return nullptr;
}



/**
 * Public Functions
 */

void UStateMachineComponent::ActivateStateMachine(const FString& p_StartStateID) 
{
	m_bIsActive = true;
	UBaseState* StartState = GetState_ByID(p_StartStateID);
	if (StartState != nullptr)
	{
		m_CurrentState = StartState;
		m_CurrentState->EnterState();
	}
}

void UStateMachineComponent::DeactivateStateMachine()
{
	m_bIsActive = false;
	m_CurrentState = nullptr;
	m_StatesHistory.Reset(m_NumberHistoryStates);
}

void UStateMachineComponent::ChangeState(const FString& p_NewStateID) 
{
	UBaseState* NextState = GetState_ByID(p_NewStateID);
	if (m_CurrentState == nullptr || m_CurrentState->GetStateTime_StartToNow() < m_MinStateTime || NextState == nullptr || !(NextState->CheckForCooldownTime())) return;
	
	m_CurrentState->ExitState();
	AddStateToHistory(m_CurrentState);
	NextState->EnterState();
	m_CurrentState = NextState;

	// Broad cast delegate m_Delegate_ChangeState
	if (m_Delegate_ChangeState.IsBound()) m_Delegate_ChangeState.Broadcast();

	// Debug new state
	FGameplayTag* stateTag = m_CurrentState->GetStateTag();
	if (stateTag != nullptr || !stateTag->IsValid())
	{
		FString stateID = m_CurrentState->GetStateID();
		UE_LOG(LogTemp, Warning, TEXT("StateMachineCom ChangeState() - %s"), *stateID);
	}
}



/**
 * Private Functions
 */

bool UStateMachineComponent::AddStateToHistory(UBaseState* p_LastState)
{
	if (p_LastState == nullptr) return false;
	if (m_StatesHistory.Num() < m_NumberHistoryStates) 
	{
		m_StatesHistory.Add(p_LastState);
	}
	else
	{
		m_StatesHistory.RemoveAt(0, 1, false);
		m_StatesHistory.Add(p_LastState);
	}

	// Debug
	//FGameplayTag* stateTag = p_LastState->GetStateTag();
	//if (stateTag != nullptr)
	//{
	//	FString stateID = p_LastState->GetStateID();
	//	UE_LOG(LogTemp, Warning, TEXT("StateMachineCom History - %s"), *stateID);
	//}

	return true;
}