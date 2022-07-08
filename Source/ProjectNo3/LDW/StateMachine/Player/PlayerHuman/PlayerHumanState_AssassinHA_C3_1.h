
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman_BaseState.h"
#include "PlayerHumanState_AssassinHA_C3_1.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHumanState_AssassinHA_C3_1 : public UPlayerHuman_BaseState
{
	GENERATED_BODY()


/**
 * Properties
 */

public:
	UPROPERTY()
		AActor* m_GotHitActor;

protected:

private:
	const float c_AdditionalArmLength = 80.0f;
	TArray<FRotator> m_ThrowingWeaponsRotationList;
	FStruct_AttackStateDefinition m_AttackState_01 = FStruct_AttackStateDefinition(EHitType::Push, EDirectionAttack6Ways::Front, false, FVector(), 0.0f);

	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;

	float m_MoveForwardValue;
	float m_MoveRightValue;
	bool b_CanBreakOut;



/**
 * Functions
 */

public:
	UPlayerHumanState_AssassinHA_C3_1();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;
	virtual void BindInputHandlingFunctions(AController* p_PlayerController) override;
	virtual void UnBindInputHandlingFunctions() override;

	virtual void HandleAnimNotify_AnimNotify_01() override;
	virtual void HandleAnimNotify_EndMontage() override;
	virtual void HandleAnimNotify_TriggerAttack_01() override;


protected:

private:
	void HandleAction_MoveForward(float p_Value);
	void HandleAction_MoveRight(float p_Value);
};
