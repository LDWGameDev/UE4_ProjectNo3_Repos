// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_UnarmedJump.h"
#include "GameplayTagContainer.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


UPlayerHumanState_UnarmedJump::UPlayerHumanState_UnarmedJump()
{
	m_StateID = FString(TEXT("PlayerHumanState_UnarmedJump"));
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.Jump.UnarmedJump", false);
}

void UPlayerHumanState_UnarmedJump::EnterState()
{
	Super::EnterState();
	m_CharPlayerHuman_Owner->LaunchCharacter(FVector::UpVector * c_DefaultJumpForce, false, true);
	(m_CharPlayerHuman_Owner->GetCharacterMovement())->MaxWalkSpeed = c_DefaultMovingSpeed;
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(c_AdditionalArmLengthFollow_01, 0.5f);
	m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Unarmed_Jump")));
}

void UPlayerHumanState_UnarmedJump::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	m_CharPlayerHuman_Owner->MoveCharacter(m_MoveForwardValue, m_MoveRightValue);
}

void UPlayerHumanState_UnarmedJump::ExitState()
{
	Super::ExitState();
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 0.5f);
}



/**
 * Handles input Functions
 */

void UPlayerHumanState_UnarmedJump::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput != nullptr && m_CharPlayerHuman_Owner != nullptr)
	{
		m_MoveForwardDelegateREF = IPlayerInput->GetDelegate_MoveForward();
		m_MoveRightDelegateREF = IPlayerInput->GetDelegate_MoveRight();
		m_Landed_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_Landed);
		m_EndMontage_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_EndMontage);

		if (m_MoveForwardDelegateREF != nullptr) m_MoveForwardDelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedJump::HandleInput_MoveForward);
		if (m_MoveRightDelegateREF != nullptr) m_MoveRightDelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedJump::HandleInput_MoveRight);
		if (m_Landed_DelegateREF != nullptr) m_Landed_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedJump::HandleEvent_Landed);
		if (m_EndMontage_DelegateREF != nullptr) m_EndMontage_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedJump::HandleEvent_EndAction);
	}
}

void UPlayerHumanState_UnarmedJump::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForwardDelegateREF != nullptr) m_MoveForwardDelegateREF->RemoveAll(this);
	if (m_MoveRightDelegateREF != nullptr) m_MoveRightDelegateREF->RemoveAll(this);
	if (m_Landed_DelegateREF != nullptr) m_MoveRightDelegateREF->RemoveAll(this);
	if (m_EndMontage_DelegateREF != nullptr) m_EndMontage_DelegateREF->RemoveAll(this);
}

void UPlayerHumanState_UnarmedJump::HandleInput_MoveForward(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_AxisValue;
}

void UPlayerHumanState_UnarmedJump::HandleInput_MoveRight(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_AxisValue;
}

void UPlayerHumanState_UnarmedJump::HandleEvent_Landed()
{
	if (!b_IsInState) return;
	m_CharPlayerHuman_Owner->PlayMontageFromTable("Unarmed_Land_Additive");
	if (FMath::Abs(m_MoveForwardValue) > 0.01f || (FMath::Abs(m_MoveRightValue) > 0.01f)) ChangeState("PlayerHumanState_UnarmedJog");
	else ChangeState("PlayerHumanState_UnarmedIdle");
}

void UPlayerHumanState_UnarmedJump::HandleEvent_EndAction()
{
	if (!b_IsInState) return;
	ChangeState("PlayerHumanState_UnarmedFalling");
}