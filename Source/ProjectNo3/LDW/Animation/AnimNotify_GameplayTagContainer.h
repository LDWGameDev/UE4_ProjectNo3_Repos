// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AnimNotify_GameplayTagContainer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UAnimNotify_GameplayTagContainer : public UAnimNotify
{
	GENERATED_BODY()
	
/**
 * Properties
 */
public:
	UPROPERTY(EditAnywhere)
		FGameplayTagContainer m_TagContainer;


/**
 * Functions
 */
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
protected:
private:
};
