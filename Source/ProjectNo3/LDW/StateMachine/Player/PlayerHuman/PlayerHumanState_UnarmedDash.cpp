// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_UnarmedDash.h"
#include "Kismet/KismetMathLibrary.h"
#include "Library/Library_CustomMath.h"
#include "Engine/Engine.h"


UPlayerHumanState_UnarmedDash::UPlayerHumanState_UnarmedDash()
{
	m_StateID = FString("PlayerHumanState_UnarmedDash");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.Dash.UnarmedDash", false);
	m_CooldownTime = c_CooldownTime;
}


/**
* Override functions
*/

void UPlayerHumanState_UnarmedDash::EnterState()
{
	Super::EnterState();
	b_CanBreakOut = false;
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(c_TargetArmLengthFollow_01, 0.5f);

	PlayDashMontage();
}

void UPlayerHumanState_UnarmedDash::TickState(float p_Delta)
{
	Super::TickState(p_Delta);
	if (b_CanBreakOut && (FMath::Abs(m_MoveForwardValue) > 0.1f || FMath::Abs(m_MoveRightValue) > 0.1f))
	{
		m_CharPlayerHuman_Owner->DisableRootMotionForTime(0.3f);
		m_CharPlayerHuman_Owner->StopAnimMontage();
		ChangeState("PlayerHumanState_UnarmedJog");
	}
}

void UPlayerHumanState_UnarmedDash::ExitState()
{
	Super::ExitState();
	if (!b_CanBreakOut) m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 0.5f);
}



/**
* Public member functions
*/

void UPlayerHumanState_UnarmedDash::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput != nullptr)
	{
		m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
		m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
		m_EndMontage_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_EndMontage);
		m_AnimNotify_01_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_AnimNotify_01);

		if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedDash::HandleInput_MoveForward);
		if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedDash::HandleInput_MoveRight);
		if (m_EndMontage_DelegateREF != nullptr) m_EndMontage_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedDash::HandleAction_EndMontage);
		if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->AddUObject(this, &UPlayerHumanState_UnarmedDash::HandleAction_AnimNotify_01);
	}
}

void UPlayerHumanState_UnarmedDash::UnBindInputHandlingFunctions()
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

void UPlayerHumanState_UnarmedDash::HandleInput_MoveForward(float p_AxisValue)
{
	m_MoveForwardValue = p_AxisValue;
}

void UPlayerHumanState_UnarmedDash::HandleInput_MoveRight(float p_AxisValue)
{
	m_MoveRightValue = p_AxisValue;
}

void UPlayerHumanState_UnarmedDash::HandleAction_EndMontage()
{
	if (!b_IsInState) return;
	if (FMath::Abs(m_MoveForwardValue) < 0.1f && FMath::Abs(m_MoveRightValue) < 0.1f)
	{
		ChangeState(FString(TEXT("PlayerHumanState_UnarmedIdle")));
	}
	else
	{
		ChangeState(FString(TEXT("PlayerHumanState_UnarmedJog")));
	}
}

void UPlayerHumanState_UnarmedDash::HandleAction_AnimNotify_01()
{
	if (!b_IsInState) return;
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 0.5f);
	b_CanBreakOut = true;
}

void UPlayerHumanState_UnarmedDash::PlayDashMontage()
{
	float MoveForwardAbsoluteValue = FMath::Abs(m_MoveForwardValue);
	float MoveRightAbsoluteValue = FMath::Abs(m_MoveRightValue);

	if (MoveForwardAbsoluteValue < 0.1f && MoveRightAbsoluteValue < 0.1f)
	{
		// No movement input, do DashBackward
		m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Unarmed_Dash_Bwd")));
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
			m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Unarmed_Dash_Fwd")));
		}
		else if (DirectionAngle > -120.0f && DirectionAngle < -60.0f)
		{
			FRotator RotatorDashLeft = DashRotator;
			RotatorDashLeft.Yaw += 90.0f;
			m_CharPlayerHuman_Owner->RotateToRotation(RotatorDashLeft, 0.0f);
			m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Unarmed_Dash_Left")));
		}
		else if (DirectionAngle > 60.0f && DirectionAngle < 120.0f)
		{
			FRotator RotatorDashLeft = DashRotator;
			RotatorDashLeft.Yaw -= 90.0f;
			m_CharPlayerHuman_Owner->RotateToRotation(RotatorDashLeft, 0.0f);
			m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Unarmed_Dash_Right")));
		}
		else
		{
			FRotator RotatorDashBwd = DashRotator;
			RotatorDashBwd.Yaw += 180.0f;
			m_CharPlayerHuman_Owner->RotateToRotation(RotatorDashBwd, 0.0f);
			m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Unarmed_Dash_Bwd")));
		}
	}
}