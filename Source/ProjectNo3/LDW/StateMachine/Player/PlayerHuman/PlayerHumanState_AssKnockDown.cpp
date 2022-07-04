// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHumanState_AssKnockDown.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"


UPlayerHumanState_AssKnockDown::UPlayerHumanState_AssKnockDown()
{
	m_StateID = TEXT("PlayerHumanState_AssassinKnockDown");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.Damage.KnockDown.AssassinKnockDown", false);
}




/**
 * Override functions
 */

void UPlayerHumanState_AssKnockDown::EnterState()
{
	Super::EnterState();
	if (m_CharPlayerHuman_Owner->GetMesh() == nullptr) return;
	StartSimulatePhysics();
}

void UPlayerHumanState_AssKnockDown::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (b_HasSimulatePhysics)
	{
		FVector PelvisLocation = (m_CharPlayerHuman_Owner->GetMesh())->GetSocketLocation(FName(TEXT("Pelvis")));
		TArray<AActor*> ActorsToIgnore;
		FHitResult HitResult;
		bool TraceResult = UKismetSystemLibrary::LineTraceSingleForObjects(m_CharPlayerHuman_Owner, PelvisLocation, PelvisLocation + FVector(0.0f, 0.0f, -100.0f), 
			m_CharPlayerHuman_Owner->m_ObjectTypes_Ground, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResult, true);
		
		if (TraceResult)
		{
			FVector NextLocation = FMath::VInterpTo(m_CharPlayerHuman_Owner->GetActorLocation(), HitResult.Location + m_SavedActorOffsetLocation, p_DeltaTime, c_SnapLocationSpeed);
			m_CharPlayerHuman_Owner->SetActorLocation(NextLocation);
		}
		else
		{
			FVector NextLocation = FMath::VInterpTo(m_CharPlayerHuman_Owner->GetActorLocation(), PelvisLocation, p_DeltaTime, c_SnapLocationSpeed);
			m_CharPlayerHuman_Owner->SetActorLocation(NextLocation);
		}
	}

}

void UPlayerHumanState_AssKnockDown::ExitState()
{
	Super::ExitState();
	b_HasSimulatePhysics = false;
}




/**
 * Public member functions
 */

void UPlayerHumanState_AssKnockDown::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
}

void UPlayerHumanState_AssKnockDown::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
}



/**
 * Private member functions
 */

void UPlayerHumanState_AssKnockDown::StartSimulatePhysics()
{
	b_HasSimulatePhysics = true;
	(m_CharPlayerHuman_Owner->GetMesh())->SetAllBodiesBelowSimulatePhysics(FName(TEXT("Pelvis")), true, true);
	m_SavedActorOffsetLocation = FVector(0.0f, 0.0f, (m_CharPlayerHuman_Owner->GetCapsuleComponent())->GetScaledCapsuleHalfHeight());
	if (m_CharPlayerHuman_Owner->m_AnimInstance_PlayerHuman_REF != nullptr)
	{
		m_CharPlayerHuman_Owner->m_AnimInstance_PlayerHuman_REF->b_IsSimulatingPhysics_KnockDown = true;
	}
}