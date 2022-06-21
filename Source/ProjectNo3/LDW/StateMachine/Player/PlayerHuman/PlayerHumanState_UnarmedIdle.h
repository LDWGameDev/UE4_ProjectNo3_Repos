// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "../../../Interface/Interface_PlayerControllerInput.h"
#include "PlayerHumanState_UnarmedIdle.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_UnarmedIdle : public UPlayerHuman_BaseState
{
	GENERATED_BODY()

/**
 * Properties 
 */

public:
protected:
private:
	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;
	FDelegate_JumpSignature* m_JumpPressed_DelegateREF;
	FDelegate_ActionSignature* m_DashStart_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;


/**
 * Functions
 */

public:
	UPlayerHumanState_UnarmedIdle();
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
	void HandleAction_DashStart();
};
