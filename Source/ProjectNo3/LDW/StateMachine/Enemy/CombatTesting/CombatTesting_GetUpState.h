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
	int32 m_GetUpIndex;
protected:
private:


/**
 * Functions
 */
public:
	UCombatTesting_GetUpState();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;

	virtual void HandleEndMontage() override;

protected:
private:
};
