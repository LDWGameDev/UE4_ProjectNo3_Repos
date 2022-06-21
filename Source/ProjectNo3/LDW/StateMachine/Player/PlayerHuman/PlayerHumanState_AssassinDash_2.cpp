// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinDash_2.h"


UPlayerHumanState_AssassinDash_2::UPlayerHumanState_AssassinDash_2()
{
	m_StateID = TEXT("PlayerHumanState_AssassinDash_2");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.Dash.AssassinDash_2", false);
	m_CooldownTime = c_CooldownTime;
	m_SavedDirection_Dash1 = EDirection8Ways::Backward;
	b_CanBreakOut = false;
}


/**
 * Override functions
 */

void UPlayerHumanState_AssassinDash_2::EnterState()
{
	Super::EnterState();
	PlayMontage();
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(c_AdditionArmLengthFollow_01, 0.5f);
}

void UPlayerHumanState_AssassinDash_2::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (b_CanBreakOut && (FMath::Abs(m_MoveForwardValue) > 0.1f || FMath::Abs(m_MoveRightValue) > 0.1f))
	{
		b_CanBreakOut = false;
		m_CharPlayerHuman_Owner->DisableRootMotionForTime(0.3f);
		m_CharPlayerHuman_Owner->StopAnimMontage();
		ChangeState("PlayerHumanState_AssassinJog");
	}
}

void UPlayerHumanState_AssassinDash_2::ExitState()
{
	Super::ExitState();
	b_CanBreakOut = false;
	m_SavedDirection_Dash1 = EDirection8Ways::Backward;
	(m_CharPlayerHuman_Owner->m_AssassinDashState)->SetExitStateTimeToNow();
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 1.0f);
}





/**
 * Public member functions
 */

void UPlayerHumanState_AssassinDash_2::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput == nullptr) return;
	m_DelegateREF_MoveForward = IPlayerInput->GetDelegate_MoveForward();
	m_DelegateREF_MoveRight = IPlayerInput->GetDelegate_MoveRight();
	m_DelegateREF_EndMontage_02 = &(m_CharPlayerHuman_Owner->m_Delegate_EndMontage_02);
	m_DelegateREF_AnimNotify_01 = &(m_CharPlayerHuman_Owner->m_Delegate_AnimNotify_01);

	if (m_DelegateREF_MoveForward != nullptr) m_DelegateREF_MoveForward->AddUObject(this, &UPlayerHumanState_AssassinDash_2::HandleAction_MoveForward);
	if (m_DelegateREF_MoveRight != nullptr) m_DelegateREF_MoveRight->AddUObject(this, &UPlayerHumanState_AssassinDash_2::HandleAction_MoveRight);
	if (m_DelegateREF_EndMontage_02 != nullptr) m_DelegateREF_EndMontage_02->AddUObject(this, &UPlayerHumanState_AssassinDash_2::HandleAction_EndMontage_02);
	if (m_DelegateREF_AnimNotify_01 != nullptr) m_DelegateREF_AnimNotify_01->AddUObject(this, &UPlayerHumanState_AssassinDash_2::HandleAction_AnimNotify_01);

}

void UPlayerHumanState_AssassinDash_2::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_DelegateREF_MoveForward != nullptr) m_DelegateREF_MoveForward->RemoveAll(this);
	if (m_DelegateREF_MoveRight != nullptr) m_DelegateREF_MoveRight->RemoveAll(this);
	if (m_DelegateREF_EndMontage_02 != nullptr) m_DelegateREF_EndMontage_02->RemoveAll(this);
	if (m_DelegateREF_AnimNotify_01 != nullptr) m_DelegateREF_AnimNotify_01->RemoveAll(this);

	m_DelegateREF_MoveForward = nullptr;
	m_DelegateREF_MoveRight = nullptr;
	m_DelegateREF_EndMontage_02 = nullptr;
	m_DelegateREF_AnimNotify_01 = nullptr;
}





/**
 * Private member functions
 */

void UPlayerHumanState_AssassinDash_2::HandleAction_MoveForward(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_Value;
}

void UPlayerHumanState_AssassinDash_2::HandleAction_MoveRight(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_Value;
}

void UPlayerHumanState_AssassinDash_2::HandleAction_EndMontage_02()
{
	if (!b_IsInState) return;
	if (FMath::Abs(m_MoveRightValue) > 0.1f || FMath::Abs(m_MoveForwardValue) > 0.1f) ChangeState(TEXT("PlayerHumanState_AssassinJog"));
	else ChangeState(TEXT("PlayerHumanState_AssassinIdle"));
}

void UPlayerHumanState_AssassinDash_2::HandleAction_AnimNotify_01()
{
	if (!b_IsInState) return;
	b_CanBreakOut = true;
}

void UPlayerHumanState_AssassinDash_2::PlayMontage()
{
	switch (m_SavedDirection_Dash1)
	{
	case EDirection8Ways::Forward:
	{
		m_CharPlayerHuman_Owner->SetActorRotation(m_SavedCharacterRotator_Dash1);
		m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_Dash_2_Fwd")));
		break;
	}
	case EDirection8Ways::Left:
	{
		//m_CharPlayerHuman_Owner->DisableRootMotionForTime(0.1f);
		m_SavedCharacterRotator_Dash1.Yaw -= 90.0f;
		m_CharPlayerHuman_Owner->SetActorRotation(m_SavedCharacterRotator_Dash1);
		m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_Dash_2_Fwd")));
		break;
	}
	case EDirection8Ways::Right:
	{
		//m_CharPlayerHuman_Owner->DisableRootMotionForTime(0.1f);
		m_SavedCharacterRotator_Dash1.Yaw += 90.0f;
		m_CharPlayerHuman_Owner->SetActorRotation(m_SavedCharacterRotator_Dash1);
		m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_Dash_2_Fwd")));
		break;
	}
	case EDirection8Ways::Backward:
	{
		m_CharPlayerHuman_Owner->SetActorRotation(m_SavedCharacterRotator_Dash1);
		m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_Dash_2_Bwd")));
		break;
	}
	default:
	{
		m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_Dash_2_Bwd")));
		break;
	}
	}
}