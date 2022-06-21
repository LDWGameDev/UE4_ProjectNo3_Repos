// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "../../../Interface/Interface_PlayerControllerInput.h"
#include "PlayerHumanState_AssassinJog.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_AssassinJog : public UPlayerHuman_BaseState
{
	GENERATED_BODY()
	

/**
 * Properties
 */
public:
protected:
private:
	const float c_AdditionalArmLength_01 = 30.0f;
	const float c_StoppingSpeed = 30.0f;
	const float c_MovingSpeed = 450.0f;
	const float c_Dash2_HoldingTime = 0.5f;

	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;
	FDelegate_JumpSignature* m_JumpPressed_DelegateREF;
	FDelegate_StartFallingSignature* m_StartFalling_DelegateREF;
	FDelegate_ActionSignature* m_DashStart_DelegateREF;
	FDelegate_ActionSignature* m_RunStart_DelegateREF;
	FDelegate_ActionSignature* m_RunEnd_DelegateREF;
	FDelegate_ActionSignature* m_LightAttackStart_DelegateREF;
	FDelegate_ActionSignature* m_HeavyAttackStart_DelegateREF;


	bool b_IsHoldingRunKey;
	float m_MoveForwardValue;
	float m_MoveRightValue;

	/**
	 * Functions
	 */
public:
	UPlayerHumanState_AssassinJog();
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
	void HandleAction_RunStart();
	void HandleAction_RunEnd();
	void HandleAction_StartFalling();
	void HandleAction_LightAttackStart();
	void HandleAction_HeavyAttackStart();
};
