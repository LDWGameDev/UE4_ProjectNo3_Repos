// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "../Interface/Interface_PlayerControllerInput.h"
#include "PlayerController_GameplayMain.generated.h"


UCLASS()
class PROJECTNO3_API APlayerController_GameplayMain : public APlayerController, public IInterface_PlayerControllerInput
{
	GENERATED_BODY()


/**
 * Properties
 */
public:
	UPROPERTY(EditAnywhere)
		float m_MouseSensitive;
	UPROPERTY(EditDefaultsOnly)
		float m_HoldTimeToRun;

protected:

private:
	// Delegate signatures
	FDelegate1_MovementSignature m_Delegate_MoveForward;
	FDelegate1_MovementSignature m_Delegate_MoveRight;
	FDelegate_JumpSignature m_Delegate_JumpPressed;
	FDelegate_JumpSignature m_Delegate_JumpReleased;
	FDelegate_ActionSignature m_Delegate_DashStart;
	FDelegate_ActionSignature m_Delegate_RunStart;
	FDelegate_ActionSignature m_Delegate_RunEnd;
	FDelegate_ActionSignature m_Delegate_LightAttackStart;
	FDelegate_ActionSignature m_Delegate_HeavyAttackStart;
	FDelegate_ActionSignature m_Delegate_BuffWeapon_01;

	bool b_ShouldCountHoldTime_Dash;
	float m_HoldTimeCount_Dash;



/**
 * Functions
 */

public:
	APlayerController_GameplayMain();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void SetupInputComponent() override;
	
	FDelegate1_MovementSignature* GetDelegate_MoveForward() override;
	FDelegate1_MovementSignature* GetDelegate_MoveRight() override;
	FDelegate_JumpSignature* GetDelegate_JumpPressed() override;
	FDelegate_JumpSignature* GetDelegate_JumpReleased() override;
	FDelegate_ActionSignature* GetDelegate_DashStart() override;
	FDelegate_ActionSignature* GetDelegate_RunStart() override;
	FDelegate_ActionSignature* GetDelegate_RunEnd() override;
	FDelegate_ActionSignature* GetDelegate_LightAttackStart() override;
	FDelegate_ActionSignature* GetDelegate_HeavyAttackStart() override;
	FDelegate_ActionSignature* GetDelegate_BuffWeapon_01() override;


private:
	// Functions handle input from player
	void BindAxis_MoveForward(float value);
	void BindAxis_MoveRight(float value);
	void BindAxis_LookUp(float value);
	void BindAxis_LookRight(float value);
	void BindAction_JumpPressed();
	void BindAction_JumpReleased();
	void BindAction_DashPressed();
	void BindAction_DashReleased();
	void BindAction_LightAttackPressed();
	void BindAction_HeavyAttackPressed();
	void BindAction_BuffWeapon_01_Pressed();
};
