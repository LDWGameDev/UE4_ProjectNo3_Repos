// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraActor.h"
#include "Component_StaticCameraManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTNO3_API UComponent_StaticCameraManager : public UActorComponent
{
	GENERATED_BODY()


/**
 * Properties
 */

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		ACameraActor* m_CameraActor_01;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		ACameraActor* m_CameraActor_02;

protected:

private:




/**
 * Functions
 */

public:	
	UComponent_StaticCameraManager();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void CreateCameraInstances();
	void SetStaticCamera_01(const FVector& p_Location, const FRotator& p_Rotation);
	void SetStaticCamera_01(const FVector& p_Location, const FVector& p_LocationToLookAt);
	void SetStaticCamera_01(const FVector& p_Location, const FVector& p_LocationToLookAt, AActor* p_ActorToAttach);
	void SetStaticCamera_01(const AActor* p_ActorToLookAt, const FVector& p_RelativeLocation, const FRotator& p_RotationOffsetToTarget);

	void SetStaticCamera_02(const FVector& p_Location, const FVector& p_LocationToLookAt);

protected:
	virtual void BeginPlay() override;

private:	

};
