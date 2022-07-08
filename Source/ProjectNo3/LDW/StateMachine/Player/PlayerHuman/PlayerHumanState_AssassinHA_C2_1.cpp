// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinHA_C2_1.h"


UPlayerHumanState_AssassinHA_C2_1::UPlayerHumanState_AssassinHA_C2_1()
{
	// Override properties
	m_StateID = TEXT("PlayerHumanState_AssassinHA_C2_1");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.HeavyAttack.AssassinHeavyAttack_Combo2_Phase1", false);
	m_CooldownTime = 1.0f;

	// Member properties
	b_CanBreakOut = false;
	b_HasTriggerHeavyAttack = false;

	m_Hitboxes_01.Reserve(3);
	m_Hitboxes_01.Add(FStruct_SphereTrace_Offset(FVector(160.0f, 70.0f, 0.0f), FVector(160.0f, 70.0f, -20.0f), 60.0f));
	m_Hitboxes_01.Add(FStruct_SphereTrace_Offset(FVector(190.0f, -10.0f, -20.0f), FVector(190.0f, -10.0f, -40.0f), 60.0f));
	m_Hitboxes_01.Add(FStruct_SphereTrace_Offset(FVector(120.0f, -90.0f, -40.0f), FVector(120.0f, -90.0f, -60.0f), 60.0f));

	m_Hitboxes_02.Reserve(4);
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(120.0f, -90.0f, -10.0f), FVector(120.0f, -90.0f, -30.0f), 60.0f));
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(180.0f, -10.0f, -10.0f), FVector(180.0f, -10.0f, -30.0f), 60.0f));
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(160.0f, 90.0f, 0.0f), FVector(160.0f, 90.0f, -20.0f), 60.0f));
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(110.0f, 180.0f, 0.0f), FVector(110.0f, 180.0f, -20.0f), 60.0f));
}



/**
 * Override functions
 */

void UPlayerHumanState_AssassinHA_C2_1::EnterState()
{
	Super::EnterState();
	RotateToClosetTarget();
	m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_HeavyAttack_C2_1")));
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(c_AdditionalArmLength, 0.5f);
}

void UPlayerHumanState_AssassinHA_C2_1::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (b_CanBreakOut && b_HasTriggerHeavyAttack)
	{
		b_CanBreakOut = false;
		b_HasTriggerHeavyAttack = false;
		ChangeState(TEXT("PlayerHumanState_AssassinHA_C2_2"));
	}
}

void UPlayerHumanState_AssassinHA_C2_1::ExitState()
{
	Super::ExitState();
	b_CanBreakOut = false;
	b_HasTriggerHeavyAttack = false;
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 2.0f);
}




/**
 * Public member functions
 */

void UPlayerHumanState_AssassinHA_C2_1::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput == nullptr) return;
	m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
	m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
	m_HeavyAttackStart_DelegateREF = IPlayerInput->GetDelegate_HeavyAttackStart();

	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C2_1::HandleAction_MoveForward);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C2_1::HandleAction_MoveRight);
	if (m_HeavyAttackStart_DelegateREF != nullptr) m_HeavyAttackStart_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C2_1::HandleAction_HeavyAttackStart);
}

void UPlayerHumanState_AssassinHA_C2_1::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);
	if (m_HeavyAttackStart_DelegateREF != nullptr) m_HeavyAttackStart_DelegateREF->RemoveAll(this);

	m_MoveForward_DelegateREF = nullptr;
	m_MoveRight_DelegateREF = nullptr;
	m_HeavyAttackStart_DelegateREF = nullptr;
}

void UPlayerHumanState_AssassinHA_C2_1::HandleAnimNotify_AnimNotify_01()
{
	b_CanBreakOut = true;
}

void UPlayerHumanState_AssassinHA_C2_1::HandleAnimNotify_EndMontage()
{
	Super::HandleAnimNotify_EndMontage();
	if (FMath::Abs(m_MoveForwardValue) > 0.1f || FMath::Abs(m_MoveRightValue) > 0.1f)
	{
		m_CharPlayerHuman_Owner->StopAnimMontage();
		m_CharPlayerHuman_Owner->DisableRootMotionForTime(0.1f);
		ChangeState("PlayerHumanState_AssassinJog");
	}
	else ChangeState("PlayerHumanState_AssassinIdle");
}

void UPlayerHumanState_AssassinHA_C2_1::HandleAnimNotify_TriggerAttack_01()
{
	CheckForHittingTarget(m_Hitboxes_01, m_AttackState_01, false);
}

void UPlayerHumanState_AssassinHA_C2_1::HandleAnimNotify_TriggerAttack_02()
{
	CheckForHittingTarget(m_Hitboxes_02, m_AttackState_02, false);
}





/**
 * Private member functions
 */

void UPlayerHumanState_AssassinHA_C2_1::HandleAction_MoveForward(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_Value;
}

void UPlayerHumanState_AssassinHA_C2_1::HandleAction_MoveRight(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_Value;
}

void UPlayerHumanState_AssassinHA_C2_1::HandleAction_HeavyAttackStart()
{
	if (!b_IsInState) return;
	b_HasTriggerHeavyAttack = true;
}