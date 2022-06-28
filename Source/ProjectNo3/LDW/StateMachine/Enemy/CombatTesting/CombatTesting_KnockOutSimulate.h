// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatTesting_BaseState.h"
#include "System/CombatSystem/System_CombatContainer.h"
#include "CombatTesting_KnockOutSimulate.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UCombatTesting_KnockOutSimulate : public UCombatTesting_BaseState
{
	GENERATED_BODY()
	

/**
 * Properties
 */
public:
	FStruct_AttackDefinition* m_AttackDefinitionREF;

protected:
private:
	const float c_SnapCharacterPositionSpeed = 5.0f;
	const float c_TimeToGetUpAfterSimulating = 2.0f;
	bool b_HasSimulatedPhysics;
	FVector m_SavedCharacterOffsetLocation;


/**
 * Functions
 */
public:
	UCombatTesting_KnockOutSimulate();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;

	virtual void HandleAnimNotify_01() override;

protected:
private:
	void PlayKnockOutMontage();
	void StartSimulating();
};
