// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTesting_KnockOutSimulate.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"


/**
 *
 */

UCombatTesting_KnockOutSimulate::UCombatTesting_KnockOutSimulate()
{
	m_StateID = TEXT("CombatTesting_KnockOutSimulateState");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag(FName(TEXT("StateMachine.EnemyState.CombatTesting.Action.Damage.KnockOutSimulate")), false);
	b_HasSimulatedPhysics = false;
}




/**
 * Override functions
 */

void UCombatTesting_KnockOutSimulate::EnterState()
{
	Super::EnterState();
	PlayKnockOutMontage();
}

void UCombatTesting_KnockOutSimulate::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	// Snap Character location via SkeletalMesh pelvis location
	if (b_HasSimulatedPhysics)
	{
		FVector PelvisLocation = m_Character_EnemyCombatTestingREF->GetMesh()->GetSocketLocation(FName(TEXT("Pelvis")));
		TArray<AActor*> ActorsToIgnore;
		FHitResult OutHitResult;
		bool TraceResult = UKismetSystemLibrary::LineTraceSingleForObjects(m_Character_EnemyCombatTestingREF, PelvisLocation, PelvisLocation + FVector(0.0f, 0.0f, -100.0f), m_Character_EnemyCombatTestingREF->m_ObjectTypes_Ground,
			false, ActorsToIgnore, EDrawDebugTrace::None, OutHitResult, true);
		if (TraceResult)
		{
			m_Character_EnemyCombatTestingREF->SetActorLocation(FMath::VInterpTo(m_Character_EnemyCombatTestingREF->GetActorLocation(), OutHitResult.Location + m_SavedCharacterOffsetLocation, p_DeltaTime, c_SnapCharacterPositionSpeed));
		}
		else
		{
			m_Character_EnemyCombatTestingREF->SetActorLocation(FMath::VInterpTo(m_Character_EnemyCombatTestingREF->GetActorLocation(), PelvisLocation, p_DeltaTime, c_SnapCharacterPositionSpeed));
		}
	}
}

void UCombatTesting_KnockOutSimulate::ExitState()
{
	Super::ExitState();
	b_HasSimulatedPhysics = false;
}

void UCombatTesting_KnockOutSimulate::HandleAnimNotify_01()
{
	StartSimulating();
}





/**
 * Private member functions
 */

void UCombatTesting_KnockOutSimulate::PlayKnockOutMontage()
{
	if (m_AttackDefinitionREF == nullptr || !m_AttackDefinitionREF->CheckValid()) return;
	m_Character_EnemyCombatTestingREF->RotateToFaceActor(m_AttackDefinitionREF->m_AttackerActor, 0.0f);
	if (FMath::FRandRange(0.0f, 1.0f) > 0.5f) m_Character_EnemyCombatTestingREF->PlayMontageFromTable_DamageMontage(FName(TEXT("Damage_KnockOutSimulate_F_01")));
	else m_Character_EnemyCombatTestingREF->PlayMontageFromTable_DamageMontage(FName(TEXT("Damage_KnockOutSimulate_F_02")));
}

void UCombatTesting_KnockOutSimulate::StartSimulating()
{
	if (!m_Character_EnemyCombatTestingREF->GetMesh()) return;
	if (m_Character_EnemyCombatTestingREF->GetCapsuleComponent() != nullptr) m_SavedCharacterOffsetLocation = FVector(0.0f, 0.0f, m_Character_EnemyCombatTestingREF->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	m_Character_EnemyCombatTestingREF->GetMesh()->SetAllBodiesBelowSimulatePhysics(FName(TEXT("Pelvis")), true, true);
	b_HasSimulatedPhysics = true;
	m_Character_EnemyCombatTestingREF->m_AnimInstanceREF_EnemyCombatTesting->b_IsSimulatingPhysics_DamageKnockOut = true;

	FTimerHandle TimerHandle_DelayGetUp;
	m_Character_EnemyCombatTestingREF->GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelayGetUp, [&]()
	{
		ChangeState(TEXT("CombatTesting_GetUpSimulateState"));
	}, c_TimeToGetUpAfterSimulating, false);
}

