// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinUnequip.h"


UPlayerHumanState_AssassinUnequip::UPlayerHumanState_AssassinUnequip()
{
	m_StateID = TEXT("PlayerHumanState_AssassinUnequip");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.Unequip.AssassinUnequip", false);
}



/**
 * Override functions
 */

void UPlayerHumanState_AssassinUnequip::EnterState()
{
	Super::EnterState();
}

void UPlayerHumanState_AssassinUnequip::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
}

void UPlayerHumanState_AssassinUnequip::ExitState()
{
	Super::ExitState();
}


/**
 * Public member functions
 */

void UPlayerHumanState_AssassinUnequip::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
}

void UPlayerHumanState_AssassinUnequip::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
}