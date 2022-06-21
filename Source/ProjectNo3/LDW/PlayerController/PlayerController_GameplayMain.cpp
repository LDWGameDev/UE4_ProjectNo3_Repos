// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_GameplayMain.h"


APlayerController_GameplayMain::APlayerController_GameplayMain() 
{
	m_MouseSensitive = 0.5f;
	m_HoldTimeToRun = 0.25f;
	m_HoldTimeCount_Dash = 0.0f;
	b_ShouldCountHoldTime_Dash = false;
}



/**
 * Override functions
 */

void APlayerController_GameplayMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (b_ShouldCountHoldTime_Dash)
	{
		m_HoldTimeCount_Dash += DeltaTime;
		if (m_HoldTimeCount_Dash > m_HoldTimeToRun)
		{
			b_ShouldCountHoldTime_Dash = false;
			if (m_Delegate_RunStart.IsBound()) m_Delegate_RunStart.Broadcast();

			// Set hold time count > hold time need to change to run
			// Used when release dash input
			m_HoldTimeCount_Dash = m_HoldTimeToRun * 2.0f;;
		}
	}
}

void APlayerController_GameplayMain::SetupInputComponent() 
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &APlayerController_GameplayMain::BindAxis_MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerController_GameplayMain::BindAxis_MoveRight);
	InputComponent->BindAxis("LookUp", this, &APlayerController_GameplayMain::BindAxis_LookUp);
	InputComponent->BindAxis("LookRight", this, &APlayerController_GameplayMain::BindAxis_LookRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerController_GameplayMain::BindAction_JumpPressed);
	InputComponent->BindAction("Jump", IE_Released, this, &APlayerController_GameplayMain::BindAction_JumpReleased);
	InputComponent->BindAction("Dash", IE_Pressed, this, &APlayerController_GameplayMain::BindAction_DashPressed);
	InputComponent->BindAction("Dash", IE_Released, this, &APlayerController_GameplayMain::BindAction_DashReleased);
	InputComponent->BindAction("LightAttack", IE_Pressed, this, &APlayerController_GameplayMain::BindAction_LightAttackPressed);
	InputComponent->BindAction("HeavyAttack", IE_Pressed, this, &APlayerController_GameplayMain::BindAction_HeavyAttackPressed);
	InputComponent->BindAction("BuffWeapon_01", IE_Pressed, this, &APlayerController_GameplayMain::BindAction_BuffWeapon_01_Pressed);
}




/**
 * Get, set member functions
 */

FDelegate1_MovementSignature* APlayerController_GameplayMain::GetDelegate_MoveForward()
{
	return &m_Delegate_MoveForward;
}

FDelegate1_MovementSignature* APlayerController_GameplayMain::GetDelegate_MoveRight()
{
	return &m_Delegate_MoveRight;
}

FDelegate_JumpSignature* APlayerController_GameplayMain::GetDelegate_JumpPressed()
{
	return &m_Delegate_JumpPressed;
}

FDelegate_JumpSignature* APlayerController_GameplayMain::GetDelegate_JumpReleased()
{
	return &m_Delegate_JumpReleased;
}

FDelegate_ActionSignature* APlayerController_GameplayMain::GetDelegate_DashStart()
{
	return &m_Delegate_DashStart;
}

FDelegate_ActionSignature* APlayerController_GameplayMain::GetDelegate_RunStart()
{
	return &m_Delegate_RunStart;
}

FDelegate_ActionSignature* APlayerController_GameplayMain::GetDelegate_RunEnd()
{
	return &m_Delegate_RunEnd;
}

FDelegate_ActionSignature* APlayerController_GameplayMain::GetDelegate_LightAttackStart()
{
	return &m_Delegate_LightAttackStart;
}

FDelegate_ActionSignature* APlayerController_GameplayMain::GetDelegate_HeavyAttackStart()
{
	return &m_Delegate_HeavyAttackStart;
}

FDelegate_ActionSignature* APlayerController_GameplayMain::GetDelegate_BuffWeapon_01()
{
	return &m_Delegate_BuffWeapon_01;
}






/**
 * Private member functions
 */

void APlayerController_GameplayMain::BindAxis_LookUp(float value) 
{
	AddPitchInput(value * m_MouseSensitive);
}

void APlayerController_GameplayMain::BindAxis_LookRight(float value) 
{
	AddYawInput(value * m_MouseSensitive);
}

void APlayerController_GameplayMain::BindAxis_MoveForward(float value) 
{
	if (m_Delegate_MoveForward.IsBound()) m_Delegate_MoveForward.Broadcast(value);
}

void APlayerController_GameplayMain::BindAxis_MoveRight(float value) 
{
	if (m_Delegate_MoveRight.IsBound()) m_Delegate_MoveRight.Broadcast(value);
}

void APlayerController_GameplayMain::BindAction_JumpPressed()
{
	if (m_Delegate_JumpPressed.IsBound()) m_Delegate_JumpPressed.Broadcast();
}

void APlayerController_GameplayMain::BindAction_JumpReleased()
{
	if (m_Delegate_JumpReleased.IsBound()) m_Delegate_JumpReleased.Broadcast();
}

void APlayerController_GameplayMain::BindAction_DashPressed()
{
	m_HoldTimeCount_Dash = 0.0f;
	b_ShouldCountHoldTime_Dash = true;
}

void APlayerController_GameplayMain::BindAction_DashReleased()
{
	b_ShouldCountHoldTime_Dash = false;
	if (m_HoldTimeCount_Dash < m_HoldTimeToRun)
	{
		if (m_Delegate_DashStart.IsBound()) m_Delegate_DashStart.Broadcast();
	}
	else
	{
		if (m_Delegate_RunEnd.IsBound()) m_Delegate_RunEnd.Broadcast();
	}
}

void APlayerController_GameplayMain::BindAction_LightAttackPressed()
{
	if (m_Delegate_LightAttackStart.IsBound()) m_Delegate_LightAttackStart.Broadcast();
}

void APlayerController_GameplayMain::BindAction_HeavyAttackPressed()
{
	if (m_Delegate_HeavyAttackStart.IsBound()) m_Delegate_HeavyAttackStart.Broadcast();
}

void APlayerController_GameplayMain::BindAction_BuffWeapon_01_Pressed()
{
	if (m_Delegate_BuffWeapon_01.IsBound()) m_Delegate_BuffWeapon_01.Broadcast();
}