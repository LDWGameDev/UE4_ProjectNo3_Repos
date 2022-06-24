// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_Dev01.h"
#include "Character/Player/Character_PlayerHuman.h"
#include "PlayerController/PlayerController_GameplayMain.h"

AGameMode_Dev01::AGameMode_Dev01() 
{
	PlayerControllerClass = APlayerController_GameplayMain::StaticClass();
	DefaultPawnClass = ACharacter_PlayerHuman::StaticClass();
}