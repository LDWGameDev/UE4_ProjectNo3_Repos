// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Library_Enum.h"
#include "Library_CustomMath.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API ULibrary_CustomMath : public UObject
{
	GENERATED_BODY()

/**
 * Functions 
 */
public:
	// Angle in range (-180, 180) between 2 vectors, 0 if something not valid
	// 2 vectors don't need to be normalized
	static float TwoVectorsAngle_Degrees180(FVector p_VectorFrom, FVector p_VectorTo);

	// Get the world location of a relative location to an actor
	// Returns (0, 0, 0) if actor not valid
	static FVector WorldLocationOfRelativeLocationToActor(const AActor* p_PivotActor, const FVector& p_RelativeLocation);

	// Get the enum represent the direction of the angle (Left, Right, Forward, Backward)
	static EDirection8Ways AngleTo4WaysDirection(float p_Angle);
};
