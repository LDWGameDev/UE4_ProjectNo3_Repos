// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"
#include "../StateMachine/StateMachineComponent.h"
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
		int32 m_AnimSetIndex;

	// Control Rig usage
	UPROPERTY(BlueprintReadOnly)
		bool b_DoFeetIK;
	UPROPERTY(BlueprintReadOnly)
		float m_ControlRigFootIKAlpha;

/**
 * Functions
 */
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Call Function")
		void SetUpJogStop();

	// Broad cast delegates in Character_PlayerHuman instance
	UFUNCTION(BlueprintCallable, Category = "Call Function")
		void BroadCastDelegate_EndMontage();
	UFUNCTION(BlueprintCallable, Category = "Call Function")
		void BroadCastDelegate_EndMontage_02();
	UFUNCTION(BlueprintCallable, Category = "Call Function")
		void BroadCastDelegate_AnimNotify_01();
	UFUNCTION(BlueprintCallable, Category = "Call Function")
		void BroadCastDelegate_AnimNotify_02();
	UFUNCTION(BlueprintCallable, Category = "Call Function")
		void BroadCastDelegate_AnimNotify_03();
	UFUNCTION(BlueprintCallable, Category = "Call Function")
		void BroadCastDelegate_EndAttack_01();
	UFUNCTION(BlueprintCallable, Category = "Call Function")
		void BroadCastDelegate_EndAttack_02();

	void CheckForCurrentState();

private:
	UPROPERTY()
		ACharacter_PlayerHuman* m_CharacterPlayerHuman_OwnerCharacter;
	bool b_HasInitializedAnimInstance = false;
};