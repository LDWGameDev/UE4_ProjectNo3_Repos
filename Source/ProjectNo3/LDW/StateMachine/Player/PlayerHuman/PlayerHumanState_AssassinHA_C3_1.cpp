// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinHA_C3_1.h"
#include "Kismet/KismetMathLibrary.h"
#include "Item/Weapon/Actor_PlayerThrowingWeapon.h"

#include "Library/Library_CustomMath.h"
#include "StateMachine/Player/PlayerHuman/PlayerHumanState_AssassinHA_C2_1.h"


/**
 * 
 */

UPlayerHumanState_AssassinHA_C3_1::UPlayerHumanState_AssassinHA_C3_1()
{
	m_StateID = TEXT("PlayerHumanState_AssassinHA_C3_1");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.HeavyAttack.AssassinHeavyAttack_Combo3_Phase1", false);
	b_CanBreakOut = false;

	m_ThrowingWeaponsRotationList.Reserve(5);
	m_ThrowingWeaponsRotationList.Add(FRotator(0.0f, -20.0f, 0.0f));
	m_ThrowingWeaponsRotationList.Add(FRotator(0.0f, -10.0f, 0.0f));
	m_ThrowingWeaponsRotationList.Add(FRotator(0.0f, 0.0f, 0.0f));
	m_ThrowingWeaponsRotationList.Add(FRotator(0.0f, 10.0f, 0.0f));
	m_ThrowingWeaponsRotationList.Add(FRotator(0.0f, 20.0f, 0.0f));
}



/**
 * Override functions
 */

void UPlayerHumanState_AssassinHA_C3_1::EnterState()
{
	Super::EnterState();
	m_GotHitActor = nullptr;
	m_CharPlayerHuman_Owner->b_IsBuffingWeapon_01 = false;

	// Rotate to Controller rotation
	FRotator ControlRotation = m_CharPlayerHuman_Owner->GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;
	m_CharPlayerHuman_Owner->RotateToRotation(ControlRotation, 0.05f);

	m_CharPlayerHuman_Owner->PlayMontageFromTable(FName(TEXT("Assassin_HeavyAttack_C3_1")));
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(c_AdditionalArmLength, 0.5f);
}

void UPlayerHumanState_AssassinHA_C3_1::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (b_CanBreakOut)
	{
		b_CanBreakOut = false;
	}
}

void UPlayerHumanState_AssassinHA_C3_1::ExitState()
{
	Super::ExitState();
	m_CharPlayerHuman_Owner->m_AssassinHeavyAttack_C2_1->SetExitStateTimeToNow();
	b_CanBreakOut = false;
	m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 2.0f);
}




/**
 * Public member functions
 */

void UPlayerHumanState_AssassinHA_C3_1::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput == nullptr) return;
	m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
	m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();

	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C3_1::HandleAction_MoveForward);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C3_1::HandleAction_MoveRight);
}

void UPlayerHumanState_AssassinHA_C3_1::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);

	m_MoveForward_DelegateREF = nullptr;
	m_MoveRight_DelegateREF = nullptr;

}

void UPlayerHumanState_AssassinHA_C3_1::HandleAnimNotify_AnimNotify_01()
{
	b_CanBreakOut = true;

}

void UPlayerHumanState_AssassinHA_C3_1::HandleAnimNotify_EndMontage()
{
	Super::HandleAnimNotify_EndMontage();
	if (!b_IsInState) return;
	if (m_GotHitActor != nullptr)
	{
		FRotator GotHitLookAtPlayerRotation = UKismetMathLibrary::FindLookAtRotation(m_GotHitActor->GetActorLocation(), m_CharPlayerHuman_Owner->GetActorLocation());
		FVector NextLocation = m_GotHitActor->GetActorLocation() + UKismetMathLibrary::GetForwardVector(GotHitLookAtPlayerRotation) * 150.0f + UKismetMathLibrary::GetRightVector(GotHitLookAtPlayerRotation) * 50.0f;
		m_CharPlayerHuman_Owner->RotateToFaceTarget(m_GotHitActor, 0.1f);
		m_CharPlayerHuman_Owner->MoveToLocation(NextLocation, 0.1f);
		ChangeState(TEXT("PlayerHumanState_AssassinHA_C3_2"));
	}
	else if (FMath::Abs(m_MoveForwardValue) > 0.1f || FMath::Abs(m_MoveRightValue) > 0.1f)
	{
		m_CharPlayerHuman_Owner->StopAnimMontage();
		m_CharPlayerHuman_Owner->DisableRootMotionForTime(0.1f);
		ChangeState("PlayerHumanState_AssassinJog");
	}
	else ChangeState("PlayerHumanState_AssassinIdle");
}

void UPlayerHumanState_AssassinHA_C3_1::HandleAnimNotify_TriggerAttack_01()
{
	if (m_CharPlayerHuman_Owner->m_SubClass_PlayerThrowingWeapon == nullptr) return;
	FVector WeaponLocation = ULibrary_CustomMath::WorldLocationOfRelativeLocationToActor(m_CharPlayerHuman_Owner, FVector(80.0f, 0.0f, 30.0f));
	FActorSpawnParameters SpawnParams;
	for (auto& OffsetRotation : m_ThrowingWeaponsRotationList)
	{
		FRotator WeaponRotation = UKismetMathLibrary::ComposeRotators(m_CharPlayerHuman_Owner->GetActorRotation(), OffsetRotation);
		WeaponRotation.Pitch = -4.0f;
		AActor_PlayerThrowingWeapon* ThrowingWeapon = m_CharPlayerHuman_Owner->GetWorld()->SpawnActor<AActor_PlayerThrowingWeapon>(m_CharPlayerHuman_Owner->m_SubClass_PlayerThrowingWeapon, WeaponLocation, WeaponRotation, SpawnParams);
		ThrowingWeapon->SetReferenceValues(m_CharPlayerHuman_Owner, &m_AttackState_01);
	}
}





/**
 * Private member functions
 */

void UPlayerHumanState_AssassinHA_C3_1::HandleAction_MoveForward(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_Value;
}

void UPlayerHumanState_AssassinHA_C3_1::HandleAction_MoveRight(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_Value;
}