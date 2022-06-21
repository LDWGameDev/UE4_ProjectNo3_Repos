// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_UnarmedIdle.h"
#include "../../../Interface/Interface_PlayerControllerInput.h"
#include "../../../AnimInstance/AnimInstance_PlayerHuman.h"
#include "PlayerHumanState_UnarmedDash.h"

UPlayerHumanState_UnarmedIdle::UPlayerHumanState_UnarmedIdle()
{
	m_StateID = FString(TEXT("PlayerHumanState_UnarmedIdle"));
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Locomotion.Idle.UnarmedIdle", false);
	m_MoveForward_DelegateREF = nullptr;
	m_MoveRight_DelegateREF = nullptr;
	m_JumpPressed_DelegateREF = nullptr;
	m_MoveForwardValue = 0.0f;
	m_MoveRightValue = 0.0f;
}


/**
 * Override Functions
 */

void UPlayerHumanState_UnarmedIdle::EnterState()
{
	Super::EnterState();
	m_CharPlayerHuman_Owner->m_AnimInstance_PlayerHuman_REF->b_DoFeetIK = true;
	m_CharPlayerHuman_Owner->SetControlRigFootIKAlpha(1.0f, 0.75f);
}

void UPlayerHumanState_UnarmedIdle::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (FMath::Abs(m_MoveRightValue) > 0.01f || FMath::Abs(m_MoveForwardValue) > 0.01f)
	{
		ChangeState(FString(TEXT("PlayerHumanState_UnarmedJog")));
	}
}

void UPlayerHumanState_UnarmedIdle::ExitState()
{
	Super::ExitState();
	if (m_CharPlayerHuman_Owner->m_AnimInstance_PlayerHuman_REF != nullptr)
	{
		m_CharPlayerHuman_Owner->m_AnimInstance_PlayerHuman_REF->b_DoFeetIK = false;
	}
	m_CharPlayerHuman_Owner->SetControlRigFootIKAlpha(0.0f, 0.25f);
}

void UPlayerHumanState_UnarmedIdle::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput != nullptr)
	{
		m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
		m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
		m_JumpPressed_DelegateREF = IPlayerInput->GetDelegate_JumpPressed();
		m_DashStart_DelegateREF = IPlayerInput->GetDelegate_DashStart();

		if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedIdle::HandleInput_MoveForward);
		if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedIdle::HandleInput_MoveRight);
		if (m_JumpPressed_DelegateREF != nullptr) m_JumpPressed_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedIdle::HandleInput_JumpPressed);
		if (m_DashStart_DelegateREF != nullptr) m_DashStart_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedIdle::HandleAction_DashStart);
	}
}

void UPlayerHumanState_UnarmedIdle::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);
	if (m_JumpPressed_DelegateREF != nullptr) m_JumpPressed_DelegateREF->RemoveAll(this);
	if (m_DashStart_DelegateREF != nullptr) m_DashStart_DelegateREF->RemoveAll(this);
	m_MoveForward_DelegateREF = nullptr;
	m_MoveRight_DelegateREF = nullptr;
	m_JumpPressed_DelegateREF = nullptr;
	m_DashStart_DelegateREF = nullptr;
}



/**
 * Private Member Functions
 */

void UPlayerHumanState_UnarmedIdle::HandleInput_MoveForward(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_AxisValue;
}

void UPlayerHumanState_UnarmedIdle::HandleInput_MoveRight(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_AxisValue;
}

void UPlayerHumanState_UnarmedIdle::HandleInput_JumpPressed() 
{
	if (!b_IsInState) return;
	ChangeState("PlayerHumanState_UnarmedJump");
}

void UPlayerHumanState_UnarmedIdle::HandleAction_DashStart()
{
	if (!b_IsInState || m_CharPlayerHuman_Owner == nullptr) return;
	ChangeState("PlayerHumanState_UnarmedDash");
}
