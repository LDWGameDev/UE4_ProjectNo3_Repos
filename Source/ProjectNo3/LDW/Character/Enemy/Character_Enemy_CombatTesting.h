// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance_Enemy_CombatTesting.h"
#include "Character_EnemyBase.h"
#include "GameplayTagContainer.h"
#include "Character_Enemy_CombatTesting.generated.h"


class UCombatTesting_DamageState;
class UCombatTesting_IdleState;
class UCombatTesting_KnockOutSimulate;
class UCombatTesting_GetUpSimulate;

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

	UPROPERTY(EditDefaultsOnly, Category = "Custom EnemyCombatTesting")
		FGameplayTagContainer m_TagContainer_StatesCanChangeToGetDamage;

	// AnimInstance reference. Set value in BeginPlay()
	UPROPERTY()
		UAnimInstance_Enemy_CombatTesting* m_AnimInstanceREF_EnemyCombatTesting;

	// State references. Create and set values in InitStates()
	UPROPERTY()
		UCombatTesting_DamageState* m_DamageStateREF;
	UPROPERTY()
		UCombatTesting_IdleState* m_IdleStateREF;
	UPROPERTY()
		UCombatTesting_KnockOutSimulate* m_KnockOutSimulateStateREF;
	UPROPERTY()
		UCombatTesting_GetUpSimulate* m_GetUpSimulateStateREF;

protected:

private:




/**
 * Functions
 */

public:
	ACharacter_Enemy_CombatTesting();
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Inherited from EnemyBase
	virtual void ActivateEnemy(bool p_DoActivate) override;
	
	// Inherited from Interface_Attackable
	virtual void TakeHit(FStruct_AttackDefinition& p_AttackDefinition) override;

	// Find and play montage from m_DataTable_DamageMontage
	void PlayMontageFromTable_DamageMontage(const FName& p_MontageID);

protected:
	virtual void BeginPlay() override;

private:
	// Create state instances and set those references to variables
	void InitStates();



public:
	UFUNCTION(BlueprintCallable)
	void TestFunction(int32 p_CommandIndex);
};
