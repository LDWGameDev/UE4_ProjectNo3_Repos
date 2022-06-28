// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/Enemy/EnemyBaseState.h"
#include "Character/Enemy/Character_Enemy_CombatTesting.h"
#include "CombatTesting_BaseState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UCombatTesting_BaseState : public UEnemyBaseState
{
	GENERATED_BODY()
	
/**
 * Properties
 */
public:
protected:
	ACharacter_Enemy_CombatTesting* m_Character_EnemyCombatTestingREF;
private:


/**
 * Functions
 */
public:
	UCombatTesting_BaseState();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;

	// Initialize state, set references (m_CharacterEnemyBaseREF, m_StateMachineComponentREF, m_Character_EnemyCombatTestingREF)
	// Called when create state in character
	virtual void InitState(UStateMachineComponent* p_StateMachineREF, AActor* p_CharacterEnemeyREF) override;

protected:
private:
};
