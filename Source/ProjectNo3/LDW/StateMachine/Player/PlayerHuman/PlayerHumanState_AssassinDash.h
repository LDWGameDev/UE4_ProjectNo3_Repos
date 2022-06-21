// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "../../../Interface/Interface_PlayerControllerInput.h"
#include "PlayerHumanState_AssassinDash.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_AssassinDash : public UPlayerHuman_BaseState
{
	GENERATED_BODY()

/**
 * Properties
 */

public:

protected:

private:
	const float c_CooldownTime = 1.0f;
	const float c_AdditionArmLengthFollow_01 = 50.0f;

	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;
	FDelegate_ActionSignature* m_DashStart_DelegateREF;
	FDelegate_ActionSignature* m_EndMontage_DelegateREF;
	FDelegate_ActionSignature* m_AnimNotify_01_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;
	bool b_CanBreakOut;
	bool b_HasTriggerDashInput;


/**
 * Functions
 */

public:
	UPlayerHumanState_AssassinDash();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;
	virtual void BindInputHandlingFunctions(AController* p_PlayerController) override;
	virtual void UnBindInputHandlingFunctions() override;

protected:

private:
	void HandleInput_MoveRight(float p_AxisValue);
	void HandleInput_MoveForward(float p_AxisValue);
	void HandleAction_DashStart();
	void HandleAction_EndMontage();
	void HandleAction_AnimNotify_01();
	void PlayDashMontage();
};
