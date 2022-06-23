// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "PlayerHumanState_UnarmedJog.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_UnarmedJog : public UPlayerHuman_BaseState
{
	GENERATED_BODY()

/**
 * Properties
 */
public:

protected:

private:
	const float m_SpeedToStop = 30.0f;
	const float c_MovingSpeed = 400.0f;

	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;
	FDelegate_JumpSignature* m_JumpPressed_DelegateREF;
	FDelegate_StartFallingSignature* m_StartFalling_DelegateREF;
	FDelegate_ActionSignature* m_DashStart_DelegateREF;
	FDelegate_ActionSignature* m_RunStart_DelegateREF;
	FDelegate_ActionSignature* m_RunEnd_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;
	bool b_IsHoldingRunKey;
	

/**
 * Functions
 */
public:
	UPlayerHumanState_UnarmedJog();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;
	virtual void BindInputHandlingFunctions(AController* p_PlayerController) override;
	virtual void UnBindInputHandlingFunctions() override;
protected:
private:
	void HandleInput_MoveRight(float p_AxisValue);
	void HandleInput_MoveForward(float p_AxisValue);
	void HandleInput_JumpPressed();
	void HandleEvent_StartFalling();
	void HandleAction_DashStart();
	void HandleAction_RunStart();
	void HandleAction_RunEnd();
};
