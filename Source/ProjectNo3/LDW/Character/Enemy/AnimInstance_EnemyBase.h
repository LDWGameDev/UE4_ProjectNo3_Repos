// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_EnemyBase.generated.h"


class ACharacter_EnemyBase;

/**
 * 
 */

UCLASS()
class PROJECTNO3_API UAnimInstance_EnemyBase : public UAnimInstance
{
	GENERATED_BODY()
	

/**
 * Properties
 */

public:
protected:
	ACharacter_EnemyBase* m_CharacterREF_EnemyBase;
private:



/**
 * Functions
 */

public:
	virtual void NativeBeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
		void HandleAnimNotify_01();
	UFUNCTION(BlueprintCallable)
		void HandleAnimNotify_02();
	UFUNCTION(BlueprintCallable)
		void HandleAnimNotify_03();
	UFUNCTION(BlueprintCallable)
		void HandleEndMontage();

protected:
private:

};
