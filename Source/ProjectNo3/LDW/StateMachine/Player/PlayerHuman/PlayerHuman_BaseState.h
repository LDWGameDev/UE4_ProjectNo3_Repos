// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StateMachine/BaseState.h"
#include "System/CombatSystem/System_CombatContainer.h"
#include "Character/Player/Character_PlayerHuman.h"
#include "PlayerController/Interface_PlayerControllerInput.h"
#include "PlayerHuman_BaseState.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTNO3_API UPlayerHuman_BaseState : public UBaseState
{
	GENERATED_BODY()
	
/**
 * Properties
 */
public:

protected:
	UPROPERTY()
		ACharacter_PlayerHuman* m_CharPlayerHuman_Owner;

	TArray<AActor*> m_HasGotHitActors;

private:


/**
 * Functions
 */
public:
	UPlayerHuman_BaseState();
	virtual void EnterState() override;
	virtual void TickState(float p_DeltaTime) override;
	virtual void ExitState() override;
	
	// Called at BeginPlay() of Character_PlayerHuman after create the instance state of this class
	void InitState_PlayerHuman(ACharacter_PlayerHuman* p_CharOwner, UStateMachineComponent* p_StateMachineComponent);
	
	// Binds input and other delegate event of Character_PlayerHuman
	// Called when Character_PlayerHuman instance get possessed
	virtual void BindInputHandlingFunctions(AController* p_PlayerController);
	
	// Unbinds input and other delegate event of Character_PlayerHuman
	// Called when Character_PlayerHuman instance get dispossessed
	virtual void UnBindInputHandlingFunctions();


protected:
	// Set arm length and socket offset of CameraFollow_01
	void SetCameraFollow_01(const float& p_AdditionArmLength, const FVector& p_SocketOffset, float p_BlendTime, float p_ArmLength_AddFwd = -20.0f, float p_ArmLength_AddBwd = 80.0f,
											FVector p_SocketOffset_AddFwd = FVector(0.0f, -40.0f, 0.0f), FVector p_SocketOffset_AddBwd = FVector(0.0f, -40.0f, 0.0f));

	// Check if hitboxes hit target or not
	void CheckForHittingTarget(TArray<FStruct_SphereTrace_Offset>& p_Hitboxes, FStruct_AttackStateDefinition& p_AttackState, bool p_DebugHitboxes = false);

	void RotateToClosetTarget(const FVector& p_CheckPositionOffset = FVector(50.0f, 0.0f, 0.0f), float p_CheckRadius = 250.0f, float p_RotateTime = 0.1f);

private:
};




//__________________________________Header file template_______________________________________



///**
// * Properties
// */
//public:
//protected:
//private:
//
//
//	/**
//	 * Functions
//	 */
//public:
//	UPlayerHumanState_AssassinUnequip();
//	virtual void EnterState() override;
//	virtual void TickState(float p_DeltaTime) override;
//	virtual void ExitState() override;
//	virtual void BindInputHandlingFunctions(AController* p_PlayerController) override;
//	virtual void UnBindInputHandlingFunctions() override;
//protected:
//private:







//__________________________________Base state cpp file______________________________________________



//UPlayerHumanState_AssassinUnequip::UPlayerHumanState_AssassinUnequip()
//{
//	m_StateID = TEXT("PlayerHumanState_AssassinUnequip");
//	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.Equip.AssassinUnequip", false);
//}
//
//
//
///**
// * Override functions
// */
//
//void UPlayerHumanState_AssassinUnequip::EnterState()
//{
//	Super::EnterState();
//}
//
//void UPlayerHumanState_AssassinUnequip::TickState(float p_DeltaTime)
//{
//	Super::TickState(p_DeltaTime);
//}
//
//void UPlayerHumanState_AssassinUnequip::ExitState()
//{
//	Super::ExitState();
//}
//
//
///**
// * Public member functions
// */
//
//void UPlayerHumanState_AssassinUnequip::BindInputHandlingFunctions(AController* p_PlayerController)
//{
//	Super::BindInputHandlingFunctions(p_PlayerController);
//}
//
//void UPlayerHumanState_AssassinUnequip::UnBindInputHandlingFunctions()
//{
//	Super::UnBindInputHandlingFunctions();
//}










//___________________________Attack state header file______________________________



///**
// * Properties
// */
//
//public:
//
//protected:
//
//private:
//	FDelegate1_MovementSignature* m_MoveForward_DelegateREF;
//	FDelegate1_MovementSignature* m_MoveRight_DelegateREF;
//	FDelegate_ActionSignature* m_AnimNotify_01_DelegateREF;
//	FDelegate_ActionSignature* m_EndAttack_01_DelegateREF;
//
//	float m_MoveForwardValue;
//	float m_MoveRightValue;
//	bool b_CanBreakOut;
//
//
//
//	/**
//	 * Functions
//	 */
//
//public:
//	UPlayerHumanState_AssassinHA_C1_1();
//	virtual void EnterState() override;
//	virtual void TickState(float p_DeltaTime) override;
//	virtual void ExitState() override;
//	virtual void BindInputHandlingFunctions(AController* p_PlayerController) override;
//	virtual void UnBindInputHandlingFunctions() override;
//
//protected:
//
//private:
//	void HandleAction_MoveForward(float p_Value);
//	void HandleAction_MoveRight(float p_Value);
//	void HandleAction_AnimNotify_01();
//	void HandleAction_EndAttack_01();







//___________________________Attack state cpp file___________________________
// Change constructor, EndAttack notify


//UPlayerHumanState_AssassinHA_C1_1::UPlayerHumanState_AssassinHA_C1_1()
//{
//	m_StateID = TEXT("PlayerHumanState_AssassinHA_C1_1");
//	m_StateGameplayTag = FGameplayTag::RequestGameplayTag("StateMachine.PlayerState.Human.Action.HeavyAttack.AssassinHeavyAttack_Combo1_Phase1", false);
//	b_CanBreakOut = false;
//}
//
//
//
///**
// * Override functions
// */
//
//void UPlayerHumanState_AssassinHA_C1_1::EnterState()
//{
//	Super::EnterState();
//}
//
//void UPlayerHumanState_AssassinHA_C1_1::TickState(float p_DeltaTime)
//{
//	Super::TickState(p_DeltaTime);
//	if (b_CanBreakOut)
//	{
//		b_CanBreakOut = false;
//	}
//}
//
//void UPlayerHumanState_AssassinHA_C1_1::ExitState()
//{
//	Super::ExitState();
//	b_CanBreakOut = false;
//}
//
//
//
//
///**
// * Public member functions
// */
//
//void UPlayerHumanState_AssassinHA_C1_1::BindInputHandlingFunctions(AController* p_PlayerController)
//{
//	Super::BindInputHandlingFunctions(p_PlayerController);
//	IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(p_PlayerController);
//	if (IPlayerInput == nullptr) return;
//	m_MoveForward_DelegateREF = IPlayerInput->GetDelegate_MoveForward();
//	m_MoveRight_DelegateREF = IPlayerInput->GetDelegate_MoveRight();
//	m_AnimNotify_01_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_AnimNotify_01);
//	m_EndAttack_01_DelegateREF = &(m_CharPlayerHuman_Owner->m_Delegate_EndAttack_01);
//
//	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C1_1::HandleAction_MoveForward);
//	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C1_1::HandleAction_MoveRight);
//	if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C1_1::HandleAction_AnimNotify_01);
//	if (m_EndAttack_01_DelegateREF != nullptr) m_EndAttack_01_DelegateREF->AddUObject(this, &UPlayerHumanState_AssassinHA_C1_1::HandleAction_EndAttack_01);
//
//}
//
//void UPlayerHumanState_AssassinHA_C1_1::UnBindInputHandlingFunctions()
//{
//	Super::UnBindInputHandlingFunctions();
//	if (m_MoveForward_DelegateREF != nullptr) m_MoveForward_DelegateREF->RemoveAll(this);
//	if (m_MoveRight_DelegateREF != nullptr) m_MoveRight_DelegateREF->RemoveAll(this);
//	if (m_AnimNotify_01_DelegateREF != nullptr) m_AnimNotify_01_DelegateREF->RemoveAll(this);
//	if (m_EndAttack_01_DelegateREF != nullptr) m_EndAttack_01_DelegateREF->RemoveAll(this);
//
//	m_MoveForward_DelegateREF = nullptr;
//	m_MoveRight_DelegateREF = nullptr;
//	m_AnimNotify_01_DelegateREF = nullptr;
//	m_EndAttack_01_DelegateREF = nullptr;
//
//}
//
//
//
//
///**
// * Private member functions
// */
//
//void UPlayerHumanState_AssassinHA_C1_1::HandleAction_MoveForward(float p_Value)
//{
//	if (!b_IsInState) return;
//	m_MoveForwardValue = p_Value;
//}
//
//void UPlayerHumanState_AssassinHA_C1_1::HandleAction_MoveRight(float p_Value)
//{
//	if (!b_IsInState) return;
//	m_MoveRightValue = p_Value;
//}
//
//void UPlayerHumanState_AssassinHA_C1_1::HandleAction_AnimNotify_01()
//{
//	if (!b_IsInState) return;
//	b_CanBreakOut = true;
//}
//
//void UPlayerHumanState_AssassinHA_C1_1::HandleAction_EndAttack_01()
//{
//	if (!b_IsInState) return;
//	if (FMath::Abs(m_MoveForwardValue) > 0.1f || FMath::Abs(m_MoveRightValue) > 0.1f)
//	{
//	m_CharPlayerHuman_Owner->StopAnimMontage();
//	m_CharPlayerHuman_Owner->DisableRootMotionForTime(0.1f);
//	ChangeState("PlayerHumanState_AssassinJog");
//	}
//	else ChangeState("PlayerHumanState_AssassinIdle");
//}