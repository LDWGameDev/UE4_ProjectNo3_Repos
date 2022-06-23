// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHuman_BaseState.h"
#include "GameplayTagContainer.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Library/Library_CustomMath.h"
#include "System/CombatSystem/Interface_Attackable.h"
#include "System/CombatSystem/System_CombatContainer.h"

#include "Library/Library_CustomMath.h"
#include "DrawDebugHelpers.h"


/**
 * 
 */

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

void UPlayerHuman_BaseState::CheckForHittingTarget(TArray<FStruct_SphereTrace_Offset>& p_Hitboxes, FStruct_AttackStateDefinition& p_AttackState, bool p_DebugHitboxes)
{
	m_HasGotHitActors.Empty();
	for (FStruct_SphereTrace_Offset& SphereTrace : p_Hitboxes)
	{
		FVector StartPosition = ULibrary_CustomMath::WorldLocationOfRelativeLocationToActor(m_CharPlayerHuman_Owner, SphereTrace.m_StartOffsetPosition);
		FVector EndPosition = ULibrary_CustomMath::WorldLocationOfRelativeLocationToActor(m_CharPlayerHuman_Owner, SphereTrace.m_EndOffsetPosition);
		TArray<AActor*> ActorToIgnore;
		ActorToIgnore.Add(m_CharPlayerHuman_Owner);
		TArray<FHitResult> HitResults;

		/*bool TraceResult = UKismetSystemLibrary::SphereTraceMultiForObjects(m_CharPlayerHuman_Owner, StartPosition, EndPosition, SphereTrace.m_Radius, m_CharPlayerHuman_Owner->m_ObjectTypes_AttackHitboxTrace,
			false, ActorToIgnore, EDrawDebugTrace::ForDuration, HitResults, true, FLinearColor::Red, FLinearColor::Green, 1.0f);*/
		
		// Debug, replace with above if not need to debug anymore
		bool TraceResult = false;
		if (p_DebugHitboxes)
		{
			UKismetSystemLibrary::SphereTraceMultiForObjects(m_CharPlayerHuman_Owner, StartPosition, EndPosition, SphereTrace.m_Radius, m_CharPlayerHuman_Owner->m_ObjectTypes_AttackHitboxTrace,
				false, ActorToIgnore, EDrawDebugTrace::ForDuration, HitResults, true, FLinearColor::Red, FLinearColor::Green, 1.0f);
		}
		else 
		{
			UKismetSystemLibrary::SphereTraceMultiForObjects(m_CharPlayerHuman_Owner, StartPosition, EndPosition, SphereTrace.m_Radius, m_CharPlayerHuman_Owner->m_ObjectTypes_AttackHitboxTrace,
				false, ActorToIgnore, EDrawDebugTrace::None, HitResults, true, FLinearColor::Red, FLinearColor::Green, 1.0f);
		}
		//

		if (TraceResult)
		{
			for (FHitResult& HitResult : HitResults)
			{
				IInterface_Attackable* IAttackable = Cast<IInterface_Attackable>(HitResult.GetActor());
				if (IAttackable != nullptr && !m_HasGotHitActors.Contains(HitResult.GetActor()))
				{
					// Get stats component
					// Create FStruct_AttackDefinition
					FStruct_AttackDefinition AttackDefinition(m_CharPlayerHuman_Owner, HitResult.GetActor(), &p_AttackState, &HitResult);
					IAttackable->TakeHit(AttackDefinition);
					m_HasGotHitActors.Add(HitResult.GetActor());
				}
			}
		}
	}
}

void UPlayerHuman_BaseState::RotateToClosetTarget(const FVector& p_CheckPositionOffset, float p_CheckRadius, float p_RotateTime)
{
	if (m_CharPlayerHuman_Owner == nullptr) return;
	AActor* ClosetActor = m_CharPlayerHuman_Owner->FindClosetTargetToAttack(p_CheckPositionOffset, p_CheckRadius);
	m_CharPlayerHuman_Owner->RotateToFaceTarget(ClosetActor, p_RotateTime);

	bool DoDebug = false;
	if (DoDebug)
	{
		FVector CheckPosition = ULibrary_CustomMath::WorldLocationOfRelativeLocationToActor(m_CharPlayerHuman_Owner, p_CheckPositionOffset);
		DrawDebugSphere(m_CharPlayerHuman_Owner->GetWorld(), CheckPosition, p_CheckRadius, 12, FColor::Green, true, 2.0f, 2, 0.4f);
	}
}