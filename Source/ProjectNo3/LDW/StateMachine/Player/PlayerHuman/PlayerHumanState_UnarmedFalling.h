// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "PlayerHumanState_UnarmedFalling.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_UnarmedFalling : public UPlayerHuman_BaseState
{
	GENERATED_BODY()
	

/**
 * Properties
 */
public:

protected:

private:
	const float c_MovingSpeed = 120.0f;

	FDelegate1_MovementSignature* m_MoveForwardDelegateREF;
	FDelegate1_MovementSignature* m_MoveRightDelegateREF;
	FDelegate_LandedSignature* m_Landed_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;
	bool b_HasLanded;


/**
 * Functions
 */
public:
	UPlayerHumanState_UnarmedFalling();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;
	virtual void BindInputHandlingFunctions(AController* p_PlayerController) override;
	virtual void UnBindInputHandlingFunctions() override;

protected:

private:
	void HandleInput_MoveForward(float p_AxisValue);
	void HandleInput_MoveRight(float p_AxisValue);
	void HandleEvent_Landed();
};
