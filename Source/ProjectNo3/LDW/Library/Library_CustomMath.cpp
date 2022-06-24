// Fill out your copyright notice in the Description page of Project Settings.

#include "Library_CustomMath.h"
#include "Kismet/KismetMathLibrary.h"


float ULibrary_CustomMath::TwoVectorsAngle_Degrees180(FVector p_VectorFrom, FVector p_VectorTo)
{
	if (UKismetMathLibrary::Vector_IsNearlyZero(p_VectorFrom, 0.01f) || UKismetMathLibrary::Vector_IsNearlyZero(p_VectorTo, 0.01f)) return 0.0f;
	
	p_VectorFrom.Normalize();
	p_VectorTo.Normalize();
	float Angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(p_VectorFrom, p_VectorTo)));
	Angle = ((FVector::CrossProduct(p_VectorFrom, p_VectorTo)).Z > 0) ? Angle : -Angle;
	return Angle;
}

FVector ULibrary_CustomMath::WorldLocationOfRelativeLocationToActor(const AActor* p_PivotActor, const FVector& p_RelativeLocation)
{
	if(p_PivotActor == nullptr) return FVector::ZeroVector;
	FVector AdditionLocation = p_RelativeLocation.X * p_PivotActor->GetActorForwardVector() + p_RelativeLocation.Y * p_PivotActor->GetActorRightVector() + p_RelativeLocation.Z * p_PivotActor->GetActorUpVector();
	return AdditionLocation + p_PivotActor->GetActorLocation();
}

EDirection8Ways ULibrary_CustomMath::AngleTo4WaysDirection(float p_Angle)
{
	float Angle = FMath::Clamp(p_Angle, -180.0f, 180.0f);
	if (Angle >= -45.0f && Angle <= 45.0f) return EDirection8Ways::Forward;
	else if (Angle > -135.0f && Angle < -45.0f) return EDirection8Ways::Left;
	else if (Angle > 45.0f && Angle < 135.0f) return EDirection8Ways::Right;
	return EDirection8Ways::Backward;
}