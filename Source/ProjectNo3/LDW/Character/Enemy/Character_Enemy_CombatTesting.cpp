// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Enemy_CombatTesting.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



ACharacter_Enemy_CombatTesting::ACharacter_Enemy_CombatTesting()
{
	// Set CapsuleComponent defaults
	GetCapsuleComponent()->InitCapsuleSize(40.0f, 86.0f);

	// Set CharacterMovement defaults
	GetCharacterMovement()->GravityScale = 2.5f;

}

void ACharacter_Enemy_CombatTesting::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacter_Enemy_CombatTesting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}





/**
 * Interface functions
 */

void ACharacter_Enemy_CombatTesting::TakeHit(FStruct_AttackDefinition& p_AttackDefinition)
{
	Super::TakeHit(p_AttackDefinition);
	if (!p_AttackDefinition.CheckValid()) return;

	switch ((p_AttackDefinition.m_AttackerAttackStateREF)->m_HitType)
	{
	case EHitType::LightAttack:
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy_CombatTesting TakeHit()     LightAttack"));
		break;
	}
	case EHitType::Knock:
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy_CombatTesting TakeHit()     Knock"));
		break;
	}
	}
}
