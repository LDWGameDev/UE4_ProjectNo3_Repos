// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character_EnemyBase.h"
#include "Components/TimelineComponent.h"
#include "Character_Enemy_CombatTesting.generated.h"


class UCurveFloat;


/**
 * 
 */
UCLASS()
class PROJECTNO3_API ACharacter_Enemy_CombatTesting : public ACharacter_EnemyBase
{
	GENERATED_BODY()


/**
 * Properties
 */

public:
	UPROPERTY(EditDefaultsOnly)
		UCurveFloat* m_CurveFloat_AlphaEaseInOut;

protected:

private:
	FTimeline m_Timeline_PositionControl;
	FVector m_SavedCurrentPosition;
	FVector m_SavedNewPosition;


/**
 * Functions
 */

public:
	ACharacter_Enemy_CombatTesting();
	virtual void Tick(float DeltaTime) override;
	// Inherited from Interface_Attackable
	virtual void TakeHit(FStruct_AttackDefinition& p_AttackDefinition) override;

protected:
	virtual void BeginPlay() override;

private:
	// Init timeline component in BeginPlay()
	void InitTimelines();
	// Tick timeline component in Tick()
	void TickTimelines(float p_DeltaTime);
};
