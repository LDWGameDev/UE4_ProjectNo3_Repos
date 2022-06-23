// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinLA_C1_3.h"
#include "PlayerHumanState_AssassinLA_C1_1.h"


UPlayerHumanState_AssassinLA_C1_3::UPlayerHumanState_AssassinLA_C1_3()
{
	m_StateID = TEXT("PlayerHumanState_AssassinLA_C1_3");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.LightAttack.AssassinLightAttack_Combo1_Phase3", false);
	m_CooldownTime = c_CooldownTime;
	b_HasTriggerLightAttack = false;
	b_CanBreakOut = false;

	m_Hitboxes_01.Reserve(4);
	m_Hitboxes_01.Add(FStruct_SphereTrace_Offset(FVector(130.0f, -90.0f, -40.0f), FVector(130.0f, -90.0f, -60.0f), 80.0f));
	m_Hitboxes_01.Add(FStruct_SphereTrace_Offset(FVector(180.0f, -10.0f, -20.0f), FVector(180.0f, -10.0f, -40.0f), 80.0f));
	m_Hitboxes_01.Add(FStruct_SphereTrace_Offset(FVector(160.0f, 70.0f, 0.0f), FVector(160.0f, 70.0f, -20.0f), 80.0f));
	m_Hitboxes_01.Add(FStruct_SphereTrace_Offset(FVector(90.0f, 150.0f, 10.0f), FVector(90.0f, 150.0f, -10.0f), 80.0f));

	m_Hitboxes_02.Reserve(4);
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(120.0f, -90.0f, -40.0f), FVector(120.0f, -90.0f, -60.0f), 80.0f));
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(180.0f, -10.0f, -20.0f), FVector(180.0f, -10.0f, -40.0f), 80.0f));
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(150.0f, 70.0f, 0.0f), FVector(150.0f, 70.0f, -20.0f), 80.0f));
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(90.0f, 150.0f, 10.0f), FVector(90.0f, 150.0f, -10.0f), 80.0f));

	m_Hitboxes_03.Reserve(2);
	m_Hitboxes_03.Add(FStruct_SphereTrace_Offset(FVector(160.0f, 30.0f, 60.0f), FVector(160.0f, 30.0f, 10.0f), 80.0f));
	m_Hitboxes_03.Add(FStruct_SphereTrace_Offset(FVector(150.0f, -60.0f, 20.0f), FVector(150.0f, -60.0f, -30.0f), 80.0f));
}



/**
 * Override functions
 */

void UPlayerHumanState_AssassinLA_C1_3::EnterState()
{
	Super::EnterState();
	m_CharPlayerHuman_Owner->PlayMontageFromTable("Assassin_LightAttack_C1_3");
	SetCameraFollow_01(c_AdditionalArmLength, c_SocketOffset, 1.0f, -20.0f, 60.0f, FVector(0.0f, -60.0f, 0.0f), FVector(0.0f, -60.0f, 0.0f));
}

void UPlayerHumanState_AssassinLA_C1_3::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (b_CanBreakOut && b_HasTriggerLightAttack)
	{
		b_CanBreakOut = false;
	}
}

void UPlayerHumanState_AssassinLA_C1_3::ExitState()
{
	Super::ExitState();
	b_HasTriggerLightAttack = false;
	b_CanBreakOut = false;
	(m_CharPlayerHuman_Owner->m_AssassinLightAttack_C1_1)->SetExitStateTimeToNow();
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 2.0f);
}





/**
 * Public member functions
 */

void UPlayerHumanState_AssassinLA_C1_3::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput == nullptr) return;
	m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
	m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
	m_EndAttack_01_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_EndAttack_01);
	m_AnimNotify_01_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_AnimNotify_01);
	m_TriggerAttack_01_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_TriggerAttack_01);
	m_TriggerAttack_02_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_TriggerAttack_02);
	m_TriggerAttack_03_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_TriggerAttack_03);

	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinLA_C1_3::HandleAction_MoveForward);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinLA_C1_3::HandleAction_MoveRight);
	if (m_EndAttack_01_DelegateREF != nullptr) m_EndAttack_01_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinLA_C1_3::HandleAction_EndAttack_01);
	if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinLA_C1_3::HandleAction_AnimNotify_01);
	if (m_TriggerAttack_01_DelegateREF != nullptr) m_TriggerAttack_01_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinLA_C1_3::HandleAction_TriggerAttack_01);
	if (m_TriggerAttack_02_DelegateREF != nullptr) m_TriggerAttack_02_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinLA_C1_3::HandleAction_TriggerAttack_02);
	if (m_TriggerAttack_03_DelegateREF != nullptr) m_TriggerAttack_03_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinLA_C1_3::HandleAction_TriggerAttack_03);
}

void UPlayerHumanState_AssassinLA_C1_3::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);
	if (m_EndAttack_01_DelegateREF != nullptr) m_EndAttack_01_DelegateREF->RemoveAll(this);
	if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->RemoveAll(this);
	if (m_TriggerAttack_01_DelegateREF != nullptr) m_TriggerAttack_01_DelegateREF->RemoveAll(this);
	if (m_TriggerAttack_02_DelegateREF != nullptr) m_TriggerAttack_02_DelegateREF->RemoveAll(this);
	if (m_TriggerAttack_03_DelegateREF != nullptr) m_TriggerAttack_03_DelegateREF->RemoveAll(this);

	m_MoveForward_DelegateREF = nullptr;
	m_MoveRight_DelegateREF = nullptr;
	m_EndAttack_01_DelegateREF = nullptr;
	m_AnimNotify_01_DelegateREF = nullptr;
	m_TriggerAttack_01_DelegateREF = nullptr;
	m_TriggerAttack_02_DelegateREF = nullptr;
	m_TriggerAttack_03_DelegateREF = nullptr;
}




/**
 * Private member functions
 */

void UPlayerHumanState_AssassinLA_C1_3::HandleAction_MoveForward(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_Value;
}

void UPlayerHumanState_AssassinLA_C1_3::HandleAction_MoveRight(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_Value;
}

void UPlayerHumanState_AssassinLA_C1_3::HandleAction_EndAttack_01()
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

void UPlayerHumanState_AssassinLA_C1_3::HandleAction_AnimNotify_01()
{
	if (!b_IsInState) return;
	b_CanBreakOut = true;
}

void UPlayerHumanState_AssassinLA_C1_3::HandleAction_TriggerAttack_01()
{
	if (!b_IsInState) return;
	CheckForHittingTarget(m_Hitboxes_01, m_AttackStateDefinition_01);
}

void UPlayerHumanState_AssassinLA_C1_3::HandleAction_TriggerAttack_02()
{
	if (!b_IsInState) return;
	CheckForHittingTarget(m_Hitboxes_02, m_AttackStateDefinition_01);
}

void UPlayerHumanState_AssassinLA_C1_3::HandleAction_TriggerAttack_03()
{
	if (!b_IsInState) return;
	CheckForHittingTarget(m_Hitboxes_03, m_AttackStateDefinition_02);
}
