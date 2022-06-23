// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character_EnemyBase.generated.h"

UCLASS(Abstract)
class PROJECTNO3_API ACharacter_EnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacter_EnemyBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
