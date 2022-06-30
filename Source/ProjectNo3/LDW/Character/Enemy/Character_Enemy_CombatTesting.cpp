// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Enemy_CombatTesting.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Character/Struct_MontageToPlay.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

#include "StateMachine/Enemy/CombatTesting/CombatTesting_IdleState.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_DamageState.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_DamageInAirState.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_KnockOutSimulate.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_GetUpSimulate.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_FallState.h"
#include "Library/Library_CustomMath.h"


/**
 * 
 */
ACharacter_Enemy_CombatTesting::ACharacter_Enemy_CombatTesting()
{
	// CapsuleComponent defaults
	m_DefaultCapsuleHalfHeight = 96.0f;
	m_DefaultCapsuleRadius = 42.0f;
	GetCapsuleComponent()->InitCapsuleSize(m_DefaultCapsuleRadius, m_DefaultCapsuleHalfHeight);

	// SkeletalMesh defaults
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -m_DefaultCapsuleHalfHeight));

	// Set CharacterMovement defaults
	GetCharacterMovement()->GravityScale = 2.5f;

}

void ACharacter_Enemy_CombatTesting::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ACharacter_Enemy_CombatTesting::BeginPlay()
{
	Super::BeginPlay();
	m_AnimInstanceREF_EnemyCombatTesting = Cast<UAnimInstance_Enemy_CombatTesting>(GetMesh()->GetAnimInstance());
	if (m_StateMachine_01 != nullptr) m_StateMachine_01->m_Delegate_ChangeState.AddUObject(this, &ACharacter_Enemy_CombatTesting::HandleDelegate_ChangeState);
	InitStates();
	ActivateEnemy(true);
}

void ACharacter_Enemy_CombatTesting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacter_Enemy_CombatTesting::ActivateEnemy(bool p_DoActivate)
{
	Super::ActivateEnemy(p_DoActivate);
	if (m_StateMachine_01 == nullptr) return;

	if (p_DoActivate)
	{
		// Delay activate m_StateMachine_01 and trigger start state
		FTimerHandle TimerHandle_DelayActivateEnemy;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelayActivateEnemy, [&]()
			{
				m_StateMachine_01->ActivateStateMachine(TEXT("CombatTesting_IdleState"));
			}, 0.5f, false);
	}
	else
	{
		// Deactivate enemy
		m_StateMachine_01->DeactivateStateMachine();
	}
}





/**
 * Interface functions
 */

void ACharacter_Enemy_CombatTesting::TakeHit(FStruct_AttackDefinition& p_AttackDefinition)
{
	Super::TakeHit(p_AttackDefinition);
	if (m_StateMachine_01 == nullptr || !p_AttackDefinition.CheckValid()) return;
	// Check current state
	if (!m_TagContainer_StatesCanChangeToGetDamage.IsValid() || m_StateMachine_01->GetCurrentState() == nullptr || !m_StateMachine_01->GetCurrentState()->GetStateTag()->IsValid() ||
		!m_StateMachine_01->GetCurrentState()->GetStateTag()->MatchesAny(m_TagContainer_StatesCanChangeToGetDamage)) return;

	if (p_AttackDefinition.m_AttackerAttackStateREF->m_HitType == EHitType::KnockSimulate)
	{
		m_KnockOutSimulateStateREF->m_AttackDefinitionREF = &p_AttackDefinition;
		m_StateMachine_01->ChangeState(TEXT("CombatTesting_KnockOutSimulateState"));
	}
	else if(p_AttackDefinition.m_AttackerAttackStateREF->m_AttackDirection == EDirectionAttack6Ways::Up)
	{
		m_DamageInAirStateREF->m_AttackDefinitionREF = &p_AttackDefinition;
		m_StateMachine_01->ChangeState(TEXT("CombatTesting_DamageInAirState"));
	}
	else
	{
		m_DamageStateREF->m_AttackDefinitionREF = &p_AttackDefinition;
		m_StateMachine_01->ChangeState(TEXT("CombatTesting_LightDamageState"));
	}
}

void ACharacter_Enemy_CombatTesting::PlayMontageFromTable_DamageMontage(const FName& p_MontageID)
{
	FStruct_MontageToPlay* MontageStruct = m_DataTable_DamageMontages->FindRow<FStruct_MontageToPlay>(p_MontageID, nullptr, false);
	if (MontageStruct != nullptr && MontageStruct->m_AnimMontage != nullptr)
	{
		PlayAnimMontage(MontageStruct->m_AnimMontage);
	}
}

void ACharacter_Enemy_CombatTesting::PlayMontageFromTable_DamageMontage(const FName& p_MontageID, float p_TimeToPlay)
{
	FStruct_MontageToPlay* MontageStruct = m_DataTable_DamageMontages->FindRow<FStruct_MontageToPlay>(p_MontageID, nullptr, false);
	if (MontageStruct != nullptr && MontageStruct->m_AnimMontage != nullptr)
	{
		if (p_TimeToPlay <= 0.0f)
		{
			PlayAnimMontage(MontageStruct->m_AnimMontage);
		}
		else
		{
			float MontageLength = MontageStruct->m_AnimMontage->GetPlayLength();
			PlayAnimMontage(MontageStruct->m_AnimMontage, MontageLength / p_TimeToPlay);
		}
	}
}







/**
 * Private member functions
 */

void ACharacter_Enemy_CombatTesting::InitStates()
{
	if (m_StateMachine_01 == nullptr || m_StateMachine_01->GetAvailableStatesList() == nullptr) return;
	auto* StatesListREF = m_StateMachine_01->GetAvailableStatesList();
	StatesListREF->Reserve(5);

	m_IdleStateREF = NewObject<UCombatTesting_IdleState>();
	m_IdleStateREF->InitState(m_StateMachine_01, this);
	m_DamageStateREF = NewObject<UCombatTesting_DamageState>();
	m_DamageStateREF->InitState(m_StateMachine_01, this);
	m_KnockOutSimulateStateREF = NewObject<UCombatTesting_KnockOutSimulate>();
	m_KnockOutSimulateStateREF->InitState(m_StateMachine_01, this);
	m_GetUpSimulateStateREF = NewObject<UCombatTesting_GetUpSimulate>();
	m_GetUpSimulateStateREF->InitState(m_StateMachine_01, this);
	m_FallStateREF = NewObject<UCombatTesting_FallState>();
	m_FallStateREF->InitState(m_StateMachine_01, this);
	m_DamageInAirStateREF = NewObject<UCombatTesting_DamageInAirState>();
	m_DamageInAirStateREF->InitState(m_StateMachine_01, this);

	StatesListREF->Add(m_IdleStateREF);
	StatesListREF->Add(m_DamageStateREF);
	StatesListREF->Add(m_KnockOutSimulateStateREF);
	StatesListREF->Add(m_GetUpSimulateStateREF);
	StatesListREF->Add(m_FallStateREF);
	StatesListREF->Add(m_DamageInAirStateREF);
}

void ACharacter_Enemy_CombatTesting::HandleDelegate_ChangeState()
{
	if (m_AnimInstanceREF_EnemyCombatTesting != nullptr && m_StateMachine_01 != nullptr) m_AnimInstanceREF_EnemyCombatTesting->CheckCurrentState(m_StateMachine_01->GetCurrentState());
}










void ACharacter_Enemy_CombatTesting::TestFunction(int32 p_CommandIndex)
{
	switch (p_CommandIndex)
	{
	case 0:
	{
		m_StateMachine_01->ChangeState((TEXT("CombatTesting_KnockOutSimulateState")));
		break;
	}
	case 1:
	{
		m_StateMachine_01->ChangeState((TEXT("CombatTesting_GetUpSimulateState")));
		break;
	}
	case 2:
	{
		FVector NextLocation = GetActorLocation() + FVector(0.0f, 0.0f, 150.0f);
		MoveToLocation(NextLocation, 2.0f);
		break;
	}
	}
}