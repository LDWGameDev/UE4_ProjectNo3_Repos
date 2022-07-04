// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHuman/PlayerHuman_BaseState.h"

#include "PlayerHuman/PlayerHumanState_UnarmedDash.h"
#include "PlayerHuman/PlayerHumanState_UnarmedFalling.h"
#include "PlayerHuman/PlayerHumanState_UnarmedIdle.h"
#include "PlayerHuman/PlayerHumanState_UnarmedJog.h"
#include "PlayerHuman/PlayerHumanState_UnarmedJump.h"
#include "PlayerHuman/PlayerHumanState_UnarmedRun.h"

#include "PlayerHuman/PlayerHumanState_AssassinEquip.h"
#include "PlayerHuman/PlayerHumanState_AssassinUnequip.h"
#include "PlayerHuman/PlayerHumanState_AssassinIdle.h"
#include "PlayerHuman/PlayerHumanState_AssassinJog.h"
#include "PlayerHuman/PlayerHumanState_AssassinRun.h"
#include "PlayerHuman/PlayerHumanState_AssassinDash.h"
#include "PlayerHuman/PlayerHumanState_AssassinDash_2.h"
#include "PlayerHuman/PlayerHumanState_AssassinFalling.h"
#include "PlayerHuman/PlayerHumanState_AssassinJump.h"
#include "PlayerHuman/PlayerHumanState_AssassinLA_C1_1.h"
#include "PlayerHuman/PlayerHumanState_AssassinLA_C1_2.h"
#include "PlayerHuman/PlayerHumanState_AssassinLA_C1_3.h"
#include "PlayerHuman/PlayerHumanState_AssassinHA_C1_1.h"
#include "PlayerHuman/PlayerHumanState_AssassinHA_C1_2.h"
#include "PlayerHuman/PlayerHumanState_AssassinHA_C2_1.h"
#include "PlayerHuman/PlayerHumanState_AssassinHA_C2_2.h"
#include "PlayerHuman/PlayerHumanState_AssassinHA_C2_3.h"
#include "PlayerHuman/PlayerHumanState_AssassinHA_C2_4.h"
#include "PlayerHuman/PlayerHumanState_AssassinHA_C3_1.h"
#include "PlayerHuman/PlayerHumanState_AssassinHA_C3_2.h"
#include "PlayerHuman/PlayerHumanState_AssGetUp.h"
#include "PlayerHuman/PlayerHumanState_AssKnockDown.h"



/**
 * 
 */
class PROJECTNO3_API ContainerPlayerStates
{
public:
	ContainerPlayerStates();
	~ContainerPlayerStates();
};

ContainerPlayerStates::ContainerPlayerStates() {}
ContainerPlayerStates::~ContainerPlayerStates() {}