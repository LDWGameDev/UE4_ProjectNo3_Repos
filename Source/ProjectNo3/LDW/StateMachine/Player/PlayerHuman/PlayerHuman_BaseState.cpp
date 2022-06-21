// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHuman_BaseState.h"
#include "GameplayTagContainer.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../../Library/Library_CustomMath.h"

UPlayerHuman_BaseState::UPlayerHuman_BaseState() 
{

}

void UPlayerHuman_BaseState::InitState_PlayerHuman(ACharacter_PlayerHuman* p_CharOwner, UStateMachineComponent* p_StateMachineComponent)
{
	m_CharPlayerHuman_Owner = p_CharOwner;
	m_StateMachineComponentREF = p_StateMachineComponent;
}

void UPlayerHuman_BaseState::EnterState()
{
	Super::EnterState();
	if (m_CharPlayerHuman_Owner == nullptr) return;

}

void UPlayerHuman_BaseState::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (!b_IsInState || m_CharPlayerHuman_Owner == nullptr) return;

}

void UPlayerHuman_BaseState::ExitState()
{
	Super::ExitState();
	if (m_CharPlayerHuman_Owner == nullptr) return;

}

void UPlayerHuman_BaseState::BindInputHandlingFunctions(AController* p_PlayerController)
{
	if (m_CharPlayerHuman_Owner == nullptr || p_PlayerController == nullptr) return;
}

void UPlayerHuman_BaseState::UnBindInputHandlingFunctions()
{

}




/**
 * Protected member functions
 */

void UPlayerHuman_BaseState::SetCameraFollow_01(const float& p_AdditionArmLength, const FVector& p_SocketOffset, float p_BlendTime, float p_ArmLength_AddFwd /* = -20.0f */, 
	float p_ArmLength_AddBwd /* = 80.0f */, FVector p_SocketOffset_AddFwd /* = FVector(0.0f, -40.0f, 0.0f) */, FVector p_SocketOffset_AddBwd /* = FVector(0.0f, -40.0f, 0.0f) */)
{
	float ArmLength = p_AdditionArmLength;
	FVector SocketOffset = p_SocketOffset;

	FRotator CharacterRotator = m_CharPlayerHuman_Owner->GetActorRotation();
	FRotator ControllerRotator = m_CharPlayerHuman_Owner->GetControlRotation();
	ControllerRotator.Pitch = 0.0f;
	ControllerRotator.Roll = 0.0f;
	float DirectionAngle = ULibrary_CustomMath::TwoVectorsAngle_Degrees180(UKismetMathLibrary::GetForwardVector(CharacterRotator), UKismetMathLibrary::GetForwardVector(ControllerRotator));

	if (DirectionAngle > -30.0f && DirectionAngle < 30.0f)
	{
		ArmLength += p_ArmLength_AddFwd;
		SocketOffset += p_SocketOffset_AddFwd;
	}
	else if (DirectionAngle < -150.0f || DirectionAngle > 150.0f)
	{
		ArmLength += p_ArmLength_AddBwd;
		SocketOffset += p_SocketOffset_AddBwd;
	}
	if (DirectionAngle > 0.0f) SocketOffset.Y *= -1.0f;
	m_CharPlayerHuman_Owner->SetCameraFollow_01(ArmLength, SocketOffset, p_BlendTime);
}
