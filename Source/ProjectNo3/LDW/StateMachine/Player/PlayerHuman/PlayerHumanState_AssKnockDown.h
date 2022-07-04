// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "PlayerHumanState_AssKnockDown.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_AssKnockDown : public UPlayerHuman_BaseState
{
	GENERATED_BODY()
	

/**
 * Properties
 */

public:
protected:
private:
	const float c_SnapLocationSpeed = 5.0f;
	FVector m_SavedActorOffsetLocation;
	bool b_HasSimulatePhysics;

/**
 * Functions
 */

public:
	UPlayerHumanState_AssKnockDown();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;
	virtual void BindInputHandlingFunctions(AController* p_PlayerController) override;
	virtual void UnBindInputHandlingFunctions() override;
protected:
private:
	void StartSimulatePhysics();
};
