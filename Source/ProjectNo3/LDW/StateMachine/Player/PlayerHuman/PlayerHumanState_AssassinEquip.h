// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "PlayerHumanState_AssassinEquip.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_AssassinEquip : public UPlayerHuman_BaseState
{
	GENERATED_BODY()
	
/**
 * Properties
 */
public:
protected:
private:
	const float c_AdditionalArmLength = -15.0f;

	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;
	FDelegate_ActionSignature* m_EndMontage_DelegateREF;
	FDelegate_ActionSignature* m_AnimNotify_01_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;

/**
 * Functions
 */
public:
	UPlayerHumanState_AssassinEquip();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;
	virtual void BindInputHandlingFunctions(AController* p_PlayerController) override;
	virtual void UnBindInputHandlingFunctions() override;
protected:
private:
	void HandleDelegate_MoveForward(float p_Value);
	void HandleDelegate_MoveRight(float p_Value);
	void HandleAction_EndMontage();
	void HandleAction_AnimNotify_01();
};
