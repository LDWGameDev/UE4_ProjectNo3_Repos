// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHumanState_AssassinHA_C2_4.h"
#include "Kismet/KismetMathLibrary.h"


UPlayerHumanState_AssassinHA_C2_4::UPlayerHumanState_AssassinHA_C2_4()
{
	m_StateID = TEXT("PlayerHumanState_AssassinHA_C2_4");
	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.HeavyAttack.AssassinHeavyAttack_Combo2_Phase4", false);
	b_CanBreakOut = false;
	b_CameraSequenceValid = true;
	m_TargetActor = nullptr;

	m_Hitboxes_01.Add(FStruct_SphereTrace_Offset(FVector(140.0f, 0.0f, -20.0f), FVector(140.0f, 0.0f, -40.0f), 120.0f));

	m_Hitboxes_02.Reserve(6);
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(50.0f, -120.0f, -10.0f), FVector(50.0f, -120.0f, -30.0f), 80.0f));
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(140.0f, -90.0f, -10.0f), FVector(140.0f, -90.0f, -30.0f), 80.0f));
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(200.0f, -10.0f, -10.0f), FVector(200.0f, -10.0f, -30.0f), 80.0f));
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(180.0f, 90.0f, 0.0f), FVector(180.0f, 90.0f, -20.0f), 80.0f));
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(130.0f, 160.0f, 0.0f), FVector(130.0f, 160.0f, -20.0f), 80.0f));
	m_Hitboxes_02.Add(FStruct_SphereTrace_Offset(FVector(40.0f, 210.0f, 0.0f), FVector(40.0f, 210.0f, -20.0f), 80.0f));
}



/**
 * Override functions
 */

void UPlayerHumanState_AssassinHA_C2_4::EnterState()
{
	Super::EnterState();

	// if m_TargetActor not valid, exit state
	if (m_TargetActor == nullptr)
	{
		if (FMath::Abs(m_MoveForwardValue) > 0.1f || FMath::Abs(m_MoveRightValue) > 0.1f)
		{
			m_CharPlayerHuman_Owner->StopAnimMontage();
			m_CharPlayerHuman_Owner->DisableRootMotionForTime(0.1f);
			ChangeState("PlayerHumanState_AssassinJog");
		}
		else ChangeState("PlayerHumanState_AssassinIdle");
		return;
	}

	m_CharPlayerHuman_Owner->RotateToFaceTarget(m_TargetActor, 0.1f);
	FRotator LookAtRotation_TargetToPlayer = UKismetMathLibrary::FindLookAtRotation(m_TargetActor->GetActorLocation(), m_CharPlayerHuman_Owner->GetActorLocation());
	LookAtRotation_TargetToPlayer.Pitch = 0.0f;
	LookAtRotation_TargetToPlayer.Roll = 0.0f;
	FVector PlayerNextLocation = UKismetMathLibrary::GetForwardVector(LookAtRotation_TargetToPlayer) * 200.0f + m_TargetActor->GetActorLocation();
	m_CharPlayerHuman_Owner->MoveToLocation(PlayerNextLocation, 0.1f);

	FTimerHandle m_DelayBlendCamera;
	m_CharPlayerHuman_Owner->GetWorld()->GetTimerManager().SetTimer(m_DelayBlendCamera, [&]()
		{
			if (b_IsInState)
			{
				if (b_CameraSequenceValid)
				{
					m_CharPlayerHuman_Owner->PlayMontageFromTable(FName("Assassin_HeavyAttack_C2_4"));
					m_CharPlayerHuman_Owner->SetViewToCameraSequence(FName(TEXT("Sequence_HA_C2_4")), true);
				}
				else
				{
					m_CharPlayerHuman_Owner->PlayMontageFromTable(FName("Assassin_HeavyAttack_C2_4_Type2"));
					SetCameraFollow_01(c_AdditionArmLength, c_SocketOffset, 0.75f, -20.0f, 80.0f, FVector(0.0f, -50.0f, 0.0f), FVector(0.0f, -50.0f, 0.0f));
				}
			}
		}, 0.2f, false);
}

void UPlayerHumanState_AssassinHA_C2_4::TickState(float p_DeltaTime)
{
	Super::TickState(p_DeltaTime);
	if (b_CanBreakOut)
	{
		b_CanBreakOut = false;
		// Do something
	}
}

void UPlayerHumanState_AssassinHA_C2_4::ExitState()
{
	Super::ExitState();
	m_TargetActor = nullptr;
	b_CanBreakOut = false;
	if(!b_CameraSequenceValid) m_CharPlayerHuman_Owner->SetArmLength_CameraFollow_01(0.0f, 2.0f);
}




/**
 * Public member functions
 */

void UPlayerHumanState_AssassinHA_C2_4::BindInputHandlingFunctions(AController* p_PlayerController)
{
	Super::BindInputHandlingFunctions(p_PlayerController);
	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
	if (IPlayerInput == nullptr) return;
	m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
	m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();

	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C2_4::HandleAction_MoveForward);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C2_4::HandleAction_MoveRight);
}

void UPlayerHumanState_AssassinHA_C2_4::UnBindInputHandlingFunctions()
{
	Super::UnBindInputHandlingFunctions();
	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);

	m_MoveForward_DelegateREF = nullptr;
	m_MoveRight_DelegateREF = nullptr;
}

void UPlayerHumanState_AssassinHA_C2_4::HandleAnimNotify_AnimNotify_01()
{
	b_CanBreakOut = true;
}

void UPlayerHumanState_AssassinHA_C2_4::HandleAnimNotify_EndMontage()
{
	Super::HandleAnimNotify_EndMontage();
	if (FMath::Abs(m_MoveForwardValue) > 0.1f || FMath::Abs(m_MoveRightValue) > 0.1f)
	{
		m_CharPlayerHuman_Owner->StopAnimMontage();
		m_CharPlayerHuman_Owner->DisableRootMotionForTime(0.1f);
		ChangeState("PlayerHumanState_AssassinJog");
	}
	else ChangeState("PlayerHumanState_AssassinIdle");
}

void UPlayerHumanState_AssassinHA_C2_4::HandleAnimNotify_TriggerAttack_01()
{
	CheckForHittingTarget(m_Hitboxes_01, m_AttackState_01, false);
}

void UPlayerHumanState_AssassinHA_C2_4::HandleAnimNotify_TriggerAttack_02()
{
	CheckForHittingTarget(m_Hitboxes_01, m_AttackState_02, false);
}

void UPlayerHumanState_AssassinHA_C2_4::HandleAnimNotify_TriggerAttack_03()
{
	CheckForHittingTarget(m_Hitboxes_01, m_AttackState_03, false);
}

void UPlayerHumanState_AssassinHA_C2_4::HandleAnimNotify_TriggerAttack_04()
{
	CheckForHittingTarget(m_Hitboxes_01, m_AttackState_04, false);
}

void UPlayerHumanState_AssassinHA_C2_4::HandleAnimNotify_TriggerAttack_05()
{
	CheckForHittingTarget(m_Hitboxes_02, m_AttackState_05, false);
}






/**
 * Private member functions
 */

void UPlayerHumanState_AssassinHA_C2_4::HandleAction_MoveForward(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveForwardValue = p_Value;
}

void UPlayerHumanState_AssassinHA_C2_4::HandleAction_MoveRight(float p_Value)
{
	if (!b_IsInState) return;
	m_MoveRightValue = p_Value;
}