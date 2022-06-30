// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_BaseState.h"
#include "CombatTesting_FallState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UCombatTesting_FallState : public UCombatTesting_BaseState
{
	GENERATED_BODY()
	

/**
 * Properties
 */
public:
protected:
private:
	FDelegate_EnemyBaseActionSignature* m_LandStart_DelegateREF;
	bool b_HasLanded;

/**
 * Functions
 */
public:
	UCombatTesting_FallState();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;
	virtual void InitState(UStateMachineComponent* p_StateMachineREF, AActor* p_CharacterEnemeyREF) override;

protected:
private:
	void HandleDelegate_LandStart();
};
