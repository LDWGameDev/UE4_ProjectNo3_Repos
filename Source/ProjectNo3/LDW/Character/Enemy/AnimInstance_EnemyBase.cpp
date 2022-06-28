// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_EnemyBase.h"
#include "Character/Enemy/Character_EnemyBase.h"
#include "StateMachine/Enemy/EnemyBaseState.h"


/**
 * Override functions
 */

void UAnimInstance_EnemyBase::NativeBeginPlay()
{
	m_CharacterREF_EnemyBase = Cast<ACharacter_EnemyBase>(TryGetPawnOwner());
}




/**
 * Public member functions
 */

void UAnimInstance_EnemyBase::HandleAnimNotify_01()
{
	if (m_CharacterREF_EnemyBase != nullptr && m_CharacterREF_EnemyBase->GetCurrentState_EnemyBaseState() != nullptr)
	{
		m_CharacterREF_EnemyBase->GetCurrentState_EnemyBaseState()->HandleAnimNotify_01();
	}
}

void UAnimInstance_EnemyBase::HandleAnimNotify_02()
{
	if (m_CharacterREF_EnemyBase != nullptr && m_CharacterREF_EnemyBase->GetCurrentState_EnemyBaseState() != nullptr)
	{
		m_CharacterREF_EnemyBase->GetCurrentState_EnemyBaseState()->HandleAnimNotify_02();
	}
}

void UAnimInstance_EnemyBase::HandleAnimNotify_03()
{
	if (m_CharacterREF_EnemyBase != nullptr && m_CharacterREF_EnemyBase->GetCurrentState_EnemyBaseState() != nullptr)
	{
		m_CharacterREF_EnemyBase->GetCurrentState_EnemyBaseState()->HandleAnimNotify_03();
	}
}

void UAnimInstance_EnemyBase::HandleEndMontage()
{
	if (m_CharacterREF_EnemyBase != nullptr && m_CharacterREF_EnemyBase->GetCurrentState_EnemyBaseState() != nullptr)
	{
		m_CharacterREF_EnemyBase->GetCurrentState_EnemyBaseState()->HandleEndMontage();
	}
}
