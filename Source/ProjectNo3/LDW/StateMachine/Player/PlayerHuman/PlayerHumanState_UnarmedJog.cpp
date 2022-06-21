// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_UnarmedJog.h"
#include "GameplayTagContainer.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


UPlayerHumanState_UnarmedJog::UPlayerHumanState_UnarmedJog()
{
	m_StateID = FString(TEXT("PlayerHumanState_UnarmedJog"));
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Locomotion.Jog.UnarmedJog", false);
}

void UPlayerHumanState_UnarmedJog::EnterState()
{
	Super::EnterState();
	(m_CharPlayerHuman_Owner->GetCharacterMovement())->MaxWalkSpeed = c_MovingSpeed;
}

void UPlayerHumanState_UnarmedJog::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	m_CharPlayerHuman_Owner->MoveCharacter(m_MoveForwardValue, m_MoveRightValue);
	if (m_CharPlayerHuman_Owner->GetMovingSpeed() < m_SpeedToStop && FMath::Abs(m_MoveForwardValue) < 0.01f && FMath::Abs(m_MoveRightValue) < 0.01f)
	{
		ChangeState(FString(TEXT("PlayerHumanState_UnarmedIdle")));
	}
	else if (b_IsHoldingRunKey)
	{
		ChangeState(FString(TEXT("PlayerHumanState_UnarmedRun")));
	}
}

void UPlayerHumanState_UnarmedJog::ExitState()
{
	Super::ExitState();
}



/**
 * Input Functions
 */

void UPlayerHumanState_UnarmedJog::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput == nullptr || m_CharPlayerHuman_Owner == nullptr) return;
	m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
	m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
	m_JumpPressed_DelegateREF = IPlayerInput->GetDelegate_JumpPressed();
	m_StartFalling_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_StartFalling);
	m_DashStart_DelegateREF = IPlayerInput->GetDelegate_DashStart();
	m_RunStart_DelegateREF = IPlayerInput->GetDelegate_RunStart();
	m_RunEnd_DelegateREF = IPlayerInput->GetDelegate_RunEnd();

	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedJog::HandleInput_MoveForward);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedJog::HandleInput_MoveRight);
	if (m_JumpPressed_DelegateREF != nullptr) m_JumpPressed_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedJog::HandleInput_JumpPressed);
	if (m_StartFalling_DelegateREF != nullptr) m_StartFalling_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedJog::HandleEvent_StartFalling);
	if (m_DashStart_DelegateREF != nullptr) m_DashStart_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedJog::HandleAction_DashStart);
	if (m_RunStart_DelegateREF != nullptr) m_RunStart_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedJog::HandleAction_RunStart);
	if (m_RunEnd_DelegateREF != nullptr) m_RunEnd_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedJog::HandleAction_RunEnd);

}

void UPlayerHumanState_UnarmedJog::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);
	if (m_JumpPressed_DelegateREF != nullptr) m_JumpPressed_DelegateREF->RemoveAll(this);
	if (m_StartFalling_DelegateREF != nullptr) m_StartFalling_DelegateREF->RemoveAll(this);
	if (m_DashStart_DelegateREF != nullptr) m_DashStart_DelegateREF->RemoveAll(this);
	if (m_RunStart_DelegateREF != nullptr) m_RunStart_DelegateREF->RemoveAll(this);
	if (m_RunEnd_DelegateREF != nullptr) m_RunEnd_DelegateREF->RemoveAll(this);
}

void UPlayerHumanState_UnarmedJog::HandleInput_MoveForward(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_AxisValue;
}

void UPlayerHumanState_UnarmedJog::HandleInput_MoveRight(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_AxisValue;
}

void UPlayerHumanState_UnarmedJog::HandleInput_JumpPressed()
{
	if (!b_IsInState) return;
	ChangeState(FString(TEXT("PlayerHumanState_UnarmedJump")));
}

void UPlayerHumanState_UnarmedJog::HandleEvent_StartFalling()
{
	if (!b_IsInState) return;
	ChangeState(FString(TEXT("PlayerHumanState_UnarmedFalling")));
}

void UPlayerHumanState_UnarmedJog::HandleAction_DashStart()
{
	if (!b_IsInState) return;
	ChangeState(FString(TEXT("PlayerHumanState_UnarmedDash")));
}

void UPlayerHumanState_UnarmedJog::HandleAction_RunStart()
{
	b_IsHoldingRunKey = true;
}

void UPlayerHumanState_UnarmedJog::HandleAction_RunEnd()
{
	b_IsHoldingRunKey = false;
}