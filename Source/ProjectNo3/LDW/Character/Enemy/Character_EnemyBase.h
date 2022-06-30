// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"

#include "System/CombatSystem/Interface_Attackable.h"
#include "System/InteractingSystem/Interface_GameplayTagControl.h"
#include "StateMachine/StateMachineComponent.h"
#include "Character_EnemyBase.generated.h"


DECLARE_MULTICAST_DELEGATE(FDelegate_EnemyBaseActionSignature)

class UCurveFloat;
class UEnemyBaseState;

/**
 * 
 */
UCLASS(Abstract)
class PROJECTNO3_API ACharacter_EnemyBase : public ACharacter, public IInterface_Attackable, public IInterface_GameplayTagControl
{
	GENERATED_BODY()


/**
 * Properties
 */

public:
	// TagContainer actor all tags
	UPROPERTY(EditDefaultsOnly, Category = "Custom EnemyBase")
		FGameplayTagContainer m_TagContainer;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom EnemyBase")
		UCurveFloat* m_CurveFloat_AlphaEaseInOut;

	UPROPERTY(EditDefaultsOnly, Category = "Custom EnemyBase")
		TArray<TEnumAsByte<EObjectTypeQuery>> m_ObjectTypes_Ground;

	bool b_IsActive;
	bool b_IsInAir;
	float m_CurrentMovingSpeed;

	FDelegate_EnemyBaseActionSignature m_Delegate_LandStart;


protected:
	// State machine
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom EnemyBase", meta = (AllowPrivateAccess = "true"))
		UStateMachineComponent* m_StateMachine_01;

	float m_DefaultCapsuleHalfHeight = 96.0f;
	float m_DefaultCapsuleRadius = 42.0f;


private:
	// Timeline control Location
	FTimeline m_Timeline_LocationControl;
	FVector m_SavedCurrentLocation;
	FVector m_SavedNewLocation;

	// Timeline control Rotation
	FTimeline m_Timeline_RotationControl;
	FRotator m_SavedCurrentRotator;
	FRotator m_SavedNextRotator;

	// Timeline control CapsuleComponent
	FTimeline m_Timeline_CapsuleSizeControl;
	float m_SavedCapsuleHalfHeight;
	float m_SavedCapsuleRadius;
	float m_SavedNewCapsuleHalfHeight;
	float m_SavedNewCapsuleRadius;





/**
 * Functions
 */

public:
	ACharacter_EnemyBase();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Landed(const FHitResult& Hit) override;

	// Get current state of m_StateMachine_01
	UEnemyBaseState* GetCurrentState_EnemyBaseState();

	// Inherited from IInterface_GameplayTagControl
	const FGameplayTagContainer& GetTagContainer() override;

	// Inherited from IInterface_Attackable
	virtual void TakeHit(FStruct_AttackDefinition& p_AttackDefinition);

	// Activate or deactivate this enemy
	virtual void ActivateEnemy(bool p_DoActivate);

	// Move this actor to a location using m_Timeline_LocationControl
	void MoveToLocation(const FVector& p_NewLocation, float p_BlendTime);

	// Rotate to rotator using m_Timeline_LocationControl
	void RotateToRotation(const FRotator& p_NewRotation, float p_BlendTime);

	// Rotate to face target actor. Only rotate Yaw, Pitch and Roll remain 0
	void RotateToFaceActor(AActor* p_TargetActor, float p_BlendTime);

	// Update CapsuleSize overtime using m_Timeline_CapsuleSizeControl 
	void SetCapsuleSize(float p_NewCapsuleHalfHeight, float p_NewCapsuleRadius, float p_BlendTime);
	void ResetCapsuleSize(float p_BlendTime);

protected:
	virtual void BeginPlay() override;

private:
	// Init timeline component in BeginPlay()
	void InitTimelines();
	// Tick timeline component in Tick()
	void TickTimelines(float p_DeltaTime);

	// Check and set values for b_IsInAir, m_CurrentMovingSpeed
	void CalculateMovement();

};