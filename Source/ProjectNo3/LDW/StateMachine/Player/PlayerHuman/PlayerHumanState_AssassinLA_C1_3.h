// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "System/CombatSystem/System_CombatContainer.h"
#include "PlayerHumanState_AssassinLA_C1_3.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_AssassinLA_C1_3 : public UPlayerHuman_BaseState
{
	GENERATED_BODY()
	

/**
 * Properties
 */

public:

protected:

private:
	const float c_CooldownTime = 1.0f;
	const float c_AdditionalArmLength = -80.0f;
	const FVector c_SocketOffset = FVector(0.0f, 100.0f, 0.0f);
	FStruct_AttackStateDefinition m_AttackStateDefinition_01 = FStruct_AttackStateDefinition(EHitType::LightPush, EDirectionAttack6Ways::Front, false, FVector(), 0.0f);
	FStruct_AttackStateDefinition m_AttackStateDefinition_02 = FStruct_AttackStateDefinition(EHitType::Push, EDirectionAttack6Ways::Front, false, FVector(), 0.0f);
	FStruct_AttackStateDefinition m_AttackStateDefinition_03 = FStruct_AttackStateDefinition(EHitType::KnockSimulate, EDirectionAttack6Ways::Front, false, FVector(), 0.0f);

	TArray<FStruct_SphereTrace_Offset> m_Hitboxes_01;
	TArray<FStruct_SphereTrace_Offset> m_Hitboxes_02;
	TArray<FStruct_SphereTrace_Offset> m_Hitboxes_03;

	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;
	bool b_CanBreakOut;
	bool b_HasTriggerLightAttack;



/**
 * Functions
 */

public:
	UPlayerHumanState_AssassinLA_C1_3();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;
	virtual void BindInputHandlingFunctions(AController* p_PlayerController) override;
	virtual void UnBindInputHandlingFunctions() override;

	virtual void HandleAnimNotify_AnimNotify_01() override;
	virtual void HandleAnimNotify_EndMontage() override;
	virtual void HandleAnimNotify_TriggerAttack_01() override;
	virtual void HandleAnimNotify_TriggerAttack_02() override;
	virtual void HandleAnimNotify_TriggerAttack_03() override;

protected:

private:
	void HandleAction_MoveForward(float p_Value);
	void HandleAction_MoveRight(float p_Value);
};
