// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "PlayerHumanState_UnarmedDash.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_UnarmedDash : public UPlayerHuman_BaseState
{
	GENERATED_BODY()
	
/**
 * Properties
 */
public:
protected:
private:
	const float c_CooldownTime = 1.0f;
	const float c_TargetArmLengthFollow_01 = -40.0f;

	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;
	FDelegate_ActionSignature* m_EndMontage_DelegateREF;
	FDelegate_ActionSignature* m_AnimNotify_01_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;
	bool b_CanBreakOut;


/**
 * Functions
 */
public:
	UPlayerHumanState_UnarmedDash();
	void EnterState() override;
	void TickState(float p_DeltaTime) override;
	void ExitState() override;

	void BindInputHandlingFunctions(AController* p_PlayerController) override;
	void UnBindInputHandlingFunctions() override;
protected:
private:
	void HandleInput_MoveRight(float p_AxisValue);
	void HandleInput_MoveForward(float p_AxisValue);
	void HandleAction_EndMontage();
	void HandleAction_AnimNotify_01();
	void PlayDashMontage();
};
