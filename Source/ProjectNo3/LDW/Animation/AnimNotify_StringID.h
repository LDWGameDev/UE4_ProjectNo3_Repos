// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_StringID.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UAnimNotify_StringID : public UAnimNotify
{
	GENERATED_BODY()
	
/**
 * Properties
 */
public:
	UPROPERTY(EditAnywhere)
		FString m_StringID;
protected:
private:


/**
 * Functions
 */
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
protected:
private:
};
