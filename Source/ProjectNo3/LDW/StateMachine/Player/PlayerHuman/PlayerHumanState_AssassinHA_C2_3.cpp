// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinHA_C2_3.h"
#include "GameFramework/CharacterMovementComponent.h"



UPlayerHumanState_AssassinHA_C2_3::UPlayerHumanState_AssassinHA_C2_3()
{
	m_StateID = TEXT("PlayerHumanState_AssassinHA_C2_3");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.HeavyAttack.AssassinHeavyAttack_Combo2_Phase3", false);
	b_CanBreakOut = false;
}



/**
 * Override functions
 */

void UPlayerHumanState_AssassinHA_C2_3::EnterState()
{
	Super::EnterState();
	(m_CharPlayerHuman_Owner->GetCharacterMovement())->SetMovementMode(EMovementMode::MOVE_Flying, 0);
	m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_HeavyAttack_C2_3")));
	SetCameraFollow_01(c_AdditionArmLength, c_SocketOffset, 0.75f, -20.0f, 60.0f, FVector(0.0f, -40.0f, 0.0f), FVector(0.0f, -40.0f, 0.0f));
}

void UPlayerHumanState_AssassinHA_C2_3::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (b_CanBreakOut && b_HasTriggerHeavyAttack)
	{
		b_CanBreakOut = false;
		b_HasTriggerHeavyAttack = false;
		ChangeState("PlayerHumanState_AssassinHA_C2_4");
	}
}

void UPlayerHumanState_AssassinHA_C2_3::ExitState()
{
	Super::ExitState();
	(m_CharPlayerHuman_Owner->GetCharacterMovement())->SetMovementMode(EMovementMode::MOVE_Walking, 0);
	b_CanBreakOut = false;
	b_HasTriggerHeavyAttack = false;
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 2.0f);
}




/**
 * Public member functions
 */

void UPlayerHumanState_AssassinHA_C2_3::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput == nullptr) return;
	m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
	m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
	m_HeavyAttackStart_DelegateREF = IPlayerInput->GetDelegate_HeavyAttackStart();
	m_AnimNotify_01_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_AnimNotify_01);
	m_EndAttack_01_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_EndAttack_01);

	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C2_3::HandleAction_MoveForward);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C2_3::HandleAction_MoveRight);
	if (m_HeavyAttackStart_DelegateREF != nullptr) m_HeavyAttackStart_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C2_3::HandleAction_HeavyAttackStart);
	if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C2_3::HandleAction_AnimNotify_01);
	if (m_EndAttack_01_DelegateREF != nullptr) m_EndAttack_01_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C2_3::HandleAction_EndAttack_01);

}

void UPlayerHumanState_AssassinHA_C2_3::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);
	if (m_HeavyAttackStart_DelegateREF != nullptr) m_HeavyAttackStart_DelegateREF->RemoveAll(this);
	if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->RemoveAll(this);
	if (m_EndAttack_01_DelegateREF != nullptr) m_EndAttack_01_DelegateREF->RemoveAll(this);

	m_MoveForward_DelegateREF = nullptr;
	m_MoveRight_DelegateREF = nullptr;
	m_HeavyAttackStart_DelegateREF = nullptr;
	m_AnimNotify_01_DelegateREF = nullptr;
	m_EndAttack_01_DelegateREF = nullptr;
}




/**
 * Private member functions
 */

void UPlayerHumanState_AssassinHA_C2_3::HandleAction_MoveForward(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_Value;
}

void UPlayerHumanState_AssassinHA_C2_3::HandleAction_MoveRight(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_Value;
}

void UPlayerHumanState_AssassinHA_C2_3::HandleAction_HeavyAttackStart()
{
	if (!b_IsInState) return;
	b_HasTriggerHeavyAttack = true;
}

void UPlayerHumanState_AssassinHA_C2_3::HandleAction_AnimNotify_01()
{
	if (!b_IsInState) return;
	b_CanBreakOut = true;
}

void UPlayerHumanState_AssassinHA_C2_3::HandleAction_EndAttack_01()
{
	if (!b_IsInState) return;
	if (FMath::Abs(m_MoveForwardValue) > 0.1f || FMath::Abs(m_MoveRightValue) > 0.1f)
	{
	m_CharPlayerHuman_Owner->StopAnimMontage();
	m_CharPlayerHuman_Owner->DisableRootMotionForTime(0.1f);
	ChangeState("PlayerHumanState_AssassinJog");
	}
	else ChangeState("PlayerHumanState_AssassinIdle");
}