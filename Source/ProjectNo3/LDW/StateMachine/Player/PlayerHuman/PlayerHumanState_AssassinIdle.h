// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "PlayerHumanState_AssassinIdle.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_AssassinIdle : public UPlayerHuman_BaseState
{
	GENERATED_BODY()

/**
 * Properties
 */
public:
protected:
private:
	const float c_Dash2_HoldingTime = 0.5f;

	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;
	FDelegate_JumpSignature* m_JumpPressed_DelegateREF;
	FDelegate_ActionSignature* m_DashStart_DelegateREF;
	FDelegate_ActionSignature* m_LightAttack_DelegateREF;
	FDelegate_ActionSignature* m_HeavyAttack_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;

/**
 * Functions
 */
public:
	UPlayerHumanState_AssassinIdle();
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
	void HandleAction_LightAttack();
	void HandleAction_HeavyAttackStart();
};
