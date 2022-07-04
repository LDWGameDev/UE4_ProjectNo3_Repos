// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "PlayerHumanState_AssassinLA_C1_1.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_AssassinLA_C1_1 : public UPlayerHuman_BaseState
{
	GENERATED_BODY()
	


/**
 * Properties
 */

public:

protected:

private:
	const float c_CooldownTime = 1.0f;
	const float c_AdditionalArmLength = 20.0f;
	FStruct_AttackStateDefinition m_AttackStateDefinition_01 = FStruct_AttackStateDefinition(EHitType::LightAttack, EDirectionAttack6Ways::Front, false, FVector(0.0f, 0.0f, 0.0f), 0.0f);
	FStruct_AttackStateDefinition m_AttackStateDefinition_02 = FStruct_AttackStateDefinition(EHitType::LightPush, EDirectionAttack6Ways::Front, false, FVector(0.0f, 0.0f, 0.0f), 0.0f);
	TArray<FStruct_SphereTrace_Offset> m_Hitboxes_01;
	TArray<FStruct_SphereTrace_Offset> m_Hitboxes_02;

	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;
	FDelegate_ActionSignature* m_LightAttack_DelegateREF;
	FDelegate_ActionSignature* m_EndAttack_01_DelegateREF;
	FDelegate_ActionSignature* m_AnimNotify_01_DelegateREF;
	FDelegate_ActionSignature* m_TriggerAttack_01_DelegateREF;
	FDelegate_ActionSignature* m_TriggerAttack_02_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;
	bool b_CanBreakOut;
	bool b_HasTriggerLA_C1_2;
	bool b_ShoudlResetArmLength;
	TArray<AActor*> m_GetHitActors;



/**
 * Functions
 */

public:
	UPlayerHumanState_AssassinLA_C1_1();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;
	virtual void BindInputHandlingFunctions(AController* p_PlayerController) override;
	virtual void UnBindInputHandlingFunctions() override;

protected:

private:
	void HandleAction_MoveForward(float p_Value);
	void HandleAction_MoveRight(float p_Value);
	void HandleAction_LightAttack();
	void HandleAction_EndAttack_01();
	void HandleAction_AnimNotify_01();
	void HandleAction_TriggerAttack_01();
	void HandleAction_TriggerAttack_02();
};
