// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_PlayerHuman.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/Player/Character_PlayerHuman.h"


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
}

void UAnimInstance_PlayerHuman::NativeUpdateAnimation(float DeltaSeconds) 
{
	if (m_CharacterPlayerHuman_OwnerCharacter == nullptr || !b_HasInitializedAnimInstance) return;
	m_MovingSpeed = m_CharacterPlayerHuman_OwnerCharacter->GetMovingSpeed();
	m_MovingDirectionAngle = CalculateDirection(m_CharacterPlayerHuman_OwnerCharacter->GetVelocity(), m_CharacterPlayerHuman_OwnerCharacter->GetActorRotation());
}




/**
 * Public member functions
 */

void UAnimInstance_PlayerHuman::SetUpJogStop()
{
	m_SavedMovingDirectionAngle = m_MovingDirectionAngle;
	m_JogStop_StartPositionCurveValue = GetCurveValue(FName(TEXT("JogStop_StartPosition")));
}

void UAnimInstance_PlayerHuman::BroadCastDelegate_EndMontage()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_EndMontage.IsBound())
	{
		m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_EndMontage.Broadcast();
	}
}

void UAnimInstance_PlayerHuman::BroadCastDelegate_EndMontage_02()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_EndMontage_02.IsBound())
	{
		m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_EndMontage_02.Broadcast();
	}
}

void UAnimInstance_PlayerHuman::BroadCastDelegate_AnimNotify_01()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_AnimNotify_01.IsBound())
	{
		m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_AnimNotify_01.Broadcast();
	}
}

void UAnimInstance_PlayerHuman::BroadCastDelegate_AnimNotify_02()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_AnimNotify_02.IsBound())
	{
		m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_AnimNotify_02.Broadcast();
	}
}

void UAnimInstance_PlayerHuman::BroadCastDelegate_AnimNotify_03()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_AnimNotify_03.IsBound())
	{
		m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_AnimNotify_03.Broadcast();
	}
}

void UAnimInstance_PlayerHuman::BroadCastDelegate_EndAttack_01()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_EndAttack_01.IsBound())
	{
		m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_EndAttack_01.Broadcast();
	}
}

void UAnimInstance_PlayerHuman::BroadCastDelegate_EndAttack_02()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_EndAttack_02.IsBound())
	{
		m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_EndAttack_02.Broadcast();
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

void UAnimInstance_PlayerHuman::BroadCastDelegate_TriggerAttack_01()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_TriggerAttack_01.IsBound())
	{
		m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_TriggerAttack_01.Broadcast();
	}
}

void UAnimInstance_PlayerHuman::BroadCastDelegate_TriggerAttack_02()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_TriggerAttack_02.IsBound())
	{
		m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_TriggerAttack_02.Broadcast();
	}
}

void UAnimInstance_PlayerHuman::BroadCastDelegate_TriggerAttack_03()
{
	if (m_CharacterPlayerHuman_OwnerCharacter != nullptr && m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_TriggerAttack_03.IsBound())
	{
		m_CharacterPlayerHuman_OwnerCharacter->m_Delegate_TriggerAttack_03.Broadcast();
	}
}