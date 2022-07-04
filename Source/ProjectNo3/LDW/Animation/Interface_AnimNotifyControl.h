// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "Interface_AnimNotifyControl.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_AnimNotifyControl : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTNO3_API IInterface_AnimNotifyControl
{
	GENERATED_BODY()

// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void HandleAnimNotify_StringID(const FString& p_StringID) = 0;
	virtual void HandleAnimNotify_GameplayTagContainer(const FGameplayTagContainer& m_GameplayTagContainer) = 0;
};
