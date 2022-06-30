// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatTesting_BaseState.h"
#include "System/CombatSystem/System_CombatContainer.h"
#include "CombatTesting_DamageState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UCombatTesting_DamageState : public UCombatTesting_BaseState
{
	GENERATED_BODY()
	

/**
 * Properties
 */
public:
	FStruct_AttackDefinition* m_AttackDefinitionREF;

protected:
private:


/**
 * Functions
 */
public:
	UCombatTesting_DamageState();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;

	virtual void HandleEndMontage() override;

protected:
private:
	void HandleGetDamage();
};
