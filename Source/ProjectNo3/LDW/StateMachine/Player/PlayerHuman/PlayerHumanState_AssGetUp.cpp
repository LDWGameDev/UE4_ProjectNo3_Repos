// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssGetUp.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Misc/App.h"

#include "Character/Struct_MontageToPlay.h"



UPlayerHumanState_AssGetUp::UPlayerHumanState_AssGetUp()
{
	m_StateID = TEXT("PlayerHumanState_AssassinGetUp");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.GetUp.AssassinGetUp", false);
}



/**
 * Override functions
 */

void UPlayerHumanState_AssGetUp::EnterState()
{
	Super::EnterState();
	if (!m_CharPlayerHuman_Owner->GetMesh()) return;

	// Check for SkeletalMesh is facing up or down
	FRotator PelvisRotator = (m_CharPlayerHuman_Owner->GetMesh())->GetSocketRotation(FName(TEXT("Pelvis")));
	float DotProductResult = UKismetMathLibrary::Dot_VectorVector(UKismetMathLibrary::GetRightVector(PelvisRotator), FVector::UpVector);
	b_SavedIsFacingUp = (DotProductResult >= 0.0f) ? true : false;

	// Rotate Character to match the getting up direction via get up anim montage 
	FVector PelvisLocation = (m_CharPlayerHuman_Owner->GetMesh())->GetSocketLocation(FName(TEXT("Pelvis")));
	FVector NeckLocation = (m_CharPlayerHuman_Owner->GetMesh())->GetSocketLocation(FName(TEXT("neck_01")));

	FVector ForwardDirection = (b_SavedIsFacingUp) ? (PelvisLocation - NeckLocation) : (NeckLocation - PelvisLocation);
	FRotator CharacterRotator = UKismetMathLibrary::MakeRotFromZX(FVector::UpVector, ForwardDirection);
	CharacterRotator.Roll = 0.0f;
	CharacterRotator.Pitch = 0.0f;
	m_CharPlayerHuman_Owner->SetActorRotation(CharacterRotator);

	// Delay save pose snapshot
	FTimerHandle TimerHandleDelaySnapshot;
	m_CharPlayerHuman_Owner->GetWorld()->GetTimerManager().SetTimer(TimerHandleDelaySnapshot, [&]()
		{
			(m_CharPlayerHuman_Owner->m_AnimInstance_PlayerHuman_REF)->SavePoseSnapshot(FName(TEXT("PoseSnapshot_GetUp")));
			if (b_SavedIsFacingUp) m_CharPlayerHuman_Owner->PlayMontageFromTable_DamageMontages(FName(TEXT("Damage_GetUp_F_01")));
			else m_CharPlayerHuman_Owner->PlayMontageFromTable_DamageMontages(FName(TEXT("Damage_GetUp_B_01")));
		}, 0.1f, false);

	// Delay stop simulating physics
	FTimerHandle TimerHandleDelayStopSimulate;
	m_CharPlayerHuman_Owner->GetWorld()->GetTimerManager().SetTimer(TimerHandleDelayStopSimulate, [&]()
		{
			(m_CharPlayerHuman_Owner->GetMesh())->SetAllBodiesBelowSimulatePhysics(FName(TEXT("Pelvis")), false, true);
			m_CharPlayerHuman_Owner->m_AnimInstance_PlayerHuman_REF->b_IsSimulatingPhysics_KnockDown = false;
		}, 0.2f, false);
}

void UPlayerHumanState_AssGetUp::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
}

void UPlayerHumanState_AssGetUp::ExitState()
{
	Super::ExitState();
}




/**
 * Public member functions
 */

void UPlayerHumanState_AssGetUp::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
}

void UPlayerHumanState_AssGetUp::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
}