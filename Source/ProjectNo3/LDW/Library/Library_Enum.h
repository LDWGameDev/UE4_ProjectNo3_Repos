// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Library_Enum.generated.h"


/**
 * 8 ways direction enum
 */
UENUM(BlueprintType)
enum class EDirection8Ways : uint8
{
	Forward					UMETA(DisplayName = "Forward"),
	Forward_Left			UMETA(DisplayName = "Forward Left"),
	Forward_Right			UMETA(DisplayName = "Forward Right"),
	Left					UMETA(DisplayName = "Left"),
	Right					UMETA(DisplayName = "Right"),
	Backward_Left			UMETA(DisplayName = "Backward Left"),
	Backward_Right			UMETA(DisplayName = "Backward Right"),
	Backward				UMETA(DisplayName = "Backward")
};
