// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Enemy/Character_EnemyBase.h"
#include "StateMachine/BaseState.h"
#include "StateMachine/StateMachineComponent.h"
#include "EnemyBaseState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UEnemyBaseState : public UBaseState
{
	GENERATED_BODY()
	

/**
 * Properties
 */
public:
protected:
private:



/**
 * Functions
 */
public:
	UEnemyBaseState();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;

	// Initialize state, set reference to m_StateMachineComponentREF
	// Called when create state in character
	virtual void InitState(UStateMachineComponent* p_StateMachineREF, AActor* p_CharacterEnemeyREF);

	// AnimMontage handling functions
	virtual void HandleAnimNotify_01();
	virtual void HandleAnimNotify_02();
	virtual void HandleAnimNotify_03();
	virtual void HandleEndMontage();

protected:
private:

};
