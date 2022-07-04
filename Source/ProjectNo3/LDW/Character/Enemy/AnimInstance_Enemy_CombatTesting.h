// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance_EnemyBase.h"
#include "GameplayTagContainer.h"
#include "StateMachine/BaseState.h"
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
	UPROPERTY(EditDefaultsOnly)
		FGameplayTagContainer m_TagContainer_InAirStates;
	UPROPERTY(BlueprintReadOnly)
		bool b_IsSimulatingPhysics_DamageKnockOut;
	UPROPERTY(BlueprintReadOnly)
		bool b_IsInAir;
	UPROPERTY(BlueprintReadOnly)
		int32 m_FallingIndex;

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

	void CheckCurrentState(UBaseState* p_CurrentState);
protected:
private:
};
