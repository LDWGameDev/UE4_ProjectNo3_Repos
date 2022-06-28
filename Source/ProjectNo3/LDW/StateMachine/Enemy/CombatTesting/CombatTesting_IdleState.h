// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/Enemy/CombatTesting/CombatTesting_BaseState.h"
#include "CombatTesting_IdleState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UCombatTesting_IdleState : public UCombatTesting_BaseState
{
	GENERATED_BODY()
	

/**
 * Properties
 */
public:
protected:
private:


/**
 * Functions
 */
public:
	UCombatTesting_IdleState();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;

protected:
private:
};
