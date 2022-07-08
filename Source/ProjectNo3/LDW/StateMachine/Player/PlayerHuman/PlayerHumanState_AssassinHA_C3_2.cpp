// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinHA_C3_2.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"



/**
 * 
 */

UPlayerHumanState_AssassinHA_C3_2::UPlayerHumanState_AssassinHA_C3_2()
{
	m_StateID = TEXT("PlayerHumanState_AssassinHA_C3_2");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.HeavyAttack.AssassinHeavyAttack_Combo3_Phase2", false);
	b_CanBreakOut = false;
	b_CameraSequenceValid = true;

	m_Hitboxes_01.Reserve(2);
	m_Hitboxes_01.Add(FStruct_SphereTrace_Offset(FVector(150.0f, -50.0f, -10.0f), FVector(150.0f, -50.0f, -30.0f), 80.0f));
	m_Hitboxes_01.Add(FStruct_SphereTrace_Offset(FVector(150.0f, 50.0f, -10.0f), FVector(150.0f, 50.0f, -30.0f), 80.0f));

	m_Hitboxes_02.Reserve(3);
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(-150.0f, 50.0f, -10.0f), FVector(-150.0f, 50.0f, -30.0f), 80.0f));
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(-180.0f, -50.0f, -10.0f), FVector(-180.0f, -50.0f, -30.0f), 80.0f));
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(-100.0f, -160.0f, -10.0f), FVector(-100.0f, -160.0f, -30.0f), 80.0f));

	m_Hitboxes_03.Reserve(3);
	m_Hitboxes_03.Add(FStruct_SphereTrace_Offset(FVector(90.0f, -150.0f, -10.0f), FVector(90.0f, -150.0f, -30.0f), 80.0f));
	m_Hitboxes_03.Add(FStruct_SphereTrace_Offset(FVector(0.0f, -200.0f, -10.0f), FVector(0.0f, -200.0f, -30.0f), 80.0f));
	m_Hitboxes_03.Add(FStruct_SphereTrace_Offset(FVector(-100.0f, -140.0f, -10.0f), FVector(-100.0f, -140.0f, -30.0f), 80.0f));

	m_Hitboxes_04.Reserve(4);
	m_Hitboxes_04.Add(FStruct_SphereTrace_Offset(FVector(0.0f, 190.0f, 0.0f), FVector(0.0f, 190.0f, -30.0f), 80.0f));
	m_Hitboxes_04.Add(FStruct_SphereTrace_Offset(FVector(-100.0f, 190.0f, 0.0f), FVector(-100.0f, 190.0f, -30.0f), 80.0f));
	m_Hitboxes_04.Add(FStruct_SphereTrace_Offset(FVector(-200.0f, 120.0f, 0.0f), FVector(-200.0f, 120.0f, -30.0f), 80.0f));

	m_Hitboxes_05.Add(FStruct_SphereTrace_Offset(FVector(80.0f, 0.0f, 40.0f), FVector(80.0f, 0.0f, -100.0f), 180.0f));
}



/**
 * Override functions
 */

void UPlayerHumanState_AssassinHA_C3_2::EnterState()
{
	Super::EnterState();
	m_CharPlayerHuman_Owner->GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("PawnIgnorePawn")), false);
	m_AttackIndex = 0;
	(m_CharPlayerHuman_Owner->GetCharacterMovement())->SetMovementMode(EMovementMode::MOVE_Flying);
	if (b_CameraSequenceValid) m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_HeavyAttack_C3_2")));
	else m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_HeavyAttack_C3_2_Type2")));
}

void UPlayerHumanState_AssassinHA_C3_2::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (b_CanBreakOut)
	{
		b_CanBreakOut = false;
	}
}

void UPlayerHumanState_AssassinHA_C3_2::ExitState()
{
	Super::ExitState();
	m_CharPlayerHuman_Owner->GetCapsuleComponent()->SetCollisionProfileName(FName(TEXT("Pawn")), false);
	(m_CharPlayerHuman_Owner->GetCharacterMovement())->SetMovementMode(EMovementMode::MOVE_Walking);
	b_CanBreakOut = false;
	if (!b_CameraSequenceValid) m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 2.0f);
}




/**
 * Public member functions
 */

void UPlayerHumanState_AssassinHA_C3_2::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput == nullptr) return;
	m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
	m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();

	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C3_2::HandleAction_MoveForward);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C3_2::HandleAction_MoveRight);
}

void UPlayerHumanState_AssassinHA_C3_2::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);

	m_MoveForward_DelegateREF = nullptr;
	m_MoveRight_DelegateREF = nullptr;
}

void UPlayerHumanState_AssassinHA_C3_2::HandleAnimNotify_AnimNotify_01()
{
	if (!b_IsInState) return;
	if (b_CameraSequenceValid) m_CharPlayerHuman_Owner->SetViewToCameraSequence(FName("Sequence_HA_C3_2"), true);
	else SetCameraFollow_01(c_AdditionArmLength, c_SocketOffset, 0.3f, -10.0f, 60.0f, FVector(0.0f, -40.0f, 0.0f), FVector(0.0f, -40.0f, 0.0f));
}

void UPlayerHumanState_AssassinHA_C3_2::HandleAnimNotify_EndMontage()
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

void UPlayerHumanState_AssassinHA_C3_2::HandleAnimNotify_TriggerAttack_01()
{
	CheckForHittingTarget(m_Hitboxes_01, m_AttackState_01, false);
}

void UPlayerHumanState_AssassinHA_C3_2::HandleAnimNotify_TriggerAttack_02()
{
	CheckForHittingTarget(m_Hitboxes_02, m_AttackState_02, false);
}

void UPlayerHumanState_AssassinHA_C3_2::HandleAnimNotify_TriggerAttack_03()
{
	CheckForHittingTarget(m_Hitboxes_03, m_AttackState_03, false);
}

void UPlayerHumanState_AssassinHA_C3_2::HandleAnimNotify_TriggerAttack_04()
{
	CheckForHittingTarget(m_Hitboxes_04, m_AttackState_04, false);
}

void UPlayerHumanState_AssassinHA_C3_2::HandleAnimNotify_TriggerAttack_05()
{
	CheckForHittingTarget(m_Hitboxes_05, m_AttackState_05, false);
}





/**
 * Private member functions
 */

void UPlayerHumanState_AssassinHA_C3_2::HandleAction_MoveForward(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_Value;
}

void UPlayerHumanState_AssassinHA_C3_2::HandleAction_MoveRight(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_Value;
}