// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "System/CombatSystem/System_CombatContainer.h"
#include "PlayerHumanState_AssassinHA_C3_2.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_AssassinHA_C3_2 : public UPlayerHuman_BaseState
{
	GENERATED_BODY()
	


/**
 * Properties
 */
		
public:
		
protected:
		
private:
	const float c_AdditionArmLength = 90.0f;
	const FVector c_SocketOffset = FVector(0.0f, 60.0f, 0.0f);
	TArray<FStruct_SphereTrace_Offset> m_Hitboxes_01;
	TArray<FStruct_SphereTrace_Offset> m_Hitboxes_02;
	TArray<FStruct_SphereTrace_Offset> m_Hitboxes_03;
	TArray<FStruct_SphereTrace_Offset> m_Hitboxes_04;
	TArray<FStruct_SphereTrace_Offset> m_Hitboxes_05;

	FStruct_AttackStateDefinition m_AttackState_01 = FStruct_AttackStateDefinition(EHitType::Push, EDirectionAttack6Ways::Left, true, FVector(220.0f, -30.0f, 0.0f), 1.25f);
	FStruct_AttackStateDefinition m_AttackState_02 = FStruct_AttackStateDefinition(EHitType::Push, EDirectionAttack6Ways::Right, true, FVector(-200.0f, -50.0f, 0.0f), 1.25f);
	FStruct_AttackStateDefinition m_AttackState_03 = FStruct_AttackStateDefinition(EHitType::Push, EDirectionAttack6Ways::Right, true, FVector(60.0f, -180.0f, 0.0f), 1.25f);
	FStruct_AttackStateDefinition m_AttackState_04 = FStruct_AttackStateDefinition(EHitType::Push, EDirectionAttack6Ways::Right, true, FVector(-30.0f, 140.0f, 0.0f), 1.0f);
	FStruct_AttackStateDefinition m_AttackState_05 = FStruct_AttackStateDefinition(EHitType::KnockSimulate, EDirectionAttack6Ways::Front, false, FVector(), 0.0f);

	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;
	int32 m_AttackIndex;
	bool b_CanBreakOut;
	bool b_CameraSequenceValid;



/**
 * Functions
 */
		
public:
	UPlayerHumanState_AssassinHA_C3_2();
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
	virtual void HandleAnimNotify_TriggerAttack_04() override;
	virtual void HandleAnimNotify_TriggerAttack_05() override;
		
protected:
		
private:
	void HandleAction_MoveForward(float p_Value);
	void HandleAction_MoveRight(float p_Value);
};
