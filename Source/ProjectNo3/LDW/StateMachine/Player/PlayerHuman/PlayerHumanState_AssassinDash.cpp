// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinDash.h"
#include "PlayerHumanState_AssassinDash_2.h"
#include "Kismet/KismetMathLibrary.h"
#include "Library/Library_CustomMath.h"
#include "Library/Library_Enum.h"


UPlayerHumanState_AssassinDash::UPlayerHumanState_AssassinDash()
{
	m_StateID = TEXT("PlayerHumanState_AssassinDash");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.Dash.AssassinDash", false);
	m_CooldownTime = c_CooldownTime;
	
	b_HasTriggerDashInput = false;
	b_CanBreakOut = false;
}



/**
 * Override functions
 */

void UPlayerHumanState_AssassinDash::EnterState()
{
	Super::EnterState();
	PlayDashMontage();
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(c_AdditionArmLengthFollow_01, 0.5f);
}

void UPlayerHumanState_AssassinDash::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (b_CanBreakOut)
	{
		if (b_HasTriggerDashInput)
		{
			b_CanBreakOut = false;
			b_HasTriggerDashInput = false;
			ChangeState("PlayerHumanState_AssassinDash_2");
		}
		else if (FMath::Abs(m_MoveForwardValue) > 0.1f || FMath::Abs(m_MoveRightValue) > 0.1f)
		{
			b_CanBreakOut = false;
			m_CharPlayerHuman_Owner->DisableRootMotionForTime(0.3f);
			m_CharPlayerHuman_Owner->StopAnimMontage();
			ChangeState("PlayerHumanState_AssassinJog");
		}
	}
}

void UPlayerHumanState_AssassinDash::ExitState()
{
	Super::ExitState();
	b_HasTriggerDashInput = false;
	b_CanBreakOut = false;
	(m_CharPlayerHuman_Owner->m_AssassinDash_2_State)->m_SavedCharacterRotator_Dash1 = m_CharPlayerHuman_Owner->GetActorRotation();
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 2.0f);
}





/**
 * Public member functions
 */

void UPlayerHumanState_AssassinDash::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput != nullptr)
	{
		m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
		m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
		m_DashStart_DelegateREF = IPlayerInput->GetDelegate_DashStart();
		m_EndMontage_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_EndMontage);
		m_AnimNotify_01_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_AnimNotify_01);

		if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinDash::HandleInput_MoveForward);
		if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinDash::HandleInput_MoveRight);
		if (m_DashStart_DelegateREF != nullptr) m_DashStart_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinDash::HandleAction_DashStart);
		if (m_EndMontage_DelegateREF != nullptr) m_EndMontage_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinDash::HandleAction_EndMontage);
		if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinDash::HandleAction_AnimNotify_01);
	}
}

void UPlayerHumanState_AssassinDash::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);
	if (m_DashStart_DelegateREF != nullptr) m_DashStart_DelegateREF->RemoveAll(this);
	if (m_EndMontage_DelegateREF != nullptr) m_EndMontage_DelegateREF->RemoveAll(this);
	if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->RemoveAll(this);

	m_MoveForward_DelegateREF = nullptr;
	m_MoveRight_DelegateREF = nullptr;
	m_DashStart_DelegateREF = nullptr;
	m_EndMontage_DelegateREF = nullptr;
	m_AnimNotify_01_DelegateREF = nullptr;
}




/**
* Private member functions
*/

void UPlayerHumanState_AssassinDash::HandleInput_MoveForward(float p_AxisValue)
{
	m_MoveForwardValue = p_AxisValue;
}

void UPlayerHumanState_AssassinDash::HandleInput_MoveRight(float p_AxisValue)
{
	m_MoveRightValue = p_AxisValue;
}

void UPlayerHumanState_AssassinDash::HandleAction_EndMontage()
{
	if (!b_IsInState) return;
	if (FMath::Abs(m_MoveForwardValue) < 0.1f && FMath::Abs(m_MoveRightValue) < 0.1f)
	{
		ChangeState(FString(TEXT("PlayerHumanState_AssassinIdle")));
	}
	else
	{
		ChangeState(FString(TEXT("PlayerHumanState_AssassinJog")));
	}
}

void UPlayerHumanState_AssassinDash::HandleAction_AnimNotify_01()
{
	if (!b_IsInState) return;
	b_CanBreakOut = true;
}

void UPlayerHumanState_AssassinDash::HandleAction_DashStart()
{
	if (!b_IsInState) return;
	b_HasTriggerDashInput = true;
}

void UPlayerHumanState_AssassinDash::PlayDashMontage()
{
	float MoveForwardAbsoluteValue = FMath::Abs(m_MoveForwardValue);
	float MoveRightAbsoluteValue = FMath::Abs(m_MoveRightValue);

	if (MoveForwardAbsoluteValue < 0.1f && MoveRightAbsoluteValue < 0.1f)
	{
		// No movement input, do DashBackward
		m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_Dash_Bwd")));
	}
	else
	{
		// Has movement input, do Dash based on controller direction (with offset base on movement input) and character direction.
		// Calculate the dash direction (direction where character will dash to), check with character current rotation and do the appropriate dashing and rotating.
		float AdditionAngle = 0.0f;
		if (m_MoveForwardValue > 0.1f)
		{
			if (MoveRightAbsoluteValue < 0.1f) AdditionAngle = 0.0f;
			else if (m_MoveRightValue > 0.1f) AdditionAngle = 45.0f;
			else AdditionAngle = -45.0f;
		}
		else if (m_MoveForwardValue < -0.1f)
		{
			if (MoveRightAbsoluteValue < 0.1f) AdditionAngle = 180.0f;
			else if (m_MoveRightValue > 0.1f) AdditionAngle = 135.0f;
			else AdditionAngle = -135.0f;
		}
		else
		{
			if (m_MoveRightValue > 0.1f) AdditionAngle = 90.0f;
			else if (m_MoveRightValue < -0.1f) AdditionAngle = -90.0f;
		}

		FRotator DashRotator = m_CharPlayerHuman_Owner->GetControlRotation();
		DashRotator.Roll = 0.0f;
		DashRotator.Pitch = 0.0f;
		DashRotator.Yaw += AdditionAngle;

		FVector DashDirection = UKismetMathLibrary::GetForwardVector(DashRotator);
		FVector CharacterForwardVector = m_CharPlayerHuman_Owner->GetActorForwardVector();
		float DirectionAngle = ULibrary_CustomMath::TwoVectorsAngle_Degrees180(CharacterForwardVector, DashDirection);

		if (DirectionAngle >= -60.0f && DirectionAngle <= 60.0f)
		{
			m_CharPlayerHuman_Owner->RotateToRotation(DashRotator, 0.0f);
			m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_Dash_Fwd")));
			(m_CharPlayerHuman_Owner->m_AssassinDash_2_State)->m_SavedDirection_Dash1 = EDirection8Ways::Forward;
		}
		else if (DirectionAngle > -120.0f && DirectionAngle < -60.0f)
		{
			FRotator RotatorDashLeft = DashRotator;
			RotatorDashLeft.Yaw += 90.0f;
			m_CharPlayerHuman_Owner->RotateToRotation(RotatorDashLeft, 0.0f);
			m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_Dash_Left")));
			(m_CharPlayerHuman_Owner->m_AssassinDash_2_State)->m_SavedDirection_Dash1 = EDirection8Ways::Left;
		}
		else if (DirectionAngle > 60.0f && DirectionAngle < 120.0f)
		{
			FRotator RotatorDashLeft = DashRotator;
			RotatorDashLeft.Yaw -= 90.0f;
			m_CharPlayerHuman_Owner->RotateToRotation(RotatorDashLeft, 0.0f);
			m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_Dash_Right")));
			(m_CharPlayerHuman_Owner->m_AssassinDash_2_State)->m_SavedDirection_Dash1 = EDirection8Ways::Right;
		}
		else
		{
			FRotator RotatorDashBwd = DashRotator;
			RotatorDashBwd.Yaw += 180.0f;
			m_CharPlayerHuman_Owner->RotateToRotation(RotatorDashBwd, 0.0f);
			m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_Dash_Bwd")));
			(m_CharPlayerHuman_Owner->m_AssassinDash_2_State)->m_SavedDirection_Dash1 = EDirection8Ways::Backward;
		}
	}
}
