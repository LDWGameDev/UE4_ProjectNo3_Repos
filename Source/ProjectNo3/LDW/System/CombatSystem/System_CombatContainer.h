// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "System_CombatContainer.generated.h"



/**
 * Hit type
 */
UENUM(BlueprintType)
enum class EHitType : uint8 
{
	LightAttack			UMETA(DisplayName = "LightAttack"),
	Push				UMETA(DisplayName = "Push"),
	Pull				UMETA(DisplayName = "Pull"),
	Knock				UMETA(DisplayName = "Knock"),
	Stun				UMETA(DisplayName = "Stun"),
	PushAndStun			UMETA(DisplayName = "PushAndStun"0)
};




/**
 * 6 ways attack direction
 */
UENUM(BlueprintType)
enum class EDirectionAttack6Ways : uint8
{
	Front			UMETA(DisplayName = "Front", ToolTip = "Front direction of attacker"),
	Back			UMETA(DisplayName = "Back", ToolTip = "Back direction of attacker"),
	Left			UMETA(DisplayName = "Left", ToolTip = "Left direction of attacker"),
	Right			UMETA(DisplayName = "Right", ToolTip = "Right direction of attacker"),
	Up				UMETA(DisplayName = "Up", ToolTip = "Up direction of attacker"),
	Down			UMETA(DisplayName = "Down", ToolTip = "Down direction of attacker")
};




/**
 * Hitbox sphere trace definition
 */
USTRUCT(BlueprintType)
struct FStruct_SphereTrace_Offset : public FTableRowBase
{
	GENERATED_BODY()

	FORCEINLINE FStruct_SphereTrace_Offset();
	FORCEINLINE FStruct_SphereTrace_Offset(const FVector& p_StartOffset, const FVector& p_EndOffset, float p_Radius);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector m_StartOffsetPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector m_EndOffsetPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_Radius;
};

FORCEINLINE FStruct_SphereTrace_Offset::FStruct_SphereTrace_Offset() : m_StartOffsetPosition(FVector()), m_EndOffsetPosition(FVector()), m_Radius(0.0f) {}
FORCEINLINE FStruct_SphereTrace_Offset::FStruct_SphereTrace_Offset(const FVector& p_StartOffset, const FVector& p_EndOffset, float p_Radius) : m_StartOffsetPosition(p_StartOffset), m_EndOffsetPosition(p_EndOffset), m_Radius(p_Radius) {}



USTRUCT(BlueprintType)
struct FStruct_SphereOverlap_Offset : public FTableRowBase
{
	GENERATED_BODY()

	FORCEINLINE FStruct_SphereOverlap_Offset();
	FORCEINLINE FStruct_SphereOverlap_Offset(const FVector& p_OffsetPosition, float p_Radius);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector m_OffsetPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_Radius;
};

FORCEINLINE FStruct_SphereOverlap_Offset::FStruct_SphereOverlap_Offset() : m_OffsetPosition(FVector()), m_Radius(0.0f) {}

FORCEINLINE FStruct_SphereOverlap_Offset::FStruct_SphereOverlap_Offset(const FVector& p_OffsetPosition, float p_Radius) : m_OffsetPosition(p_OffsetPosition), m_Radius(p_Radius) {}





/**
 * 
 */
USTRUCT(BlueprintType)
struct FStruct_AttackStateDefinition : public FTableRowBase
{
	GENERATED_BODY()

	FORCEINLINE FStruct_AttackStateDefinition();
	FORCEINLINE FStruct_AttackStateDefinition(EHitType p_HitType, EDirectionAttack6Ways p_AttackDirection, bool p_DoControlPosition, const FVector& p_ControlPositionOffset, float p_ControlPositionTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EHitType m_HitType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EDirectionAttack6Ways m_AttackDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool b_DoControlPostion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector m_ControlPositionOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_ControlPositionTime;
};

FORCEINLINE FStruct_AttackStateDefinition::FStruct_AttackStateDefinition() : m_HitType(EHitType::LightAttack), m_AttackDirection(EDirectionAttack6Ways::Front), b_DoControlPostion(false), m_ControlPositionOffset(FVector()), m_ControlPositionTime(0.0f) {}

FORCEINLINE FStruct_AttackStateDefinition::FStruct_AttackStateDefinition(EHitType p_HitType, EDirectionAttack6Ways p_AttackDirection, bool p_DoControlPosition, const FVector& p_ControlPositionOffset, float p_ControlPositionTime) :
	m_HitType(p_HitType), m_AttackDirection(p_AttackDirection), b_DoControlPostion(p_DoControlPosition), m_ControlPositionOffset(p_ControlPositionOffset), m_ControlPositionTime(p_ControlPositionTime) {}





USTRUCT()
struct FStruct_AttackDefinition
{
	GENERATED_BODY()

	FORCEINLINE FStruct_AttackDefinition();
	FORCEINLINE FStruct_AttackDefinition(AActor* p_Attacker, AActor* p_GetHitActor, FStruct_AttackStateDefinition* p_AttackerAttackState, FHitResult* p_HitResult);

	AActor* m_AttackerActor;
	AActor* m_GetHitActor;
	FStruct_AttackStateDefinition* m_AttackerAttackStateREF;
	FHitResult* m_HitResultREF;

	FORCEINLINE bool CheckValid();

	// Some kinds of stats: attacker stats, gethit stats, calculated damage
};

FORCEINLINE FStruct_AttackDefinition::FStruct_AttackDefinition() : m_AttackerActor(nullptr), m_GetHitActor(nullptr), m_AttackerAttackStateREF(nullptr), m_HitResultREF(nullptr) {}

FORCEINLINE FStruct_AttackDefinition::FStruct_AttackDefinition(AActor* p_Attacker, AActor* p_GetHitActor, FStruct_AttackStateDefinition* p_AttackerAttackState, FHitResult* p_HitResult) :
	m_AttackerActor(p_Attacker), m_GetHitActor(p_GetHitActor), m_AttackerAttackStateREF(p_AttackerAttackState), m_HitResultREF(p_HitResult) {}

FORCEINLINE bool FStruct_AttackDefinition::CheckValid()
{
	if (m_AttackerActor == nullptr || m_GetHitActor == nullptr || m_AttackerAttackStateREF == nullptr || m_HitResultREF == nullptr) return false;
	return true;
}