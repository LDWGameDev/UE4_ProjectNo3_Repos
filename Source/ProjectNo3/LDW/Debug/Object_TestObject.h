// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Object_TestObject.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNO3_API UObject_TestObject : public UObject
{
	GENERATED_BODY()


/**
	* Properties
	*/
public:
	int32 m_IntValue;
	FString m_StringValue;


/**
	* Functions
	*/
public:
	UObject_TestObject();
	static UObject_TestObject* CreateInstance(const int32& p_IntValue, const FString& p_StringValue);
	void Print();

private:
};



