// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "System/CombatSystem/System_CombatContainer.h"
#include "PlayerHumanState_AssassinHA_C2_4.generated.h"



/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_AssassinHA_C2_4 : public UPlayerHuman_BaseState
{
	GENERATED_BODY()



/**
 * Properties
 */

public:
	UPROPERTY()
		AActor* m_TargetActor;
protected:

private:
	const float c_AdditionArmLength = -90.0f;
	const FVector c_SocketOffset = FVector(0.0f, 80.0f, 20.0f);
	TArray<FStruct_SphereTrace_Offset> m_Hitboxes_01;
	TArray<FStruct_SphereTrace_Offset> m_Hitboxes_02;
	FStruct_AttackStateDefinition m_AttackState_01 = FStruct_AttackStateDefinition(EHitType::LightPush, EDirectionAttack6Ways::Front, true, FVector(200.0f, 20.0f, 0.0f), 0.1f);
	FStruct_AttackStateDefinition m_AttackState_02 = FStruct_AttackStateDefinition(EHitType::LightPush, EDirectionAttack6Ways::Right, false, FVector(), 0.0f);
	FStruct_AttackStateDefinition m_AttackState_03 = FStruct_AttackStateDefinition(EHitType::LightPush, EDirectionAttack6Ways::Left, false, FVector(), 0.0f);
	FStruct_AttackStateDefinition m_AttackState_04 = FStruct_AttackStateDefinition(EHitType::Push, EDirectionAttack6Ways::Front, true, FVector(430.0f, 120.0f, 0.0f), 0.6f);
	FStruct_AttackStateDefinition m_AttackState_05 = FStruct_AttackStateDefinition(EHitType::KnockSimulate, EDirectionAttack6Ways::Front, false, FVector(), 0.0f);

	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;
	bool b_CanBreakOut;
	bool b_CameraSequenceValid;



/**
 * Functions
 */

public:
	UPlayerHumanState_AssassinHA_C2_4();
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
