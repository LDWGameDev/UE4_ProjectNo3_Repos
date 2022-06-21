// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinJog.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerHumanState_AssassinDash.h"


UPlayerHumanState_AssassinJog::UPlayerHumanState_AssassinJog()
{
	m_StateID = TEXT("PlayerHumanState_AssassinJog");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Locomotion.Jog.AssassinJog", false);
}


/**
 * Override functions
 */

void UPlayerHumanState_AssassinJog::EnterState()
{
	Super::EnterState();
	(m_CharPlayerHuman_Owner->GetCharacterMovement())->MaxWalkSpeed = c_MovingSpeed;
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(c_AdditionalArmLength_01, 1.0f);
}

void UPlayerHumanState_AssassinJog::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	m_CharPlayerHuman_Owner->MoveCharacter(m_MoveForwardValue, m_MoveRightValue);
	if (FMath::Abs(m_MoveForwardValue) < 0.1f && FMath::Abs(m_MoveRightValue) < 0.1f && m_CharPlayerHuman_Owner->GetMovingSpeed() < c_StoppingSpeed)
	{
		ChangeState(TEXT("PlayerHumanState_AssassinIdle"));

	}
	else if (b_IsHoldingRunKey) 
	{
		ChangeState(TEXT("PlayerHumanState_AssassinRun"));
	}
}

void UPlayerHumanState_AssassinJog::ExitState()
{
	Super::ExitState();
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 2.0f);
}


/**
 * Public member functions
 */

void UPlayerHumanState_AssassinJog::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput != nullptr)
	{
		m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
		m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
		m_JumpPressed_DelegateREF = IPlayerInput->GetDelegate_JumpPressed();
		m_DashStart_DelegateREF = IPlayerInput->GetDelegate_DashStart();
		m_RunStart_DelegateREF = IPlayerInput->GetDelegate_RunStart();
		m_RunEnd_DelegateREF = IPlayerInput->GetDelegate_RunEnd();
		m_LightAttackStart_DelegateREF = IPlayerInput->GetDelegate_LightAttackStart();
		m_HeavyAttackStart_DelegateREF = IPlayerInput->GetDelegate_HeavyAttackStart();
		m_StartFalling_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_StartFalling);

		if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinJog::HandleInput_MoveForward);
		if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinJog::HandleInput_MoveRight);
		if (m_JumpPressed_DelegateREF != nullptr) m_JumpPressed_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinJog::HandleInput_JumpPressed);
		if (m_DashStart_DelegateREF != nullptr) m_DashStart_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinJog::HandleAction_DashStart);
		if (m_RunStart_DelegateREF != nullptr) m_RunStart_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinJog::HandleAction_RunStart);
		if (m_RunEnd_DelegateREF != nullptr) m_RunEnd_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinJog::HandleAction_RunEnd);
		if (m_StartFalling_DelegateREF != nullptr) m_StartFalling_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinJog::HandleAction_StartFalling);
		if (m_LightAttackStart_DelegateREF != nullptr) m_LightAttackStart_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinJog::HandleAction_LightAttackStart);
		if (m_HeavyAttackStart_DelegateREF != nullptr) m_HeavyAttackStart_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinJog::HandleAction_HeavyAttackStart);
	}
}

void UPlayerHumanState_AssassinJog::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);
	if (m_JumpPressed_DelegateREF != nullptr) m_JumpPressed_DelegateREF->RemoveAll(this);
	if (m_DashStart_DelegateREF != nullptr) m_DashStart_DelegateREF->RemoveAll(this);
	if (m_RunStart_DelegateREF != nullptr) m_RunStart_DelegateREF->RemoveAll(this);
	if (m_RunEnd_DelegateREF != nullptr) m_RunEnd_DelegateREF->RemoveAll(this);
	if (m_StartFalling_DelegateREF != nullptr) m_StartFalling_DelegateREF->RemoveAll(this);
	if (m_LightAttackStart_DelegateREF != nullptr) m_LightAttackStart_DelegateREF->RemoveAll(this);
	if (m_HeavyAttackStart_DelegateREF != nullptr) m_HeavyAttackStart_DelegateREF->RemoveAll(this);

	m_MoveForward_DelegateREF = nullptr;
	m_MoveRight_DelegateREF = nullptr;
	m_JumpPressed_DelegateREF = nullptr;
	m_DashStart_DelegateREF = nullptr;
	m_RunStart_DelegateREF = nullptr;
	m_RunEnd_DelegateREF = nullptr;
	m_StartFalling_DelegateREF = nullptr;
	m_LightAttackStart_DelegateREF = nullptr;
	m_HeavyAttackStart_DelegateREF = nullptr;
}



/**
 * Private Member Functions
 */

void UPlayerHumanState_AssassinJog::HandleInput_MoveForward(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_AxisValue;
}

void UPlayerHumanState_AssassinJog::HandleInput_MoveRight(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_AxisValue;
}

void UPlayerHumanState_AssassinJog::HandleInput_JumpPressed()
{
	if (!b_IsInState) return;
	ChangeState("PlayerHumanState_AssassinJump");
}

void UPlayerHumanState_AssassinJog::HandleAction_DashStart()
{
	if (!b_IsInState) return;
	if ((m_CharPlayerHuman_Owner->m_AssassinDashState)->CheckForHoldingAfterExit(c_Dash2_HoldingTime)) ChangeState("PlayerHumanState_AssassinDash_2");
	else ChangeState("PlayerHumanState_AssassinDash");
}

void UPlayerHumanState_AssassinJog::HandleAction_RunStart()
{
	b_IsHoldingRunKey = true;
}

void UPlayerHumanState_AssassinJog::HandleAction_RunEnd()
{
	b_IsHoldingRunKey = false;
}

void UPlayerHumanState_AssassinJog::HandleAction_StartFalling()
{
	if (!b_IsInState) return;
	ChangeState("PlayerHumanState_AssassinFalling");
}

void UPlayerHumanState_AssassinJog::HandleAction_LightAttackStart()
{
	if (!b_IsInState) return;
	ChangeState("PlayerHumanState_AssassinLA_C1_1");
}

void UPlayerHumanState_AssassinJog::HandleAction_HeavyAttackStart()
{
	if (!b_IsInState) return;
	if (m_CharPlayerHuman_Owner->b_IsBuffingWeapon_01) ChangeState("PlayerHumanState_AssassinHA_C3_1");
	else ChangeState("PlayerHumanState_AssassinHA_C2_1");
}