// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Struct_MontageToPlay.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FStruct_MontageToPlay : public FTableRowBase
{
	GENERATED_BODY()

	FORCEINLINE FStruct_MontageToPlay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName m_AnimMontageID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* m_AnimMontage;
};

FORCEINLINE FStruct_MontageToPlay::FStruct_MontageToPlay() { }