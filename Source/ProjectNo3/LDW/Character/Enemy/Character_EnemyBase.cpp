// Fill out your copyright notice in the Description page of Project Settings.


#include "LDW/Character/Enemy/Character_EnemyBase.h"

// Sets default values
ACharacter_EnemyBase::ACharacter_EnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacter_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacter_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacter_EnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

