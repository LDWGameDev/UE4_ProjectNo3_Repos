// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinHA_C1_2.h"
#include "GameFramework/CharacterMovementComponent.h"


UPlayerHumanState_AssassinHA_C1_2::UPlayerHumanState_AssassinHA_C1_2()
{
	m_StateID = TEXT("PlayerHumanState_AssassinHA_C1_2");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.HeavyAttack.AssassinHeavyAttack_Combo1_Phase2", false);
	b_CanBreakOut = false;

	m_Hitboxes_01.Add(FStruct_SphereTrace_Offset(FVector(80.0f, 0.0f, 40.0f), FVector(80.0f, 0.0f, -100.0f), 180.0f));
}



/**
 * Override functions
 */

void UPlayerHumanState_AssassinHA_C1_2::EnterState()
{
	Super::EnterState();
	(m_CharPlayerHuman_Owner->GetCharacterMovement())->SetMovementMode(EMovementMode::MOVE_Flying, 0);
	m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_HeavyAttack_C1_2")));
	SetCameraFollow_01(c_AdditionArmLength, c_SocketOffset, 1.0f, -10.0f, 60.0f, FVector(0.0f, -40.0f, 0.0f), FVector(0.0f, -40.0f, 0.0f));
	m_CharPlayerHuman_Owner->SetCapsuleSize(96.0f, 8.0f, 0.1f);
}

void UPlayerHumanState_AssassinHA_C1_2::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (b_CanBreakOut)
	{
		b_CanBreakOut = false;
	}
}

void UPlayerHumanState_AssassinHA_C1_2::ExitState()
{
	Super::ExitState();
	(m_CharPlayerHuman_Owner->GetCharacterMovement())->SetMovementMode(EMovementMode::MOVE_Walking, 0);
	b_CanBreakOut = false;
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 2.0f);
	m_CharPlayerHuman_Owner->ResetCapsuleSize(0.1f);
}




/**
 * Public member functions
 */

void UPlayerHumanState_AssassinHA_C1_2::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput == nullptr) return;
	m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
	m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
	m_AnimNotify_01_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_AnimNotify_01);
	m_EndAttack_02_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_EndAttack_02);

	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C1_2::HandleAction_MoveForward);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C1_2::HandleAction_MoveRight);
	if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C1_2::HandleAction_AnimNotify_01);
	if (m_EndAttack_02_DelegateREF != nullptr) m_EndAttack_02_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C1_2::HandleAction_EndAttack_02);

}

void UPlayerHumanState_AssassinHA_C1_2::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);
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

void UPlayerHumanState_AssassinHA_C1_2::HandleAction_MoveForward(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_Value;
}

void UPlayerHumanState_AssassinHA_C1_2::HandleAction_MoveRight(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_Value;
}

void UPlayerHumanState_AssassinHA_C1_2::HandleAction_AnimNotify_01()
{
	if (!b_IsInState) return;
	m_CharPlayerHuman_Owner->DisableRootMotionForTime(0.25f);
	m_CharPlayerHuman_Owner->ResetCapsuleSize(0.1f);
	b_CanBreakOut = true;
}

void UPlayerHumanState_AssassinHA_C1_2::HandleAction_EndAttack_02()
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
