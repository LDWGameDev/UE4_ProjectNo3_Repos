// Fill out your copyright notice in the Description page of Project Settings.


#include "Object_TestObject.h"


UObject_TestObject::UObject_TestObject() 
{
	m_IntValue = 0;
	m_StringValue = TEXT("");
}

UObject_TestObject* UObject_TestObject::CreateInstance(const int32& p_IntValue, const FString& p_StringValue) 
{
	UObject_TestObject* NewInstance = NewObject<UObject_TestObject>();
	NewInstance->m_IntValue = p_IntValue;
	NewInstance->m_StringValue = p_StringValue;
	return NewInstance;
}

void UObject_TestObject::Print()
{
	UE_LOG(LogTemp, Warning, TEXT("UObject_TestObject - Int: %d, String: %s"), m_IntValue, *m_StringValue);
}