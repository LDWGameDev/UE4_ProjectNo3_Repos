// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinHA_C2_4.h"


UPlayerHumanState_AssassinHA_C2_4::UPlayerHumanState_AssassinHA_C2_4()
{
	m_StateID = TEXT("PlayerHumanState_AssassinHA_C2_4");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.HeavyAttack.AssassinHeavyAttack_Combo2_Phase4", false);
	b_CanBreakOut = false;
	b_CameraSequenceValid = true;
}



/**
 * Override functions
 */

void UPlayerHumanState_AssassinHA_C2_4::EnterState()
{
	Super::EnterState();
	if (b_CameraSequenceValid)
	{
		m_CharPlayerHuman_Owner->PlayMontageFromTable(FName("Assassin_HeavyAttack_C2_4"));
		m_CharPlayerHuman_Owner->SetViewToCameraSequence(FName(TEXT("Sequence_HA_C2_4")), true);
	}
	else
	{
		m_CharPlayerHuman_Owner->PlayMontageFromTable(FName("Assassin_HeavyAttack_C2_4_Type2"));
		SetCameraFollow_01(c_AdditionArmLength, c_SocketOffset, 0.75f, -20.0f, 80.0f, FVector(0.0f, -50.0f, 0.0f), FVector(0.0f, -50.0f, 0.0f));
	}
}

void UPlayerHumanState_AssassinHA_C2_4::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (b_CanBreakOut)
	{
		b_CanBreakOut = false;
	}
}

void UPlayerHumanState_AssassinHA_C2_4::ExitState()
{
	Super::ExitState();
	b_CanBreakOut = false;
	if(!b_CameraSequenceValid) m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 2.0f);
}




/**
 * Public member functions
 */

void UPlayerHumanState_AssassinHA_C2_4::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput == nullptr) return;
	m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
	m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
	m_AnimNotify_01_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_AnimNotify_01);
	m_EndAttack_02_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_EndAttack_02);

	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C2_4::HandleAction_MoveForward);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C2_4::HandleAction_MoveRight);
	if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C2_4::HandleAction_AnimNotify_01);
	if (m_EndAttack_02_DelegateREF != nullptr) m_EndAttack_02_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C2_4::HandleAction_EndAttack_02);

}

void UPlayerHumanState_AssassinHA_C2_4::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->RemoveAll(this);
	if (m_EndAttack_02_DelegateREF != nullptr) m_EndAttack_02_DelegateREF->RemoveAll(this);

	m_MoveForward_DelegateREF = nullptr;
	m_MoveRight_DelegateREF = nullptr;
	m_AnimNotify_01_DelegateREF = nullptr;
	m_EndAttack_02_DelegateREF = nullptr;
}




/**
 * Private member functions
 */

void UPlayerHumanState_AssassinHA_C2_4::HandleAction_MoveForward(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_Value;
}

void UPlayerHumanState_AssassinHA_C2_4::HandleAction_MoveRight(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_Value;
}

void UPlayerHumanState_AssassinHA_C2_4::HandleAction_AnimNotify_01()
{
	if (!b_IsInState) return;
	b_CanBreakOut = true;
}

void UPlayerHumanState_AssassinHA_C2_4::HandleAction_EndAttack_02()
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