// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_TestActor.h"
#include "Kismet/KismetStringLibrary.h"
#include "GameplayTagContainer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Library/Library_CustomMath.h"

/**
 * Override Functions
 */
AActor_TestActor::AActor_TestActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AActor_TestActor::BeginPlay()
{
	Super::BeginPlay();
	// GetWorldTimerManager().SetTimer(m_TestTimerHandle, this, &AActor_TestActor::TestTimerFunction, 1.0f, false, 1.0f);
	// DateTime_01 = FDateTime::UtcNow();
	//if (m_TimelineCurve != nullptr)
	//{
	//	FOnTimelineFloat TimelineProgress_01;
	//	FOnTimelineEvent TimelineEndEventProgress;
	//	TimelineEndEventProgress.BindUFunction(this, FName(TEXT("TimelineEventEvent")));
	//	TimelineProgress_01.BindUFunction(this, FName(TEXT("TimelineProgress_01")));

	//	m_Timeline.AddInterpFloat(m_TimelineCurve, TimelineProgress_01);
	//	m_Timeline.SetLooping(true);
	//	m_Timeline.SetTimelineFinishedFunc(TimelineEndEventProgress);
	//	m_Timeline.PlayFromStart();
	//
}

void AActor_TestActor::TimelineEventEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Timeline End Event"));

}

void AActor_TestActor::TimelineProgress_01(float p_Value)
{
}

void AActor_TestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_Timeline.TickTimeline(DeltaTime);
}

void AActor_TestActor::TArrayTestFunction()
{
	// Create 10 instances of UObjectTestObject using static function CreateInstance()
	for (int i = 0; i < 10; i++) {
		m_TestObjectList.Add(UObject_TestObject::CreateInstance(i, UKismetStringLibrary::Conv_IntToString(i)));
	}

	// Sort TArray in descending order and instance with FString = "2" at the begin of the array
	m_TestObjectList.Sort([](const UObject_TestObject& obj1, const UObject_TestObject& obj2) {
		if (UKismetStringLibrary::EqualEqual_StrStr(obj1.m_StringValue, TEXT("2"))) return true;
		if (UKismetStringLibrary::EqualEqual_StrStr(obj2.m_StringValue, TEXT("2"))) return false;
		return obj1.m_IntValue > obj2.m_IntValue;
		});

	// Print array
	for (UObject_TestObject* testObject : m_TestObjectList) {
		testObject->Print();
	}

	// Find element using Predicate (lambda)
	UObject_TestObject** FoundObject = m_TestObjectList.FindByPredicate([](const UObject_TestObject* p_ObjectToFind) {
		return (p_ObjectToFind->m_IntValue == 3);
		});
	if (FoundObject != nullptr) (*FoundObject)->Print();
}

void AActor_TestActor::TArrayOptimization()
{
	// Reserve memory for 10 elements before adding
	m_TestObjectList.Reserve(10); 

	// Create 10 instances of UObjectTestObject using static function CreateInstance()
	for (int i = 0; i < 10; i++) {
		m_TestObjectList.Add(UObject_TestObject::CreateInstance(i, UKismetStringLibrary::Conv_IntToString(i)));
	}
}

void AActor_TestActor::TestTimerFunction()
{
	/*GetWorldTimerManager().SetTimer(m_TestTimerHandle, this, &AActor_TestActor::TestTimerFunction, 1.0f, false, 1.0f);
	GetWorldTimerManager().PauseTimer(m_TestTimerHandle);
	GetWorldTimerManager().ClearTimer(m_TestTimerHandle);*/

	DateTime_02 = FDateTime::UtcNow();
	FTimespan Timespan = DateTime_02 - DateTime_01;
	float a = Timespan.GetTotalMilliseconds();
	UE_LOG(LogTemp, Warning, TEXT("Actor_TestActor - Timespan: %f"), a);
}