// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinFalling.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerHumanState_AssassinFalling::UPlayerHumanState_AssassinFalling()
{
	m_StateID = TEXT("PlayerHumanState_AssassinFalling");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.Falling.AssassinFalling", false);
}



/**
 * Override functions
 */

void UPlayerHumanState_AssassinFalling::EnterState()
{
	Super::EnterState();
	(m_CharPlayerHuman_Owner->GetCharacterMovement())->MaxWalkSpeed = c_MovingSpeed;
}

void UPlayerHumanState_AssassinFalling::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	m_CharPlayerHuman_Owner->MoveCharacter(m_MoveForwardValue, m_MoveRightValue);
	if (b_HasLanded)
	{
		if (FMath::Abs(m_MoveForwardValue) > 0.1f || FMath::Abs(m_MoveRightValue) > 0.1f) ChangeState(TEXT("PlayerHumanState_AssassinJog"));
		else ChangeState(TEXT("PlayerHumanState_AssassinIdle"));
	}
}

void UPlayerHumanState_AssassinFalling::ExitState()
{
	Super::ExitState();
	b_HasLanded = false;
	m_CharPlayerHuman_Owner->PlayMontageFromTable("Assassin_LandAdditive");
}



/**
 * Public member functions
 */

void UPlayerHumanState_AssassinFalling::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput != nullptr)
	{
		m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
		m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
		m_Landed_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_Landed);

		if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinFalling::HandleInput_MoveForward);
		if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinFalling::HandleInput_MoveRight);
		if (m_Landed_DelegateREF != nullptr) m_Landed_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinFalling::HandleAction_Landed);
	}
}

void UPlayerHumanState_AssassinFalling::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);
	if (m_Landed_DelegateREF != nullptr) m_Landed_DelegateREF->RemoveAll(this);

	m_MoveForward_DelegateREF = nullptr;
	m_MoveRight_DelegateREF = nullptr;
	m_Landed_DelegateREF = nullptr;
}




/**
 * Private Member Functions
 */

void UPlayerHumanState_AssassinFalling::HandleInput_MoveForward(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_AxisValue;
}

void UPlayerHumanState_AssassinFalling::HandleInput_MoveRight(float p_AxisValue)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_AxisValue;
}

void UPlayerHumanState_AssassinFalling::HandleAction_Landed()
{
	if (!b_IsInState) return;
	b_HasLanded = true;
}