// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Library/Library_Enum.h"
#include "PlayerHuman_BaseState.h"
#include "PlayerHumanState_AssassinDash_2.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_AssassinDash_2 : public UPlayerHuman_BaseState
{
	GENERATED_BODY()
	
/**
 * Properties
 */
public:
	EDirection8Ways m_SavedDirection_Dash1;
	FRotator m_SavedCharacterRotator_Dash1;

protected:
private:
	const float c_CooldownTime = 1.0f;
	const float c_AdditionArmLengthFollow_01 = 75.0f;

	FDelegate1_MovementSignature* m_DelegateREF_MoveForward;
	FDelegate1_MovementSignature* m_DelegateREF_MoveRight;
	FDelegate_ActionSignature* m_DelegateREF_EndMontage_02;
	FDelegate_ActionSignature* m_DelegateREF_AnimNotify_01;

	float m_MoveForwardValue;
	float m_MoveRightValue;
	bool b_CanBreakOut;

/**
 * Functions
 */
public:
	UPlayerHumanState_AssassinDash_2();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;
	virtual void BindInputHandlingFunctions(AController* p_PlayerController) override;
	virtual void UnBindInputHandlingFunctions() override;
protected:
private:
	void HandleAction_MoveForward(float p_Value);
	void HandleAction_MoveRight(float p_Value);
	void HandleAction_EndMontage_02();
	void HandleAction_AnimNotify_01();
	void PlayMontage();
};
