// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character_EnemyBase.h"
#include "AnimInstance_Enemy_CombatTesting.h"
#include "Character_Enemy_CombatTesting.generated.h"


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
	// DataTable contains damage montages
	UPROPERTY(EditDefaultsOnly, Category = "Custom EnemyCombatTesting")
		UDataTable* m_DataTable_DamageMontages;

	// AnimInstance reference. Set value in BeginPlay()
	UPROPERTY()
		UAnimInstance_Enemy_CombatTesting* m_AnimInstanceREF_EnemyCombatTesting;

protected:

private:




/**
 * Functions
 */

public:
	ACharacter_Enemy_CombatTesting();
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Inherited from Interface_Attackable
	virtual void TakeHit(FStruct_AttackDefinition& p_AttackDefinition) override;


protected:
	virtual void BeginPlay() override;

private:

};
