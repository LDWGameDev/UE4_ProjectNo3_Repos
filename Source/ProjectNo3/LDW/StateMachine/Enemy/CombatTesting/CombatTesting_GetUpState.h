// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_BaseState.h"
#include "CombatTesting_GetUpState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UCombatTesting_GetUpState : public UCombatTesting_BaseState
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
	UCombatTesting_GetUpState();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;

	// Override to get delegate reference and bind handling functions to delegates
	virtual void InitState(UStateMachineComponent* p_StateMachineREF, AActor* p_CharacterEnemeyREF) override;

protected:
private:
};
