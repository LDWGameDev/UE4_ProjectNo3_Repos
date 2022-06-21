// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinLA_C1_2.h"


UPlayerHumanState_AssassinLA_C1_2::UPlayerHumanState_AssassinLA_C1_2()
{
	m_StateID = TEXT("PlayerHumanState_AssassinLA_C1_2");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.LightAttack.AssassinLightAttack_Combo1_Phase2", false);
	m_CooldownTime = c_CooldownTime;
	b_HasTriggerLightAttack = false;
	b_CanBreakOut = false;
}



/**
 * Override functions
 */

void UPlayerHumanState_AssassinLA_C1_2::EnterState()
{
	Super::EnterState();
	m_CharPlayerHuman_Owner->PlayMontageFromTable("Assassin_LightAttack_C1_2");
	SetCameraFollow_01(c_AdditionArmLength, c_SocketOffset, 0.5f, -10.0f, 30.0f, FVector(0.0f, -20.0f, 0.0f), FVector(0.0f, -20.0f, 0.0f));
}

void UPlayerHumanState_AssassinLA_C1_2::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (b_CanBreakOut)
	{
		if (b_HasTriggerLightAttack)
		{
			b_CanBreakOut = false;
			b_HasTriggerLightAttack = false;
			ChangeState("PlayerHumanState_AssassinLA_C1_3");
		}
		else if (b_HasTriggerHeavyAttack)
		{
			b_CanBreakOut = false;
			b_HasTriggerHeavyAttack = false;
			ChangeState("PlayerHumanState_AssassinHA_C1_1");
		}
	}
}

void UPlayerHumanState_AssassinLA_C1_2::ExitState()
{
	Super::ExitState();
	b_CanBreakOut = false;
	b_HasTriggerLightAttack = false;
	b_HasTriggerHeavyAttack = false;
	(m_CharPlayerHuman_Owner->m_AssassinLightAttack_C1_1)->SetExitStateTimeToNow();
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 2.0f);
}





/**
 * Public member functions
 */

void UPlayerHumanState_AssassinLA_C1_2::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput == nullptr) return;
	m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
	m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
	m_LightAttack_DelegateREF = IPlayerInput->GetDelegate_LightAttackStart();
	m_HeavyAttack_DelegateREF = IPlayerInput->GetDelegate_HeavyAttackStart();
	m_EndAttack_02_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_EndAttack_02);
	m_AnimNotify_01_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_AnimNotify_01);

	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinLA_C1_2::HandleAction_MoveForward);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinLA_C1_2::HandleAction_MoveRight);
	if (m_LightAttack_DelegateREF != nullptr) m_LightAttack_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinLA_C1_2::HandleAction_LightAttack);
	if (m_HeavyAttack_DelegateREF != nullptr) m_HeavyAttack_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinLA_C1_2::HandleAction_HeavyAttackStart);
	if (m_EndAttack_02_DelegateREF != nullptr) m_EndAttack_02_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinLA_C1_2::HandleAction_EndAttack_02);
	if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinLA_C1_2::HandleAction_AnimNotify_01);

}

void UPlayerHumanState_AssassinLA_C1_2::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);
	if (m_LightAttack_DelegateREF != nullptr) m_LightAttack_DelegateREF->RemoveAll(this);
	if (m_HeavyAttack_DelegateREF != nullptr) m_HeavyAttack_DelegateREF->RemoveAll(this);
	if (m_EndAttack_02_DelegateREF != nullptr) m_EndAttack_02_DelegateREF->RemoveAll(this);
	if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->RemoveAll(this);

	m_MoveForward_DelegateREF = nullptr;
	m_MoveRight_DelegateREF = nullptr;
	m_LightAttack_DelegateREF = nullptr;
	m_HeavyAttack_DelegateREF = nullptr;
	m_EndAttack_02_DelegateREF = nullptr;
	m_AnimNotify_01_DelegateREF = nullptr;
}




/**
 * Private member functions
 */

void UPlayerHumanState_AssassinLA_C1_2::HandleAction_MoveForward(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_Value;
}

void UPlayerHumanState_AssassinLA_C1_2::HandleAction_MoveRight(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_Value;
}

void UPlayerHumanState_AssassinLA_C1_2::HandleAction_LightAttack()
{
	if (!b_IsInState) return;
	b_HasTriggerLightAttack = true;
	b_HasTriggerHeavyAttack = false;
}

void UPlayerHumanState_AssassinLA_C1_2::HandleAction_HeavyAttackStart()
{
	if (!b_IsInState) return;
	b_HasTriggerLightAttack = false;
	b_HasTriggerHeavyAttack = true;
}

void UPlayerHumanState_AssassinLA_C1_2::HandleAction_EndAttack_02()
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

void UPlayerHumanState_AssassinLA_C1_2::HandleAction_AnimNotify_01()
{
	if (!b_IsInState) return;
	b_CanBreakOut = true;
}