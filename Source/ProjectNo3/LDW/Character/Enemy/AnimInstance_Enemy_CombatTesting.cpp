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
}

void UAnimInstance_Enemy_CombatTesting::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (m_Character_EnemyCombatTestingREF == nullptr) return;
}


