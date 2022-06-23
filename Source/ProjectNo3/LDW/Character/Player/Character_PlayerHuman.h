// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ControlRigComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "Engine/DataTable.h"
#include "ActorSequenceComponent.h"

#include "Actor/Actor_CameraSystem.h"
#include "Character/Struct_MontageToPlay.h"
#include "Character/Player/AnimInstance_PlayerHuman.h"
#include "Item/Weapon/Struct_Weapon.h"
#include "PlayerController/Interface_PlayerControllerInput.h"
#include "StateMachine/StateMachineComponent.h"

#include "Character_PlayerHuman.generated.h"


DECLARE_MULTICAST_DELEGATE(FDelegate_LandedSignature)
DECLARE_MULTICAST_DELEGATE(FDelegate_StartFallingSignature)


class UPlayerHumanState_UnarmedIdle;
class UPlayerHumanState_UnarmedJog;
class UPlayerHumanState_UnarmedJump;
class UPlayerHumanState_UnarmedFalling;
class UPlayerHumanState_UnarmedDash;
class UPlayerHumanState_UnarmedRun;
class UPlayerHumanState_AssassinEquip;
class UPlayerHumanState_AssassinUnequip;
class UPlayerHumanState_AssassinIdle;
class UPlayerHumanState_AssassinJog;
class UPlayerHumanState_AssassinRun;
class UPlayerHumanState_AssassinDash;
class UPlayerHumanState_AssassinDash_2;
class UPlayerHumanState_AssassinFalling;
class UPlayerHumanState_AssassinJump;
class UPlayerHumanState_AssassinLA_C1_1;
class UPlayerHumanState_AssassinLA_C1_2;
class UPlayerHumanState_AssassinLA_C1_3;
class UPlayerHumanState_AssassinHA_C1_1;
class UPlayerHumanState_AssassinHA_C1_2;
class UPlayerHumanState_AssassinHA_C2_1;
class UPlayerHumanState_AssassinHA_C2_2;
class UPlayerHumanState_AssassinHA_C2_3;
class UPlayerHumanState_AssassinHA_C2_4;
class UPlayerHumanState_AssassinHA_C3_1;
class UPlayerHumanState_AssassinHA_C3_2;

class AActor_HoldingWeapon;


/**
 * 
 */
UCLASS(Abstract)
class PROJECTNO3_API ACharacter_PlayerHuman : public ACharacter
{
	GENERATED_BODY()

/**
 * Properties
 */
public:
	// Camera system blueprint
	UPROPERTY(EditDefaultsOnly, Category = "Custom Camera System")
		TSubclassOf<AActor_CameraSystem> m_Subclass_CameraSystemActor;


	// ObjectType to check if hitboxes hit or not
	UPROPERTY(EditDefaultsOnly, Category = "Custom Combat System")
		TArray<TEnumAsByte<EObjectTypeQuery>> m_ObjectTypes_AttackHitboxTrace;

	// ObjectType to check if actor can be targeted to attack or not
	UPROPERTY(EditDefaultsOnly, Category = "Custom Combat System")
		TArray<TEnumAsByte<EObjectTypeQuery>> m_ObjectTypes_ClosetTargetToAttack;

	// TagContainer contains gameplay tags to check if actor can be targeted to attack or not
	UPROPERTY(EditDefaultsOnly, Category = "Custom Combat System")
		FGameplayTagContainer m_TagContainer_ClosetTargetToAttack;
		

	// Ease in and out alpha (0 - 1) curve
	UPROPERTY(EditDefaultsOnly, Category = "Custom Timeline")
		UCurveFloat* m_CurveFloat_EaseInOutAlpha;
	// Linear alpha (0 - 1) curve
	UPROPERTY(EditDefaultsOnly, Category = "Custom Timeline")
		UCurveFloat* m_CurveFloat_LinearAlpha;
	// Hard in ease out alpha (0 - 1) curve
	UPROPERTY(EditDefaultsOnly, Category = "Custom Timeline")
		UCurveFloat* m_CurveFloat_HardInEaseOutAlpha;
	// DataTable contains all weapons
	UPROPERTY(EditDefaultsOnly, Category = "Custom Timeline")
		UDataTable* m_DataTable_Weapons;
	// DataTable contains all montages
	UPROPERTY(EditDefaultsOnly, Category = "Custom Timeline")
		UDataTable* m_DataTable_Montages;
	


	UPROPERTY()
		UAnimInstance_PlayerHuman* m_AnimInstance_PlayerHuman_REF;

	// States of this character
	UPROPERTY()
		UPlayerHumanState_UnarmedIdle* m_UnarmedIdleState;
	UPROPERTY()
		UPlayerHumanState_UnarmedJog* m_UnarmedJogState;
	UPROPERTY()
		UPlayerHumanState_UnarmedJump* m_UnarmedJumpState;
	UPROPERTY()
		UPlayerHumanState_UnarmedFalling* m_UnarmedFallingState;
	UPROPERTY()
		UPlayerHumanState_UnarmedDash* m_UnarmedDashState;
	UPROPERTY()
		UPlayerHumanState_UnarmedRun* m_UnarmedRunState;
	UPROPERTY()
		UPlayerHumanState_AssassinEquip* m_AssassinEquipState;
	UPROPERTY()
		UPlayerHumanState_AssassinUnequip* m_AssassinUnequipState;
	UPROPERTY()
		UPlayerHumanState_AssassinIdle* m_AssassinIdleState;
	UPROPERTY()
		UPlayerHumanState_AssassinJog* m_AssassinJogState;
	UPROPERTY()
		UPlayerHumanState_AssassinRun* m_AssassinRunState;
	UPROPERTY()
		UPlayerHumanState_AssassinDash* m_AssassinDashState;
	UPROPERTY()
		UPlayerHumanState_AssassinFalling* m_AssassinFallingState;
	UPROPERTY()
		UPlayerHumanState_AssassinJump* m_AssassinJumpState;
	UPROPERTY()
		UPlayerHumanState_AssassinDash_2* m_AssassinDash_2_State;
	UPROPERTY()
		UPlayerHumanState_AssassinLA_C1_1* m_AssassinLightAttack_C1_1;
	UPROPERTY()
		UPlayerHumanState_AssassinLA_C1_2* m_AssassinLightAttack_C1_2;
	UPROPERTY()
		UPlayerHumanState_AssassinLA_C1_3* m_AssassinLightAttack_C1_3;
	UPROPERTY()
		UPlayerHumanState_AssassinHA_C1_1* m_AssassinHeavyAttack_C1_1;
	UPROPERTY()
		UPlayerHumanState_AssassinHA_C1_2* m_AssassinHeavyAttack_C1_2;
	UPROPERTY()
		UPlayerHumanState_AssassinHA_C2_1* m_AssassinHeavyAttack_C2_1;
	UPROPERTY()
		UPlayerHumanState_AssassinHA_C2_2* m_AssassinHeavyAttack_C2_2;
	UPROPERTY()
		UPlayerHumanState_AssassinHA_C2_3* m_AssassinHeavyAttack_C2_3;
	UPROPERTY()
		UPlayerHumanState_AssassinHA_C2_4* m_AssassinHeavyAttack_C2_4;
	UPROPERTY()
		UPlayerHumanState_AssassinHA_C3_1* m_AssassinHeavyAttack_C3_1;
	UPROPERTY()
		UPlayerHumanState_AssassinHA_C3_2* m_AssassinHeavyAttack_C3_2;

	FDelegate_LandedSignature m_Delegate_Landed;
	FDelegate_StartFallingSignature m_Delegate_StartFalling;
	FDelegate_ActionSignature m_Delegate_EndMontage;
	FDelegate_ActionSignature m_Delegate_EndMontage_02;
	FDelegate_ActionSignature m_Delegate_AnimNotify_01;
	FDelegate_ActionSignature m_Delegate_AnimNotify_02;
	FDelegate_ActionSignature m_Delegate_AnimNotify_03;
	FDelegate_ActionSignature m_Delegate_EndAttack_01;
	FDelegate_ActionSignature m_Delegate_EndAttack_02;
	FDelegate_ActionSignature m_Delegate_TriggerAttack_01;
	FDelegate_ActionSignature m_Delegate_TriggerAttack_02;
	FDelegate_ActionSignature m_Delegate_TriggerAttack_03;


	bool b_IsBuffingWeapon_01 = false;


protected:
	float m_MovingSpeed;


private:
	UPROPERTY()
		AActor_CameraSystem* m_CameraSystemActor;

	const float c_DefaultArmLength_Follow_01 = 350.0f;
	const float c_BuffWeapon_01_BuffTime = 3.0f;
	const FRotator c_SpringArm_DefaultTargetRotation = FRotator(330.0f, 30.0f, 0.0f);

	// Delegate REF to m_Delegate_BuffWeapon_01 of PlayerControllerMainController
	FDelegate_ActionSignature* m_BuffWeapon_01_DelegateREF;
	// Delegate REF to m_Delegate_ReturnViewTarget of m_CameraSystem (Actor_CameraSystem)
	FDelegate_ReturnViewTargetSignature* m_ReturnViewTarget_DelegateREF;

	FStruct_Weapon* m_CurrentWeaponStruct;
	AActor_HoldingWeapon* m_CurrentHoldingWeapon;

	// Timeline controls alpha of FootIK ControlRig node in anim BP
	FTimeline m_Timeline_ControlRigFootIK;
	float m_SavedControlRigFootIKAlpha;
	float m_NewValueControlRigFootIKAlpha;

	// Timeline controls rotation of this character
	FTimeline m_Timeline_Rotation;
	FRotator m_SavedRotator;
	FRotator m_NewRotator;

	// Timeline controls target arm length of m_SpringArm_Follow_01
	FTimeline m_Timeline_CameraFollow_01;
	float m_SavedArmLength_Follow_01;
	float m_NewArmLength_Follow_01;
	FVector m_SavedSocketOffset_Follow_01;
	FVector m_NewSocketOffset_Follow_01;

	// Timeline controls weapon buff effect 01
	FTimeline m_Timeline_WeaponBuff_01;
	float m_SavedTimeValue_WeaponBuff_01;

	



/**
 * Functions
 */

public:
	ACharacter_PlayerHuman();
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void Falling() override;
	

	// Get m_MovingSpeed
	float GetMovingSpeed();
	// Get m_StateMachine
	UStateMachineComponent* GetStateMachine();


	// Movement this character using movement input
	void MoveCharacter(float p_MoveForwardValue, float p_MoveRightValue);
	
	// Set m_ControlRigFootIKAlpha in anim instance, blend from current to p_ValueToSet in p_BlendTime
	void SetControlRigFootIKAlpha(float p_NewValue, float p_BlendTime);
	
	// Rotate this character to a rotation over p_BlendTime time
	void RotateToRotation(const FRotator& p_NewRotation, float p_BlendTime);
	
	// Rotate this character to face another actor over p_BlendTime time. Only rotate the yaw value, roll and pitch remain 0.
	void RotateToFaceTarget(const AActor* p_ActorToFace, float p_BlendTime);
	
	// Play montage from DataTable m_AnimMontagesMap
	bool PlayMontageFromTable(const FName& p_MontageID);
	
	// Disable root motion of this character for an amount of time
	void DisableRootMotionForTime(float p_DisableTime);
	
	// Change arm_length and socket_offset of m_SpringArm_Follow_01
	void SetArmLength_CameraFollow_01(float p_AdditionalLengthToDefault, float p_BlendTime);

	void SetCameraFollow_01(float p_AdditionalLengthToDefault, const FVector& p_SocketOffset, float p_BlendTime);
	
	// Equip weapon
	UFUNCTION(BlueprintCallable)
	bool EquipWeapon(const FName& p_NewWeaponID);
	
	// Set view target to m_Camera_Follow_01
	void SetViewToCameraFollow_01(float p_BlendTime, EViewTargetBlendFunction p_BlendFunction = EViewTargetBlendFunction::VTBlend_EaseInOut, float p_BlendHardness = 1.0f, bool p_LockViewToTarget = true);
	
	// Set view to camera sequence of m_CameraSystemActor
	void SetViewToCameraSequence(const FName& p_SequenceID, bool p_ResetCameraSystemTransform = true);

	// Find closet actor that is implemented Interface_GameplayTagControl and has one of the tags in p_TargetHasTag
	AActor* FindClosetActor_SphereCheck(const FVector& p_OffsetPositionToCheck, float p_RadiusToCheck, const TArray<TEnumAsByte<EObjectTypeQuery>>& p_ObjectTypesToCheck, const FGameplayTagContainer& p_TagsToCheck);

	// Find closet actor to attack
	AActor* FindClosetTargetToAttack(const FVector& p_OffsetPositionToCheck, float p_RadiusToCheck);


protected:
	virtual void BeginPlay() override;


private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom PlayerHuman", meta = (AllowPrivateAccess = "true"))
		UStateMachineComponent* m_StateMachine_01;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom PlayerHuman", meta = (AllowPrivateAccess = "true"))
		UControlRigComponent* m_ControlRig_01;

	// Camera components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom PlayerHuman", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* m_SpringArm_Follow_01;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom PlayerHuman", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* m_Camera_Follow_01;


	// Handle possession and dispossession this character
	void HandleOnPossessed(AController* p_Controller);
	void HandleOnUnPossessed();
	void DelayHandleOnPossessed();
	
	// Create PlayerHuman_BaseState derived states
	void InitStateMachine();

	// Calculate m_MovingSpeed, 
	void CalculateMovement();

	// Init timelines of this character. Called in BeginPlay()
	void InitTimelines();
	void TimelineTicks(float p_DeltaTime);

	// Timer function. Enable root motion
	void EnableRootMotion();

	// Instantiate new holding weapon object base on m_CurrentWeaponStruct and assign to m_CurrentHoldingWeapon
	void CreateHoldingWeapon();

	// Bind to FDelegate_ChangeStateSignature delegate of StateMachineComponent
	void HandleDelegate_ChangeState();

	// Bind to FDelegate_BuffWeapon_01 of PlayerController
	void HandleDelegate_BuffWeapon_01();

	// Bind to FDelegate_ReturnViewTargetSignature of m_CameraSystemActor (Actor_CameraSystem type)
	void HandleDelegate_ReturnViewTarget();


public:
	UFUNCTION(BlueprintCallable)
		void TestFunction(FVector p_StartOffset, FVector p_EndOffset, float p_Radius);
};