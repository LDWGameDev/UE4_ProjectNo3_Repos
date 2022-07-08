// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_PlayerHuman.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/Player/Character_PlayerHuman.h"
#include "StateMachine/Player/PlayerHuman/PlayerHuman_BaseState.h"

/**
 * Override functions
 */

void UAnimInstance_PlayerHuman::NativeInitializeAnimation() 
{
	m_CharacterPlayerHuman_OwnerCharacter = Cast<ACharacter_PlayerHuman>(TryGetPawnOwner());
	m_UnarmedIdleIndex = 1.0f;
	m_ControlRigFootIKAlpha = 0.0f;
	m_AnimSetIndex = 0;
	b_HasInitializedAnimInstance = true;
	b_ShouldLocomotionAnimation = true;
	b_IsInAir = false;
	b_DoFeetIK = false;
	m_LeanForwardValue = 0.0f;
	m_LeanRightValue = 0.0;
	m_SavedMovingDirectionAngle = 0.0f;
}

void UAnimInstance_PlayerHuman::NativeUpdateAnimation(float DeltaSeconds) 
{
	if (m_CharacterPlayerHuman_OwnerCharacter == nullptr || !b_HasInitializedAnimInstance) return;
	m_SavedLastFrameMovingSpeed = m_MovingSpeed;
	m_MovingSpeed = m_CharacterPlayerHuman_OwnerCharacter->GetMovingSpeed();
	m_MovingDirectionAngle = CalculateDirection(m_CharacterPlayerHuman_OwnerCharacter->GetVelocity(), m_CharacterPlayerHuman_OwnerCharacter->GetActorRotation());
	
	if (b_ShouldLocomotionAnimation)
	{
		float TargetLeanRight = FMath::Clamp(m_MovingDirectionAngle, -30.0f, 30.0f);
		m_LeanForwardValue = FMath::FInterpTo(m_LeanForwardValue, m_MovingSpeed - m_SavedLastFrameMovingSpeed, DeltaSeconds, 5.0f);
		m_LeanRightValue = FMath::FInterpTo(m_LeanRightValue, TargetLeanRight, DeltaSeconds, 8.0f);
	}
	else
	{
		m_LeanForwardValue = FMath::FInterpTo(m_LeanForwardValue, 0.0f, DeltaSeconds, 5.0f);
		m_LeanRightValue = FMath::FInterpTo(m_LeanRightValue, 0.0f, DeltaSeconds, 8.0f);
	}
}




/**
 * Public member functions
 */

void UAnimInstance_PlayerHuman::SetUpJogStop()
{
	m_SavedMovingDirectionAngle = m_MovingDirectionAngle;
	m_JogStop_StartPositionCurveValue = GetCurveValue(FName(TEXT("JogStop_StartPosition")));
}

void UAnimInstance_PlayerHuman::HandleAnimNotify_AnimNotify_01()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState() != nullptr)
	{
		m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState()->HandleAnimNotify_AnimNotify_01();
	}
}

void UAnimInstance_PlayerHuman::HandleAnimNotify_AnimNotify_02()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState() != nullptr)
	{
		m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState()->HandleAnimNotify_AnimNotify_02();
	}
}

void UAnimInstance_PlayerHuman::HandleAnimNotify_AnimNotify_03()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState() != nullptr)
	{
		m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState()->HandleAnimNotify_AnimNotify_03();
	}
}

void UAnimInstance_PlayerHuman::HandleAnimNotify_TriggerAttack_01()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState() != nullptr)
	{
		m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState()->HandleAnimNotify_TriggerAttack_01();
	}
}

void UAnimInstance_PlayerHuman::HandleAnimNotify_TriggerAttack_02()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState() != nullptr)
	{
		m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState()->HandleAnimNotify_TriggerAttack_02();
	}
}

void UAnimInstance_PlayerHuman::HandleAnimNotify_TriggerAttack_03()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState() != nullptr)
	{
		m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState()->HandleAnimNotify_TriggerAttack_03();
	}
}

void UAnimInstance_PlayerHuman::HandleAnimNotify_TriggerAttack_04()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState() != nullptr)
	{
		m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState()->HandleAnimNotify_TriggerAttack_04();
	}
}

void UAnimInstance_PlayerHuman::HandleAnimNotify_TriggerAttack_05()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState() != nullptr)
	{
		m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState()->HandleAnimNotify_TriggerAttack_05();
	}
}

void UAnimInstance_PlayerHuman::HandleAnimNotify_EndMontage()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState() != nullptr)
	{
		m_CharacterPlayerHuman_OwnerCharacter->GetCurrentState_PlayerHumanBaseState()->HandleAnimNotify_EndMontage();
	}
}

void UAnimInstance_PlayerHuman::CheckForCurrentState()
{
	if (m_CharacterPlayerHuman_OwnerCharacter == nullptr) return;
	UStateMachineComponent* StateMachineREF = m_CharacterPlayerHuman_OwnerCharacter->GetStateMachine();
	if (StateMachineREF == nullptr) return;

	UBaseState* CurrentState = StateMachineREF->GetCurrentState();
	if (CurrentState != nullptr)
	{
		FGameplayTag* StateTag = CurrentState->GetStateTag();
		if (StateTag != nullptr)
		{
			b_ShouldLocomotionAnimation = StateTag->MatchesAny(m_TagContainer_LocomotionAnimationStates);
			b_IsInAir = StateTag->MatchesAny(m_TagContainer_InAirStates);
		}
	}
}