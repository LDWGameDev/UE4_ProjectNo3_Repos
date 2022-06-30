// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "System/CombatSystem/System_CombatContainer.h"
#include "PlayerHumanState_AssassinHA_C1_1.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_AssassinHA_C1_1 : public UPlayerHuman_BaseState
{
	GENERATED_BODY()
	

/**
 * Properties
 */

public:

protected:

private:
	const float c_AdditionArmLength = -70.0f;
	const float c_AdditionArmLength_2 = 100.0f;
	const FVector c_SocketOffset = FVector(0.0f, 60.0f, -60.0);
	const FVector c_SocketOffset_2 = FVector(0.0f, 60.0f, 40.0f);

	TArray<FStruct_SphereTrace_Offset> m_Hitboxes_01;
	TArray<FStruct_SphereTrace_Offset> m_Hitboxes_02;
	FStruct_AttackStateDefinition m_AttackStateDefinition_01 = FStruct_AttackStateDefinition(EHitType::LowTakeDown, EDirectionAttack6Ways::Front, true, FVector(250.0f, 0.0f, 100.0f), 0.75f);
	FStruct_AttackStateDefinition m_AttackStateDefinition_02 = FStruct_AttackStateDefinition(EHitType::Knock, EDirectionAttack6Ways::Up, true, FVector(400.0f, 0.0f, 100.0f), 1.5f);

	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;
	FDelegate_ActionSignature* m_HeavyAttackStart_DelegateREF;
	FDelegate_ActionSignature* m_AnimNotify_01_DelegateREF;
	FDelegate_ActionSignature* m_AnimNotify_02_DelegateREF;
	FDelegate_ActionSignature* m_EndAttack_01_DelegateREF;
	FDelegate_ActionSignature* m_TriggerAttack_01_DelegateREF;
	FDelegate_ActionSignature* m_TriggerAttack_02_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;
	bool b_CanBreakOut;
	bool b_HasTriggerHeavyAttack;


/**
 * Functions
 */

public:
	UPlayerHumanState_AssassinHA_C1_1();
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
	void HandleAction_AnimNotify_02();
	void HandleAction_EndAttack_01();
	void HandleTriggerAttack_01();
	void HandleTriggerAttack_02();
};
