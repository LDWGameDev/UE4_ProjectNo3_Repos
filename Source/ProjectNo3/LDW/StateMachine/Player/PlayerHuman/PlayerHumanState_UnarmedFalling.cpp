// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_UnarmedFalling.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


UPlayerHumanState_UnarmedFalling::UPlayerHumanState_UnarmedFalling()
{
	m_StateID = FString(TEXT("PlayerHumanState_UnarmedFalling"));
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.Falling.UnarmedFalling", false);
}

void UPlayerHumanState_UnarmedFalling::EnterState()
{
	Super::EnterState();
	(m_CharPlayerHuman_Owner->GetCharacterMovement())->MaxWalkSpeed = c_MovingSpeed;
}

void UPlayerHumanState_UnarmedFalling::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	m_CharPlayerHuman_Owner->MoveCharacter(m_MoveForwardValue, m_MoveRightValue);
	if (b_HasLanded) 
	{
		if (FMath::Abs(m_MoveForwardValue) > 0.01f || (FMath::Abs(m_MoveRightValue) > 0.01f)) ChangeState("PlayerHumanState_UnarmedJog");
		else ChangeState("PlayerHumanState_UnarmedIdle");
	}
}

void UPlayerHumanState_UnarmedFalling::ExitState()
{
	Super::ExitState();
	m_CharPlayerHuman_Owner->PlayMontageFromTable("Unarmed_Land_Additive");
	b_HasLanded = false;
}


/**
 * Bind input Functions
 */

void UPlayerHumanState_UnarmedFalling::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput != nullptr && m_CharPlayerHuman_Owner != nullptr)
	{
		m_MoveForwardDelegateREF = IPlayerInput->GetDelegate_MoveForward();
		m_MoveRightDelegateREF = IPlayerInput->GetDelegate_MoveRight();
		m_Landed_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_Landed);

		if (m_MoveForwardDelegateREF != nullptr) m_MoveForwardDelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedFalling::HandleInput_MoveForward);
		if (m_MoveRightDelegateREF != nullptr) m_MoveRightDelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedFalling::HandleInput_MoveRight);
		if (m_Landed_DelegateREF != nullptr) m_Landed_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedFalling::HandleEvent_Landed);
	}
}

void UPlayerHumanState_UnarmedFalling::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForwardDelegateREF != nullptr) m_MoveForwardDelegateREF->RemoveAll(this);
	if (m_MoveRightDelegateREF != nullptr) m_MoveRightDelegateREF->RemoveAll(this);
	if (m_Landed_DelegateREF != nullptr) m_MoveRightDelegateREF->RemoveAll(this);
}

void UPlayerHumanState_UnarmedFalling::HandleInput_MoveForward(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_AxisValue;
}

void UPlayerHumanState_UnarmedFalling::HandleInput_MoveRight(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_AxisValue;
}

void UPlayerHumanState_UnarmedFalling::HandleEvent_Landed()
{
	if (!b_IsInState) return;
	m_CharPlayerHuman_Owner->PlayMontageFromTable("Unarmed_Land_Additive");
	b_HasLanded = true;
	if (FMath::Abs(m_MoveForwardValue) > 0.01f || (FMath::Abs(m_MoveRightValue) > 0.01f)) ChangeState("PlayerHumanState_UnarmedJog");
	else ChangeState("PlayerHumanState_UnarmedIdle");
}