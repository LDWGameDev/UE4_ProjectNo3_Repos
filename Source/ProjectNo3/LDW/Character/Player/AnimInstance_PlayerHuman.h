// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"
#include "StateMachine/StateMachineComponent.h"
#include "AnimInstance_PlayerHuman.generated.h"

class ACharacter_PlayerHuman;

UCLASS(Blueprintable)
class PROJECTNO3_API UAnimInstance_PlayerHuman : public UAnimInstance
{
	GENERATED_BODY()


/**
 * Properties
 */

public:
	UPROPERTY(EditDefaultsOnly)
		FGameplayTagContainer m_TagContainer_InAirStates;
	UPROPERTY(EditDefaultsOnly)
		FGameplayTagContainer m_TagContainer_LocomotionAnimationStates;

	UPROPERTY(BlueprintReadOnly)
		float m_MovingSpeed;
	UPROPERTY(BlueprintReadOnly)
		float m_UnarmedIdleIndex;
	UPROPERTY(BlueprintReadOnly)
		float m_MovingDirectionAngle;
	UPROPERTY(BlueprintReadOnly)
		float m_SavedMovingDirectionAngle;
	UPROPERTY(BlueprintReadOnly)
		float m_JogStop_StartPositionCurveValue;
	UPROPERTY(BlueprintReadOnly)
		bool b_IsInAir;
	UPROPERTY(BlueprintReadOnly)
		bool b_ShouldLocomotionAnimation;
	UPROPERTY(BlueprintReadOnly)
		bool b_IsSimulatingPhysics_KnockDown;
	UPROPERTY(BlueprintReadOnly)
		int32 m_AnimSetIndex;
	UPROPERTY(BlueprintReadOnly)
		float m_LeanForwardValue;
	UPROPERTY(BlueprintReadOnly)
		float m_LeanRightValue;

	// Control Rig usage
	UPROPERTY(BlueprintReadOnly)
		bool b_DoFeetIK;
	UPROPERTY(BlueprintReadOnly)
		float m_ControlRigFootIKAlpha;

protected:
private:
	float m_SavedLastFrameMovingSpeed;



/**
 * Functions
 */

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Call Function")
		void SetUpJogStop();

	// Handle AnimNotify functions, implemented in CurrentState (casted to PlayerHuman_BaseState) of StateMachine
	UFUNCTION(BlueprintCallable)
		void HandleAnimNotify_AnimNotify_01();
	UFUNCTION(BlueprintCallable)
		void HandleAnimNotify_AnimNotify_02();
	UFUNCTION(BlueprintCallable)
		void HandleAnimNotify_AnimNotify_03();
	UFUNCTION(BlueprintCallable)
		void HandleAnimNotify_TriggerAttack_01();
	UFUNCTION(BlueprintCallable)
		void HandleAnimNotify_TriggerAttack_02();
	UFUNCTION(BlueprintCallable)
		void HandleAnimNotify_TriggerAttack_03();
	UFUNCTION(BlueprintCallable)
		void HandleAnimNotify_TriggerAttack_04();
	UFUNCTION(BlueprintCallable)
		void HandleAnimNotify_TriggerAttack_05();
	UFUNCTION(BlueprintCallable)
		void HandleAnimNotify_EndMontage();

	void CheckForCurrentState();

private:
	UPROPERTY()
		ACharacter_PlayerHuman* m_CharacterPlayerHuman_OwnerCharacter;
	bool b_HasInitializedAnimInstance = false;
};