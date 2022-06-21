// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinIdle.h"


UPlayerHumanState_AssassinIdle::UPlayerHumanState_AssassinIdle()
{
	m_StateID = TEXT("PlayerHumanState_AssassinIdle");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Locomotion.Idle.AssassinIdle", false);
}



/**
 * Override functions
 */

void UPlayerHumanState_AssassinIdle::EnterState()
{
	Super::EnterState();
	m_CharPlayerHuman_Owner->SetControlRigFootIKAlpha(1.0f, 0.75f);
}

void UPlayerHumanState_AssassinIdle::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (FMath::Abs(m_MoveForwardValue) > 0.1f || FMath::Abs(m_MoveRightValue) > 0.1f)
	{
		ChangeState("PlayerHumanState_AssassinJog");
	}
}

void UPlayerHumanState_AssassinIdle::ExitState()
{
	Super::ExitState();
	m_CharPlayerHuman_Owner->SetControlRigFootIKAlpha(0.0f, 0.25f);
}



/**
 * Public member functions
 */

void UPlayerHumanState_AssassinIdle::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput != nullptr)
	{
		m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
		m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
		m_JumpPressed_DelegateREF = IPlayerInput->GetDelegate_JumpPressed();
		m_DashStart_DelegateREF = IPlayerInput->GetDelegate_DashStart();
		m_LightAttack_DelegateREF = IPlayerInput->GetDelegate_LightAttackStart();
		m_HeavyAttack_DelegateREF = IPlayerInput->GetDelegate_HeavyAttackStart();

		if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinIdle::HandleInput_MoveForward);
		if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinIdle::HandleInput_MoveRight);
		if (m_JumpPressed_DelegateREF != nullptr) m_JumpPressed_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinIdle::HandleInput_JumpPressed);
		if (m_DashStart_DelegateREF != nullptr) m_DashStart_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinIdle::HandleAction_DashStart);
		if (m_LightAttack_DelegateREF != nullptr) m_LightAttack_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinIdle::HandleAction_LightAttack);
		if (m_HeavyAttack_DelegateREF != nullptr) m_HeavyAttack_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinIdle::HandleAction_HeavyAttackStart);
	}
}

void UPlayerHumanState_AssassinIdle::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);
	if (m_JumpPressed_DelegateREF != nullptr) m_JumpPressed_DelegateREF->RemoveAll(this);
	if (m_DashStart_DelegateREF != nullptr) m_DashStart_DelegateREF->RemoveAll(this);
	if (m_LightAttack_DelegateREF != nullptr) m_LightAttack_DelegateREF->RemoveAll(this);
	if (m_HeavyAttack_DelegateREF != nullptr) m_HeavyAttack_DelegateREF->RemoveAll(this);

	m_MoveForward_DelegateREF = nullptr;
	m_MoveRight_DelegateREF = nullptr;
	m_JumpPressed_DelegateREF = nullptr;
	m_DashStart_DelegateREF = nullptr;
	m_LightAttack_DelegateREF = nullptr;
	m_HeavyAttack_DelegateREF = nullptr;
}



/**
 * Private Member Functions
 */

void UPlayerHumanState_AssassinIdle::HandleInput_MoveForward(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_AxisValue;
}

void UPlayerHumanState_AssassinIdle::HandleInput_MoveRight(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_AxisValue;
}

void UPlayerHumanState_AssassinIdle::HandleInput_JumpPressed()
{
	if (!b_IsInState) return;
	ChangeState("PlayerHumanState_AssassinJump");
}

void UPlayerHumanState_AssassinIdle::HandleAction_DashStart()
{
	if (!b_IsInState) return;
	if ((m_CharPlayerHuman_Owner->m_AssassinDashState)->CheckForHoldingAfterExit(c_Dash2_HoldingTime)) ChangeState("PlayerHumanState_AssassinDash_2");
	else ChangeState("PlayerHumanState_AssassinDash");
}

void UPlayerHumanState_AssassinIdle::HandleAction_LightAttack()
{
	if (!b_IsInState) return;
	ChangeState("PlayerHumanState_AssassinLA_C1_1");
}

void UPlayerHumanState_AssassinIdle::HandleAction_HeavyAttackStart()
{
	if (!b_IsInState) return;
	if (m_CharPlayerHuman_Owner->b_IsBuffingWeapon_01) ChangeState("PlayerHumanState_AssassinHA_C3_1");
	else ChangeState("PlayerHumanState_AssassinHA_C2_1");
}
