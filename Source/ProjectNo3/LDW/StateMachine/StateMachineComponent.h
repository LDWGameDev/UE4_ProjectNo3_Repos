// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseState.h"
#include "StateMachineComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FDelegate_ChangeStateSignature)


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTNO3_API UStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()


/**
 * Properties
 */
public:
	FDelegate_ChangeStateSignature m_Delegate_ChangeState;
	UPROPERTY(EditDefaultsOnly, Category = "Custom State Machine")
		FString m_BackStateWhenError = FString(TEXT(""));
	bool m_bIsActive = false;

protected:

private:
	UPROPERTY()
		UBaseState* m_CurrentState;
	UPROPERTY()
		TArray<UBaseState*> m_StatesHistory;
	UPROPERTY()
		TArray<UBaseState*> m_AvailableStatesList;
	const int m_NumberHistoryStates = 10;
	const float m_MinStateTime = 0.1f;



/**
 * Functions
 */

public:	
	UStateMachineComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	TArray<UBaseState*>* GetAvailableStatesList();
	UBaseState* GetCurrentState();

	// Activate this component, init start state
	void ActivateStateMachine(const FString& p_StartStateID);
	
	// Deactivate this component
	void DeactivateStateMachine();

	// Change current state to new state
	void ChangeState(const FString& p_NewStateID);



protected:
	virtual void BeginPlay() override;

	// Get specific state in m_AvailableStatsList
	UBaseState* GetState_ByID(const FString& p_StateID);

private:
	// Add new state to the end of m_StatesHistory
	bool AddStateToHistory(UBaseState* p_LastState);
};
