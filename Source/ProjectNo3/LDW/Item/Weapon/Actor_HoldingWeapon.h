// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Actor_HoldingWeapon.generated.h"



UCLASS()
class PROJECTNO3_API AActor_HoldingWeapon : public AActor
{
	GENERATED_BODY()

/**
 * Properties
 */
public:
	UPROPERTY(BlueprintReadOnly)
		USceneComponent* m_SceneRootComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* m_StaticMesh_Weapon;

protected:

private:



/**
 * Public member functions
 */
public:	
	AActor_HoldingWeapon();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:

};
