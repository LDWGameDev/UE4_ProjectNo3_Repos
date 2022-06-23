// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_EnemyBase.h"
#include "System/CombatSystem/System_CombatContainer.h"



ACharacter_EnemyBase::ACharacter_EnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

}




/**
 * Override functions
 */

void ACharacter_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACharacter_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacter_EnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}




/**
 * Interface functions
 */

void ACharacter_EnemyBase::TakeHit(FStruct_AttackDefinition& p_AttackDefinition)
{

}

const FGameplayTagContainer& ACharacter_EnemyBase::GetTagContainer()
{
	return m_TagContainer;
}

