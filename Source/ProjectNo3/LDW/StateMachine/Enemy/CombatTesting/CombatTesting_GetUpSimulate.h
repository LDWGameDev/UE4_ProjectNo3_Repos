// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatTesting_BaseState.h"
#include "CombatTesting_GetUpSimulate.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UCombatTesting_GetUpSimulate : public UCombatTesting_BaseState
{
	GENERATED_BODY()
	

/**
 * Properties
 */
public:
protected:
private:
	bool b_SavedIsFacingUp;


/**
 * Functions
 */
public:
	UCombatTesting_GetUpSimulate();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;

	virtual void HandleEndMontage() override;

protected:
private:
};
