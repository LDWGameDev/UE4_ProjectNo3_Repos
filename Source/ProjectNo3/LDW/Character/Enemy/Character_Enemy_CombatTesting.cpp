// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Enemy_CombatTesting.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Character/Struct_MontageToPlay.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Library/Library_CustomMath.h"



ACharacter_Enemy_CombatTesting::ACharacter_Enemy_CombatTesting()
{
	// Set CapsuleComponent defaults
	GetCapsuleComponent()->InitCapsuleSize(40.0f, 86.0f);

	// Set CharacterMovement defaults
	GetCharacterMovement()->GravityScale = 2.5f;

}

void ACharacter_Enemy_CombatTesting::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ACharacter_Enemy_CombatTesting::BeginPlay()
{
	Super::BeginPlay();
	m_AnimInstanceREF_EnemyCombatTesting = Cast<UAnimInstance_Enemy_CombatTesting>(GetMesh()->GetAnimInstance());
}

void ACharacter_Enemy_CombatTesting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}





/**
 * Interface functions
 */

void ACharacter_Enemy_CombatTesting::TakeHit(FStruct_AttackDefinition& p_AttackDefinition)
{
	Super::TakeHit(p_AttackDefinition);
	// Turn off checking valid for debugging
	// if (!p_AttackDefinition.CheckValid()) return;

	// To calculate damage direction (L, R, F, B) to play damage montage
	// First, RotatorDamageDirection = LookAtRotator from attacked to attacker
	FRotator RotatorDamageDirection = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), (p_AttackDefinition.m_AttackerActor)->GetActorLocation());
	RotatorDamageDirection.Pitch = 0.0f;
	RotatorDamageDirection.Roll = 0.0f;
	
	// Second, add appropriate yaw rotation via attack direction
	switch ((p_AttackDefinition.m_AttackerAttackStateREF)->m_AttackDirection)
	{
	case EDirectionAttack6Ways::Front:
	{
		break;
	}
	case EDirectionAttack6Ways::Back:
	{
		RotatorDamageDirection.Yaw += 180.0f;
		break;
	}
	case EDirectionAttack6Ways::Left:
	{
		RotatorDamageDirection.Yaw -= 90.0f;
		break;
	}
	case EDirectionAttack6Ways::Right:
	{
		RotatorDamageDirection.Yaw += 90.0f;
		break;
	}
	}

	float DamageAngle = ULibrary_CustomMath::TwoVectorsAngle_Degrees180(UKismetMathLibrary::GetForwardVector(this->GetActorRotation()), UKismetMathLibrary::GetForwardVector(RotatorDamageDirection));

	if (DamageAngle >= -45.0f && DamageAngle <= 45.0f)
	{
		FStruct_MontageToPlay* MontageStruct = m_DataTable_DamageMontages->FindRow<FStruct_MontageToPlay>(FName(TEXT("Damage_Light_F_01_Inplace")), nullptr, false);
		if (MontageStruct != nullptr && MontageStruct->m_AnimMontage != nullptr)
		{
			this->PlayAnimMontage(MontageStruct->m_AnimMontage);
		}
	}
	else if (DamageAngle > -135.0f && DamageAngle < -45.0f)
	{
		FStruct_MontageToPlay* MontageStruct = m_DataTable_DamageMontages->FindRow<FStruct_MontageToPlay>(FName(TEXT("Damage_Light_L_01_Inplace")), nullptr, false);
		if (MontageStruct != nullptr && MontageStruct->m_AnimMontage != nullptr)
		{
			this->PlayAnimMontage(MontageStruct->m_AnimMontage);
		}
	}
	else if (DamageAngle > 45.0f && DamageAngle < 135.0f)
	{
		FStruct_MontageToPlay* MontageStruct = m_DataTable_DamageMontages->FindRow<FStruct_MontageToPlay>(FName(TEXT("Damage_Light_R_01_Inplace")), nullptr, false);
		if (MontageStruct != nullptr && MontageStruct->m_AnimMontage != nullptr)
		{
			this->PlayAnimMontage(MontageStruct->m_AnimMontage);
		}
	}
	else
	{
		FStruct_MontageToPlay* MontageStruct = m_DataTable_DamageMontages->FindRow<FStruct_MontageToPlay>(FName(TEXT("Damage_Light_B_01_Inplace")), nullptr, false);
		if (MontageStruct != nullptr && MontageStruct->m_AnimMontage != nullptr)
		{
			this->PlayAnimMontage(MontageStruct->m_AnimMontage);
		}
	}

	//switch ((p_AttackDefinition.m_AttackerAttackStateREF)->m_HitType)
	//{
	//case EHitType::LightAttack:
	//{
	//	FStruct_MontageToPlay* MontageStruct = m_DataTable_DamageMontages->FindRow<FStruct_MontageToPlay>(FName(TEXT("Damage_Light_F_01_Inplace")), nullptr, false);
	//	if (MontageStruct != nullptr && MontageStruct->m_AnimMontage != nullptr)
	//	{
	//		this->PlayAnimMontage(MontageStruct->m_AnimMontage);
	//	}
	//	break;
	//}
	//case EHitType::Knock:
	//{
	//	break;
	//}
	//}
}
