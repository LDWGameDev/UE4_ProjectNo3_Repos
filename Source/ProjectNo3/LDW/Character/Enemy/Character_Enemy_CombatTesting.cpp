// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Enemy_CombatTesting.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Character/Struct_MontageToPlay.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

#include "StateMachine/Enemy/CombatTesting/CombatTesting_IdleState.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_DamageGroundState.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_DamageUpAndInAir.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_KnockOutSimulate.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_GetUpSimulate.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_FallState.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_GetUpState.h"
#include "Library/Library_CustomMath.h"


#include "Kismet/KismetSystemLibrary.h"



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

	//if (m_StateMachine_01->GetCurrentState() == nullptr)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("CombatTesting - TakeHit() - CurrentState is null"));
	//}
	//else if (m_StateMachine_01->GetCurrentState()->GetStateTag() == nullptr)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("CombatTesting - TakeHit() - StateTag is null"));
	//}
	//else if (m_StateMachine_01->GetCurrentState()->GetStateTag()->IsValid() == false)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("CombatTesting - TakeHit() - StateTag not valid"));
	//}
	//else if (m_StateMachine_01->GetCurrentState()->GetStateTag()->MatchesAny(m_TagContainer_StatesCannotTakeDamage) == true) 
	//{
	//	FString CurrentState = UKismetSystemLibrary::GetDisplayName(m_StateMachine_01->GetCurrentState());
	//	UE_LOG(LogTemp, Warning, TEXT("CombatTesting - TakeHit() - State cannot take damage"));
	//	UE_LOG(LogTemp, Warning, TEXT("CombatTesting - TakeHit() - Current state: %s"), *CurrentState);
	//}

	if (m_StateMachine_01->GetCurrentState() == nullptr || !m_StateMachine_01->GetCurrentState()->GetStateTag()->IsValid() || m_StateMachine_01->GetCurrentState()->GetStateTag()->MatchesAny(m_TagContainer_StatesCannotTakeDamage)) return;
	//UE_LOG(LogTemp, Warning, TEXT("CombatTesting - TakeHit() - Conditions valid"));

	if (p_AttackDefinition.m_AttackerAttackStateREF->m_HitType == EHitType::KnockSimulate)
	{
		m_KnockOutSimulateStateREF->m_AttackDefinitionREF = &p_AttackDefinition;
		m_StateMachine_01->ChangeState(TEXT("CombatTesting_KnockOutSimulateState"));

	}
	else if(p_AttackDefinition.m_AttackerAttackStateREF->m_AttackDirection == EDirectionAttack6Ways::Up)
	{
		m_DamageInAirStateREF->m_AttackDefinitionREF = &p_AttackDefinition;
		m_StateMachine_01->ChangeState(TEXT("CombatTesting_DamageUpAndInAirState"));
	}
	else
	{
		m_DamageGroundStateREF->m_AttackDefinitionREF = &p_AttackDefinition;
		m_StateMachine_01->ChangeState(TEXT("CombatTesting_DamageGroundState"));
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
	StatesListREF->Reserve(7);

	m_IdleStateREF = NewObject<UCombatTesting_IdleState>();
	m_IdleStateREF->InitState(m_StateMachine_01, this);
	m_DamageGroundStateREF = NewObject<UCombatTesting_DamageGroundState>();
	m_DamageGroundStateREF->InitState(m_StateMachine_01, this);
	m_DamageInAirStateREF = NewObject<UCombatTesting_DamageUpAndInAir>();
	m_DamageInAirStateREF->InitState(m_StateMachine_01, this);
	m_KnockOutSimulateStateREF = NewObject<UCombatTesting_KnockOutSimulate>();
	m_KnockOutSimulateStateREF->InitState(m_StateMachine_01, this);
	m_GetUpSimulateStateREF = NewObject<UCombatTesting_GetUpSimulate>();
	m_GetUpSimulateStateREF->InitState(m_StateMachine_01, this);
	m_FallStateREF = NewObject<UCombatTesting_FallState>();
	m_FallStateREF->InitState(m_StateMachine_01, this);
	m_LandAndGetUpStateREF = NewObject<UCombatTesting_GetUpState>();
	m_LandAndGetUpStateREF->InitState(m_StateMachine_01, this);

	StatesListREF->Add(m_IdleStateREF);
	StatesListREF->Add(m_DamageGroundStateREF);
	StatesListREF->Add(m_DamageInAirStateREF);
	StatesListREF->Add(m_KnockOutSimulateStateREF);
	StatesListREF->Add(m_GetUpSimulateStateREF);
	StatesListREF->Add(m_FallStateREF);
	StatesListREF->Add(m_LandAndGetUpStateREF);
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
		m_StateMachine_01->ChangeState(TEXT("CombatTesting_IdleState"));
		break;
	}
	case 1:
	{
		m_LandAndGetUpStateREF->m_GetUpIndex = 1;
		m_StateMachine_01->ChangeState((TEXT("CombatTesting_LandAndGetUpState")));
		break;
	}
	case 2:
	{
		m_StateMachine_01->ChangeState(TEXT("CombatTesting_KnockOutSimulateState"));
		break;
	}
	}
}