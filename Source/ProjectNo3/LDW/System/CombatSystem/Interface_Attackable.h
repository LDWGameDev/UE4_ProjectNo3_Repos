// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "System_CombatContainer.h"
#include "Interface_Attackable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_Attackable : public UInterface
{
	GENERATED_BODY()
};



/**
 * 
 */
class PROJECTNO3_API IInterface_Attackable
{
	GENERATED_BODY()

public:
	virtual void TakeHit(FStruct_AttackDefinition& p_AttackDefinition) = 0;
};
