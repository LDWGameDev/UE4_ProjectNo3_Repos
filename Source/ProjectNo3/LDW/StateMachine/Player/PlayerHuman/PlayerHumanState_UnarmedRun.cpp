// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_UnarmedRun.h"
#include "GameplayTagContainer.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


UPlayerHumanState_UnarmedRun::UPlayerHumanState_UnarmedRun()
{
	m_StateID = FString(TEXT("PlayerHumanState_UnarmedRun"));
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Locomotion.Run.UnarmedRun", false);
}

void UPlayerHumanState_UnarmedRun::EnterState()
{
	Super::EnterState();
	(m_CharPlayerHuman_Owner->GetCharacterMovement())->MaxWalkSpeed = c_DefaultRunSpeed;
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(c_TargetArmLengthFollow_01, 1.0f);
}

void UPlayerHumanState_UnarmedRun::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	m_CharPlayerHuman_Owner->MoveCharacter(m_MoveForwardValue, m_MoveRightValue);
	if (m_CharPlayerHuman_Owner->GetMovingSpeed() < c_SpeedToStop && FMath::Abs(m_MoveForwardValue) < 0.01f && FMath::Abs(m_MoveRightValue) < 0.01f)
	{
		ChangeState(FString(TEXT("PlayerHumanState_UnarmedJog")));
	}
	else if (!b_IsHoldingRunKey)
	{
		ChangeState(FString(TEXT("PlayerHumanState_UnarmedJog")));
	}
}

void UPlayerHumanState_UnarmedRun::ExitState()
{
	Super::ExitState();
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 1.0f);
}



/**
 * Public member functions
 */

void UPlayerHumanState_UnarmedRun::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput == nullptr || m_CharPlayerHuman_Owner == nullptr) return;
	m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
	m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
	m_JumpPressed_DelegateREF = IPlayerInput->GetDelegate_JumpPressed();
	m_StartFalling_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_StartFalling);
	m_RunStart_DelegateREF = IPlayerInput->GetDelegate_RunStart();
	m_RunEnd_DelegateREF = IPlayerInput->GetDelegate_RunEnd();

	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedRun::HandleInput_MoveForward);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedRun::HandleInput_MoveRight);
	if (m_JumpPressed_DelegateREF != nullptr) m_JumpPressed_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedRun::HandleInput_JumpPressed);
	if (m_StartFalling_DelegateREF != nullptr) m_StartFalling_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedRun::HandleEvent_StartFalling);
	if (m_RunStart_DelegateREF != nullptr) m_RunStart_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedRun::HandleAction_RunStart);
	if (m_RunEnd_DelegateREF != nullptr) m_RunEnd_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedRun::HandleAction_RunEnd);
}

void UPlayerHumanState_UnarmedRun::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);
	if (m_JumpPressed_DelegateREF != nullptr) m_JumpPressed_DelegateREF->RemoveAll(this);
	if (m_StartFalling_DelegateREF != nullptr) m_StartFalling_DelegateREF->RemoveAll(this);
	if (m_RunStart_DelegateREF != nullptr) m_RunStart_DelegateREF->RemoveAll(this);
	if (m_RunEnd_DelegateREF != nullptr) m_RunEnd_DelegateREF->RemoveAll(this);
}



/**
 * Private member functions
 */


void UPlayerHumanState_UnarmedRun::HandleInput_MoveForward(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_AxisValue;
}

void UPlayerHumanState_UnarmedRun::HandleInput_MoveRight(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_AxisValue;
}

void UPlayerHumanState_UnarmedRun::HandleInput_JumpPressed()
{
	if (!b_IsInState) return;
	ChangeState(FString(TEXT("PlayerHumanState_UnarmedJump")));
}

void UPlayerHumanState_UnarmedRun::HandleEvent_StartFalling()
{
	if (!b_IsInState) return;
	ChangeState(FString(TEXT("PlayerHumanState_UnarmedFalling")));
}

void UPlayerHumanState_UnarmedRun::HandleAction_RunStart()
{
	b_IsHoldingRunKey = true;
}

void UPlayerHumanState_UnarmedRun::HandleAction_RunEnd()
{
	b_IsHoldingRunKey = false;
}
