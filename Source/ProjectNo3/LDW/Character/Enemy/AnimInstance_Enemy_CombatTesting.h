// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance_EnemyBase.h"
#include "AnimInstance_Enemy_CombatTesting.generated.h"


class ACharacter_Enemy_CombatTesting;

/**
 * 
 */

UCLASS()
class PROJECTNO3_API UAnimInstance_Enemy_CombatTesting : public UAnimInstance_EnemyBase
{
	GENERATED_BODY()
	

/**
 * Properties
 */
public:
	UPROPERTY(BlueprintReadOnly)
		bool b_IsSimulatingPhysics_DamageKnockOut;

protected:
private:
	UPROPERTY()
		ACharacter_Enemy_CombatTesting* m_Character_EnemyCombatTestingREF;

/**
 * Functions
 */
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
private:
};
