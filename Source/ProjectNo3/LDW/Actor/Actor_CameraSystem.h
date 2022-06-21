// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraActor.h"
#include "GameFramework/PlayerController.h"
#include "Actor_CameraSystem.generated.h"


DECLARE_MULTICAST_DELEGATE(FDelegate_ReturnViewTargetSignature)

UCLASS()
class PROJECTNO3_API AActor_CameraSystem : public AActor
{
	GENERATED_BODY()
	

/**
 * Properties
 */

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom Actor Camera System")
		USpringArmComponent* m_SpringArm_Camera_01;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom Actor Camera System")
		USpringArmComponent* m_SpringArm_Camera_02;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom Actor Camera System")
		USpringArmComponent* m_SpringArm_Camera_03;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom Actor Camera System")
		ACameraActor* m_CameraActor_Camera_01;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom Actor Camera System")
		ACameraActor* m_CameraActor_Camera_02;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Custom Actor Camera System")
		ACameraActor* m_CameraActor_Camera_03;

	FDelegate_ReturnViewTargetSignature m_Delegate_ReturnViewTarget;

protected:
	UPROPERTY()
		USceneComponent* m_SceneRootComponent;

	UPROPERTY(BlueprintReadOnly)
		APlayerController* m_SavedPlayerController;

private:



/**
 * Functions
 */

public:	
	AActor_CameraSystem();
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
		void SetViewTargetToActorSequence(const FName& p_ActorSequenceID, APlayerController* p_PlayerControllerToSetView);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void ReturnViewTarget();

	UFUNCTION(BlueprintCallable)
		void SetViewTargetToCameraActor(int32 p_CameraID, float p_BlendTime = 0.0f, EViewTargetBlendFunction p_BlendFunction = EViewTargetBlendFunction::VTBlend_EaseInOut, float p_BlendExp = 1.0f, bool p_LockToCameraView = true);

private:

};
