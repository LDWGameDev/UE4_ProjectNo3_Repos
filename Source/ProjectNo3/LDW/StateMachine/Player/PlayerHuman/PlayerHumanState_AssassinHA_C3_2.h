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

	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;
	FDelegate_ActionSignature* m_AnimNotify_01_DelegateREF;
	FDelegate_ActionSignature* m_AnimNotify_02_DelegateREF;
	FDelegate_ActionSignature* m_EndAttack_02_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;
	int32 m_AttackIndex;
	bool b_CanBreakOut;
	bool b_CameraSequenceValid;

	FVector m_SavedCameraLocation_1;
	FVector m_SavedCameraLocation_2;
	FVector m_SavedCameraLocation_3;
	FVector m_SavedCameraLocation_4;
	FVector m_SavedCameraLookAtLocation_1;
	FVector m_SavedCameraLookAtLocation_2;
	FVector m_SavedCameraLookAtLocation_3;
	FVector m_SavedCameraLookAtLocation_4;
		
		
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
		
protected:
		
private:
	void HandleAction_MoveForward(float p_Value);
	void HandleAction_MoveRight(float p_Value);
	void HandleAction_AnimNotify_01();
	void HandleAction_AnimNotify_02();
	void HandleAction_EndAttack_02();
};
