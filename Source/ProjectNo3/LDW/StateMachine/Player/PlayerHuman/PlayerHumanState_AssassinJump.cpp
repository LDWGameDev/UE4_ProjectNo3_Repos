// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinJump.h"


UPlayerHumanState_AssassinJump::UPlayerHumanState_AssassinJump()
{
	m_StateID = TEXT("PlayerHumanState_AssassinJump");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.Jump.AssassinJump", false);
}




/**
 * Override functions
 */

void UPlayerHumanState_AssassinJump::EnterState()
{
	Super::EnterState();
	m_CharPlayerHuman_Owner->LaunchCharacter(FVector::UpVector * c_JumpForce, false, true);
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(c_ArmLengthFollow_01, 0.5f);
	m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_Jump")));
}

void UPlayerHumanState_AssassinJump::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	m_CharPlayerHuman_Owner->MoveCharacter(m_MoveForwardValue, m_MoveRightValue);
}

void UPlayerHumanState_AssassinJump::ExitState()
{
	Super::ExitState();
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 0.75f);
}




/**
 * Public member functions
 */

void UPlayerHumanState_AssassinJump::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput != nullptr && m_CharPlayerHuman_Owner != nullptr)
	{
		m_MoveForwardDelegateREF = IPlayerInput->GetDelegate_MoveForward();
		m_MoveRightDelegateREF = IPlayerInput->GetDelegate_MoveRight();
		m_Landed_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_Landed);
		m_EndMontage_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_EndMontage);

		if (m_MoveForwardDelegateREF != nullptr) m_MoveForwardDelegateREF->AddUObject(this, &UPlayerHumanState_AssassinJump::HandleInput_MoveForward);
		if (m_MoveRightDelegateREF != nullptr) m_MoveRightDelegateREF->AddUObject(this, &UPlayerHumanState_AssassinJump::HandleInput_MoveRight);
		if (m_Landed_DelegateREF != nullptr) m_Landed_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinJump::HandleEvent_Landed);
		if (m_EndMontage_DelegateREF != nullptr) m_EndMontage_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinJump::HandleEvent_EndAction);
	}
}

void UPlayerHumanState_AssassinJump::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForwardDelegateREF != nullptr) m_MoveForwardDelegateREF->RemoveAll(this);
	if (m_MoveRightDelegateREF != nullptr) m_MoveRightDelegateREF->RemoveAll(this);
	if (m_Landed_DelegateREF != nullptr) m_MoveRightDelegateREF->RemoveAll(this);
	if (m_EndMontage_DelegateREF != nullptr) m_EndMontage_DelegateREF->RemoveAll(this);
}




/**
 * Private member functions
 */

void UPlayerHumanState_AssassinJump::HandleInput_MoveForward(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_AxisValue;
}

void UPlayerHumanState_AssassinJump::HandleInput_MoveRight(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_AxisValue;
}

void UPlayerHumanState_AssassinJump::HandleEvent_Landed()
{
	if (!b_IsInState) return;
	m_CharPlayerHuman_Owner->PlayMontageFromTable("Assassin_LandAdditive");
	if (FMath::Abs(m_MoveForwardValue) > 0.01f || (FMath::Abs(m_MoveRightValue) > 0.01f)) ChangeState("PlayerHumanState_AssassinJog");
	else ChangeState("PlayerHumanState_AssassinIdle");
}

void UPlayerHumanState_AssassinJump::HandleEvent_EndAction()
{
	if (!b_IsInState) return;
	ChangeState("PlayerHumanState_AssassinFalling");
}