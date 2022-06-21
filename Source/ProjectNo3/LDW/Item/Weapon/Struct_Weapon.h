// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "Actor_WeaponObject.h"
#include "Actor_HoldingWeapon.h"
#include "Struct_Weapon.generated.h"


UENUM()
enum class EWeaponType : uint8
{
	None					UMETA(DisplayName = "None"),
	AssassinSword			UMETA(DisplayName = "Assassin Sword")
};


USTRUCT(BlueprintType)
struct FStruct_Weapon : public FTableRowBase
{
	GENERATED_BODY()

	FORCEINLINE FStruct_Weapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplayTagContainer m_WeaponTagContainer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName m_WeaponID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString m_WeaponName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EWeaponType m_EnumWeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor_HoldingWeapon> m_HoldingWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor_WeaponObject> m_WeaponObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName m_AttachingSocketName;

public:
	FORCEINLINE int32 GetWeaponEnumIndex();
	FORCEINLINE bool CheckValid();
};


FORCEINLINE FStruct_Weapon::FStruct_Weapon() {}

FORCEINLINE int32 FStruct_Weapon::GetWeaponEnumIndex()
{
	return static_cast<int32>(m_EnumWeaponType);
}

FORCEINLINE bool FStruct_Weapon::CheckValid()
{
	if (m_HoldingWeapon == nullptr || m_WeaponObject == nullptr || !m_WeaponTagContainer.IsValid()) return false;
	return true;
}