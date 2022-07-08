// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatTesting_DamageGroundState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Library/Library_CustomMath.h"


/**
 *
 */

UCombatTesting_DamageGroundState::UCombatTesting_DamageGroundState()
{
	m_StateID = TEXT("CombatTesting_DamageGroundState");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag(FName(TEXT("StateMachine.EnemyState.CombatTesting.Action.Damage.DamageGround")), false);
}



/**
 * Override functions
 */

void UCombatTesting_DamageGroundState::EnterState()
{
	Super::EnterState();
	HandleGetDamage();
}

void UCombatTesting_DamageGroundState::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
}

void UCombatTesting_DamageGroundState::ExitState()
{
	Super::ExitState();
}

void UCombatTesting_DamageGroundState::HandleEndMontage()
{
	Super::HandleEndMontage();
	if (m_Character_EnemyCombatTestingREF->b_IsInAir)
	{
		ChangeState(TEXT("CombatTesting_FallState"));
	}
	else
	{
		ChangeState(TEXT("CombatTesting_IdleState"));
	}
}





/**
 * Private member functions
 */

void UCombatTesting_DamageGroundState::HandleGetDamage()
{
	if (m_AttackDefinitionREF == nullptr || !m_AttackDefinitionREF->CheckValid()) return;

	// To calculate damage direction (L, R, F, B) to play damage montage
	// First, RotatorDamageDirection = LookAtRotator from attacked to attacker
	FRotator RotatorDamageDirection = UKismetMathLibrary::FindLookAtRotation(m_Character_EnemyCombatTestingREF->GetActorLocation(), (m_AttackDefinitionREF->m_AttackerActor)->GetActorLocation());
	RotatorDamageDirection.Pitch = 0.0f;
	RotatorDamageDirection.Roll = 0.0f;

	// Second, add appropriate yaw rotation to RotatorDamageDirection via attack direction
	switch ((m_AttackDefinitionREF->m_AttackerAttackStateREF)->m_AttackDirection)
	{
	case EDirectionAttack6Ways::Front:
	{
		break;
	}
	case EDirectionAttack6Ways::Back:
	{
		RotatorDamageDirection.Yaw += 180.0f;
		break;
	}
	case EDirectionAttack6Ways::Left:
	{
		RotatorDamageDirection.Yaw -= 90.0f;
		break;
	}
	case EDirectionAttack6Ways::Right:
	{
		RotatorDamageDirection.Yaw += 90.0f;
		break;
	}
	}

	// Calculated angle to play montage using RotatorDamageDirection
	float DamageAngle = ULibrary_CustomMath::TwoVectorsAngle_Degrees180(UKismetMathLibrary::GetForwardVector(m_Character_EnemyCombatTestingREF->GetActorRotation()), UKismetMathLibrary::GetForwardVector(RotatorDamageDirection));

	// Front, Back, Left and Right attack direction
		// Display damage montage (with 4 direction F, B, L, R) via DamageAngle
	FString DirectionString;
	FString MontageIDString;
	if (DamageAngle >= -45.0f && DamageAngle <= 45.0f) DirectionString = TEXT("F");
	else if (DamageAngle > -135.0f && DamageAngle < -45.0f) DirectionString = TEXT("L");
	else if (DamageAngle > 45.0f && DamageAngle < 135.0f) DirectionString = TEXT("R");
	else DirectionString = TEXT("B");

	switch ((m_AttackDefinitionREF->m_AttackerAttackStateREF)->m_HitType)
	{
	case EHitType::LightAttack:
	{
		MontageIDString = TEXT("Damage_Light_") + DirectionString + TEXT("_01_Inplace");
		break;
	}
	case EHitType::LightPush:
	{
		MontageIDString = TEXT("Damage_LightPush_") + DirectionString + TEXT("_01");
		break;
	}
	case EHitType::Push:
	{
		MontageIDString = TEXT("Damage_Push_") + DirectionString + TEXT("_01");
		break;
	}
	case EHitType::LowTakeDown:
	{
		MontageIDString = TEXT("Damage_TakeDown_Low_F_01");
		break;
	}
	}

	// Check if attack state implementing control attacked position
	if (m_AttackDefinitionREF->m_AttackerAttackStateREF->b_DoControlPostion == false)
	{
		m_Character_EnemyCombatTestingREF->PlayMontageFromTable_DamageMontage(FName(MontageIDString));
	}
	else
	{
		m_Character_EnemyCombatTestingREF->DisableRootMotion(m_AttackDefinitionREF->m_AttackerAttackStateREF->m_ControlPositionTime);
		m_Character_EnemyCombatTestingREF->PlayMontageFromTable_DamageMontage(FName(MontageIDString), m_AttackDefinitionREF->m_AttackerAttackStateREF->m_ControlPositionTime);
		FVector NextLocation = ULibrary_CustomMath::WorldLocationOfRelativeLocationToActor(m_AttackDefinitionREF->m_AttackerActor, m_AttackDefinitionREF->m_AttackerAttackStateREF->m_ControlPositionOffset);
		m_Character_EnemyCombatTestingREF->MoveToLocation(NextLocation, m_AttackDefinitionREF->m_AttackerAttackStateREF->m_ControlPositionTime);
	}
}

