// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "Character/Player/Character_PlayerHuman.h"
#include "System/CombatSystem/System_CombatContainer.h"
#include "Actor_PlayerThrowingWeapon.generated.h"

class USoundBase;

UCLASS()
class PROJECTNO3_API AActor_PlayerThrowingWeapon : public AActor
{
	GENERATED_BODY()
	

/**
 * Properties
 */

public:
	UPROPERTY(EditDefaultsOnly)
		UNiagaraSystem* m_NiagaraSystem_HitFire;
	UPROPERTY(EditDefaultsOnly)
		USoundBase* m_SoundBase_Explosion;

	ACharacter_PlayerHuman* m_CharacterPlayerHumanREF;
	FStruct_AttackStateDefinition* m_AttackStateREF;

protected:
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USphereComponent* m_SphereComponent_Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* m_StaticMesh_Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* m_ProjectileMovement_01;


/**
 * Functions
 */

public:
	AActor_PlayerThrowingWeapon();
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	void SetReferenceValues(ACharacter_PlayerHuman* p_CharacterPlayerHuman, FStruct_AttackStateDefinition* p_AttackState);

protected:
	virtual void BeginPlay() override;
private:
	// Handle OnComponentBeginOverlap of m_SphereComponent_Collision
	UFUNCTION()
		void HanldeOnComponentBeginOverlap_SphereCollision(UPrimitiveComponent* p_OverlappedComponent, AActor* p_OtherActor, UPrimitiveComponent* p_OtherComp, int32 p_OtherBodyIndex, bool p_bFromSweep, const FHitResult& p_SweepResult);
};
