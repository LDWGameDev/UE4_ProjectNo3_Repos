// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "PlayerHumanState_AssassinFalling.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_AssassinFalling : public UPlayerHuman_BaseState
{
	GENERATED_BODY()
	

/**
 * Properties
 */

public:

protected:

private:
	const float c_MovingSpeed = 140.0f;

	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;
	FDelegate_LandedSignature* m_Landed_DelegateREF;

	bool b_HasLanded;
	float m_MoveForwardValue;
	float m_MoveRightValue;


/**
 * Functions
 */

public:
	UPlayerHumanState_AssassinFalling();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;
	virtual void BindInputHandlingFunctions(AController* p_PlayerController) override;
	virtual void UnBindInputHandlingFunctions() override;

protected:

private:
	void HandleInput_MoveRight(float p_AxisValue);
	void HandleInput_MoveForward(float p_AxisValue);
	void HandleAction_Landed();
};
