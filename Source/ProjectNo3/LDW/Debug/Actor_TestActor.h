// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Misc/Timespan.h"
#include "Components/TimelineComponent.h" 
#include "Curves/CurveFloat.h"
#include "Item/Weapon/Struct_Weapon.h"
#include "Object_TestObject.h"
#include "System/CombatSystem/Interface_Attackable.h"
#include "Actor_TestActor.generated.h"


UCLASS(BlueprintType)
class PROJECTNO3_API AActor_TestActor : public AActor, public IInterface_Attackable
{
	GENERATED_BODY()
	
/**
 * Properties
 */

public:
	UPROPERTY(EditDefaultsOnly)
		FStruct_Weapon m_StructWeaponTest;
	UPROPERTY()
		TArray<UObject_TestObject*> m_TestObjectList;

	// Curve used for timeline. Has to be pointer
	UPROPERTY(EditDefaultsOnly, Category = "Custom Timeline")
		UCurveFloat* m_TimelineCurve;
	FTimeline m_Timeline;

	// Function to bind with timeline progress. Has to be marked as UFUNCTION()
	UFUNCTION()
		void TimelineProgress_01(float p_Value);
	UFUNCTION()
		void TimelineEventEvent();

	virtual void TakeHit(FStruct_AttackDefinition& p_AttackDefinition) override;

private:
	// First 10 elements will be allocated in stack memory,
	// others behind 10 will be allocated in heap 
	TArray<UObject_TestObject*, TInlineAllocator<10>> m_TestObjectListDynamicStack;
	FTimerHandle m_TestTimerHandle;
	FDateTime DateTime_01;
	FDateTime DateTime_02;

/**
 * Functions
 */
public:	
	AActor_TestActor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	void TArrayTestFunction();
	void TArrayOptimization();
	void TestTimerFunction();
};


// Something something something 