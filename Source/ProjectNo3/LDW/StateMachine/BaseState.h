// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Misc/DateTime.h"
#include "GameplayTagContainer.h"
#include "BaseState.generated.h"

/**
 * Base state for all states to derived from
 */
UCLASS()
class PROJECTNO3_API UBaseState : public UObject
{
	GENERATED_BODY()

/**
 * Properties
 */
public:

protected:
	UPROPERTY()
		class UStateMachineComponent* m_StateMachineComponentREF;
	FString m_StateID = FString(TEXT(""));
	FDateTime m_EnterStateTime;
	FDateTime m_ExitStateTime;
	FGameplayTag m_StateGameplayTag;
	bool b_IsInState = false;
	float m_CooldownTime = 0.0f;
	

private:


/**
 * Functions
 */
public:
	UBaseState();
	virtual void EnterState();
	virtual void TickState(float p_DeltaTime);
	virtual void ExitState();

	const FString& GetStateID();
	const FDateTime& GetStateTime_Enter();
	const FDateTime& GetStateTime_Exit();
	FGameplayTag* GetStateTag();
	// Get duration of last happen of this state
	float GetStateTime_LastDuration();
	// Get time from m_EnterStateTime to UTCNow
	float GetStateTime_StartToNow();
	
	void SetExitStateTimeToNow();
	bool CheckForCooldownTime();
	// Return true if current UTCNow - last ExitStateTime < p_ValueToCheck
	bool CheckForHoldingAfterExit(float p_TimeToCheck = 0.0f);

protected:
	void ChangeState(FString p_NextStateID);

private:
};
