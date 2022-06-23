// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"

#include "System/CombatSystem/Interface_Attackable.h"
#include "System/InteractingSystem/Interface_GameplayTagControl.h"
#include "Character_EnemyBase.generated.h"


class UCurveFloat;

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
	UPROPERTY(EditDefaultsOnly, Category = "Custom EnemyCombatTesting")
		FGameplayTagContainer m_TagContainer;

	UPROPERTY(EditDefaultsOnly, Category = "Custom EnemyCombatTesting")
		UCurveFloat* m_CurveFloat_AlphaEaseInOut;

protected:

private:
	FTimeline m_Timeline_LocationControl;
	FVector m_SavedCurrentLocation;
	FVector m_SavedNewLocation;



/**
 * Functions
 */

public:
	ACharacter_EnemyBase();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Inherited from IInterface_Attackable
	virtual void TakeHit(FStruct_AttackDefinition& p_AttackDefinition);

	// Inherited from IInterface_GameplayTagControl
	const FGameplayTagContainer& GetTagContainer() override;
	
	// Move this actor to a location using m_Timeline_LocationControl
	void MoveToLocation(const FVector& p_NewLocation, float p_BlendTime);

protected:
	virtual void BeginPlay() override;

private:
	// Init timeline component in BeginPlay()
	void InitTimelines();
	// Tick timeline component in Tick()
	void TickTimelines(float p_DeltaTime);

};