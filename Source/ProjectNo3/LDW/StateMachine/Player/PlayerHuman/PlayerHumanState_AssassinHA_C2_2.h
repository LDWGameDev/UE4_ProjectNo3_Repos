// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "../../../Interface/Interface_PlayerControllerInput.h"
#include "PlayerHumanState_AssassinHA_C2_2.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_AssassinHA_C2_2 : public UPlayerHuman_BaseState
{
	GENERATED_BODY()
	

/**
 * Properties
 */

public:

protected:

private:
	const float c_AdditionArmLength = -20.0f;
	const FVector c_SocketOffset = FVector(0.0f, 50.0f, 0.0f);

	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;
	FDelegate_ActionSignature* m_HeavyAttackStart_DelegateREF;
	FDelegate_ActionSignature* m_AnimNotify_01_DelegateREF;
	FDelegate_ActionSignature* m_EndAttack_02_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;
	bool b_CanBreakOut;
	bool b_HasTriggerHeavyAttack;



/**
 * Functions
 */

public:
	UPlayerHumanState_AssassinHA_C2_2();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;
	virtual void BindInputHandlingFunctions(AController* p_PlayerController) override;
	virtual void UnBindInputHandlingFunctions() override;

protected:

private:
	void HandleAction_MoveForward(float p_Value);
	void HandleAction_MoveRight(float p_Value);
	void HandleAction_HeavyAttackStart();
	void HandleAction_AnimNotify_01();
	void HandleAction_EndAttack_02();
};