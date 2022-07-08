// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTesting_GetUpSimulate.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"


/**
 *
 */

UCombatTesting_GetUpSimulate::UCombatTesting_GetUpSimulate()
{
	m_StateID = TEXT("CombatTesting_GetUpSimulateState");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag(FName(TEXT("StateMachine.EnemyState.CombatTesting.Action.GetUp.GetUpSimulate")), false);
}



/**
 * Override functions
 */

void UCombatTesting_GetUpSimulate::EnterState()
{
	Super::EnterState();

	// Check for character is facing up or down
	if (m_Character_EnemyCombatTestingREF->GetMesh() == nullptr) return;
	FRotator PelvisRotator = m_Character_EnemyCombatTestingREF->GetMesh()->GetSocketRotation(FName(TEXT("Pelvis")));
	float DotProductResult = UKismetMathLibrary::Dot_VectorVector(UKismetMathLibrary::GetRightVector(PelvisRotator), FVector::UpVector);
	b_SavedIsFacingUp = (DotProductResult >= 0.0f) ? true : false;

	// Rotate character via facing direction
	FVector PelvisLocation = m_Character_EnemyCombatTestingREF->GetMesh()->GetSocketLocation(FName(TEXT("Pelvis")));
	FVector NeckLocation = m_Character_EnemyCombatTestingREF->GetMesh()->GetSocketLocation(FName(TEXT("neck_01")));
	FVector NextForwardDirection = (b_SavedIsFacingUp) ? (PelvisLocation - NeckLocation) : (NeckLocation - PelvisLocation);
	FRotator CharacterNextRotator = UKismetMathLibrary::MakeRotFromZX(FVector::UpVector, NextForwardDirection);
	CharacterNextRotator.Pitch = 0.0f;
	CharacterNextRotator.Roll = 0.0f;
	//m_Character_EnemyCombatTestingREF->SetActorRotation(CharacterNextRotator);
	m_Character_EnemyCombatTestingREF->RotateToRotation(CharacterNextRotator, 0.1f);

	// Delay save pose snapshot
	FTimerHandle TimerHandle_DelaySavePoseSnapshot;
	m_Character_EnemyCombatTestingREF->GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelaySavePoseSnapshot, [&]()
		{
			if (b_IsInState)
			{
				m_Character_EnemyCombatTestingREF->m_AnimInstanceREF_EnemyCombatTesting->SavePoseSnapshot(FName("PoseSnapshot_DamageGetUp"));
				if (b_SavedIsFacingUp) m_Character_EnemyCombatTestingREF->PlayMontageFromTable_DamageMontage(FName(TEXT("Damage_GetUp_F_01")));
				else m_Character_EnemyCombatTestingREF->PlayMontageFromTable_DamageMontage(FName(TEXT("Damage_GetUp_B_01")));
			}
		}, 0.2f, false);

	// Delay play get up montage
	FTimerHandle TimerHandle_DelayStopSimulatingPhysics;
	m_Character_EnemyCombatTestingREF->GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelayStopSimulatingPhysics, [&]()
		{
			if (b_IsInState)
			{
				m_Character_EnemyCombatTestingREF->GetMesh()->SetAllBodiesBelowSimulatePhysics(FName("Pelvis"), false, true);
				m_Character_EnemyCombatTestingREF->m_AnimInstanceREF_EnemyCombatTesting->b_IsSimulatingPhysics_DamageKnockOut = false;
			}
		}, 0.3f, false);
}

void UCombatTesting_GetUpSimulate::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
}

void UCombatTesting_GetUpSimulate::ExitState()
{
	Super::ExitState();
	m_Character_EnemyCombatTestingREF->GetMesh()->SetAllBodiesBelowSimulatePhysics(FName("Pelvis"), false, true);
	m_Character_EnemyCombatTestingREF->m_AnimInstanceREF_EnemyCombatTesting->b_IsSimulatingPhysics_DamageKnockOut = false;
}

void UCombatTesting_GetUpSimulate::HandleEndMontage()
{
	ChangeState(TEXT("CombatTesting_IdleState"));
}