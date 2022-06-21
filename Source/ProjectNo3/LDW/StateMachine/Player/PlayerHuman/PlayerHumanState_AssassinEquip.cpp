// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinEquip.h"
#include "../../../AnimInstance/AnimInstance_PlayerHuman.h"


UPlayerHumanState_AssassinEquip::UPlayerHumanState_AssassinEquip()
{
	m_StateID = TEXT("PlayerHumanState_AssassinEquip");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.Equip.AssassinEquip", false);
}



/**
 * Override functions
 */

void UPlayerHumanState_AssassinEquip::EnterState()
{
	Super::EnterState();
	if (m_CharPlayerHuman_Owner->m_AnimInstance_PlayerHuman_REF == nullptr) return;
	(m_CharPlayerHuman_Owner->m_AnimInstance_PlayerHuman_REF)->m_AnimSetIndex = 1;
	m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_Equip")));
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(c_AdditionalArmLength, 0.5f);
}

void UPlayerHumanState_AssassinEquip::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
}

void UPlayerHumanState_AssassinEquip::ExitState()
{
	Super::ExitState();
}


/**
 * Public member functions
 */

void UPlayerHumanState_AssassinEquip::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput == nullptr) return;
	m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
	m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
	m_EndMontage_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_EndMontage);
	m_AnimNotify_01_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_AnimNotify_01);
	
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinEquip::HandleDelegate_MoveForward);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinEquip::HandleDelegate_MoveRight);
	if (m_EndMontage_DelegateREF != nullptr) m_EndMontage_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinEquip::HandleAction_EndMontage);
	if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinEquip::HandleAction_AnimNotify_01);
}

void UPlayerHumanState_AssassinEquip::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);
	if (m_EndMontage_DelegateREF != nullptr) m_EndMontage_DelegateREF->RemoveAll(this);
	if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->RemoveAll(this);

	m_MoveForward_DelegateREF = nullptr;
	m_MoveRight_DelegateREF = nullptr;
	m_EndMontage_DelegateREF = nullptr;
	m_AnimNotify_01_DelegateREF = nullptr;
}



/**
 * Private member functions
 */

void UPlayerHumanState_AssassinEquip::HandleDelegate_MoveForward(float p_Value)
{
	if (!b_IsInState)return;
	m_MoveForwardValue = p_Value;
}

void UPlayerHumanState_AssassinEquip::HandleDelegate_MoveRight(float p_Value)
{
	if (!b_IsInState)return;
	m_MoveRightValue = p_Value;
}

void UPlayerHumanState_AssassinEquip::HandleAction_EndMontage()
{
	if (!b_IsInState) return;
	if (FMath::Abs(m_MoveForwardValue) > 0.1f || FMath::Abs(m_MoveRightValue) > 0.1f) ChangeState("PlayerHumanState_AssassinJog");
	else ChangeState(TEXT("PlayerHumanState_AssassinIdle"));
}

void UPlayerHumanState_AssassinEquip::HandleAction_AnimNotify_01()
{
	if (!b_IsInState) return;
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 2.0f);
}