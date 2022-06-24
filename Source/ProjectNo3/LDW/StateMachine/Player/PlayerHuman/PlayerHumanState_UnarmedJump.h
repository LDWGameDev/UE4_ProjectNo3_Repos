// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PlayerHuman_BaseState.h"
#include "PlayerHumanState_UnarmedJump.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_UnarmedJump : public UPlayerHuman_BaseState
{
	GENERATED_BODY()
	
/**
 * Properties 
 */
public:
protected:
private:
	const float c_DefaultMovingSpeed = 180.0f;
	const float c_DefaultJumpForce = 1200.0f;
	const float c_AdditionalArmLengthFollow_01 = -40.0f;

	FDelegate1_MovementSignature* m_MoveForwardDelegateREF;
	FDelegate1_MovementSignature* m_MoveRightDelegateREF;
	FDelegate_LandedSignature* m_Landed_DelegateREF;
	FDelegate_ActionSignature* m_EndMontage_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;


/**
 * Functions
 */
public:
	UPlayerHumanState_UnarmedJump();
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
	void HandleEvent_EndAction();
};
