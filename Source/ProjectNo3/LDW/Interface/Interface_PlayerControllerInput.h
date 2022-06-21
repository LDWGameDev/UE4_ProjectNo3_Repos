// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_PlayerControllerInput.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate1_MovementSignature, float)
DECLARE_MULTICAST_DELEGATE(FDelegate_JumpSignature);
DECLARE_MULTICAST_DELEGATE(FDelegate_ActionSignature);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_PlayerControllerInput : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTNO3_API IInterface_PlayerControllerInput
{
	GENERATED_BODY()

public:
	virtual FDelegate1_MovementSignature* GetDelegate_MoveForward() = 0;
	virtual FDelegate1_MovementSignature* GetDelegate_MoveRight() = 0;
	virtual FDelegate_JumpSignature* GetDelegate_JumpPressed() = 0;
	virtual FDelegate_JumpSignature* GetDelegate_JumpReleased() = 0;
	virtual FDelegate_ActionSignature* GetDelegate_DashStart() = 0;
	virtual FDelegate_ActionSignature* GetDelegate_RunStart() = 0;
	virtual FDelegate_ActionSignature* GetDelegate_RunEnd() = 0;
	virtual FDelegate_ActionSignature* GetDelegate_LightAttackStart() = 0;
	virtual FDelegate_ActionSignature* GetDelegate_HeavyAttackStart() = 0;
	virtual FDelegate_ActionSignature* GetDelegate_BuffWeapon_01() = 0;
};