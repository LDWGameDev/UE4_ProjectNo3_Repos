// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_Enemy_CombatTesting.h"
#include "Character/Enemy/Character_Enemy_CombatTesting.h"


/**
 * Override functions
 */

void UAnimInstance_Enemy_CombatTesting::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	m_Character_EnemyCombatTestingREF = Cast<ACharacter_Enemy_CombatTesting>(TryGetPawnOwner());
	b_IsInAir = false;
	b_IsSimulatingPhysics_DamageKnockOut = false;
	m_FallingIndex = 0;
}

void UAnimInstance_Enemy_CombatTesting::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (m_Character_EnemyCombatTestingREF == nullptr) return;
}

void UAnimInstance_Enemy_CombatTesting::CheckCurrentState(UBaseState* p_CurrentState)
{
	if (p_CurrentState == nullptr || p_CurrentState->GetStateTag() == nullptr || !p_CurrentState->GetStateTag()->IsValid()) return;
	if (p_CurrentState->GetStateTag()->MatchesAny(m_TagContainer_InAirStates)) b_IsInAir = true;
	else b_IsInAir = false;
}

