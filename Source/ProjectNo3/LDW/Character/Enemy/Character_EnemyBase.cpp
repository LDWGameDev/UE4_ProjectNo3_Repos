// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/Character_EnemyBase.h"

ACharacter_EnemyBase::ACharacter_EnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

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