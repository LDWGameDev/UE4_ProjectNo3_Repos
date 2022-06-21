// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_WeaponObject.generated.h"

UCLASS()
class PROJECTNO3_API AActor_WeaponObject : public AActor
{
	GENERATED_BODY()
	

/**
 * Properties
 */

public:

protected:

private:



/**
 * Functions
 */

public:	
	AActor_WeaponObject();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:	

};
