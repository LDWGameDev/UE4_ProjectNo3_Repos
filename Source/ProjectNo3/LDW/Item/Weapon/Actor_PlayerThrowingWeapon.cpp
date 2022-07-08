// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_PlayerThrowingWeapon.h"
#include "System/CombatSystem/Interface_Attackable.h"
#include "StateMachine/Player/PlayerHuman/PlayerHumanState_AssassinHA_C3_1.h"
#include "Kismet/GameplayStatics.h"


/**
 * 
 */

AActor_PlayerThrowingWeapon::AActor_PlayerThrowingWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	m_SphereComponent_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent Collision"));
	SetRootComponent(m_SphereComponent_Collision);

	m_StaticMesh_Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh Weapon"));
	m_StaticMesh_Weapon->SetupAttachment(RootComponent);

	m_ProjectileMovement_01 = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement 01"));
}



/**
 * Override functions
 */

void AActor_PlayerThrowingWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	m_SphereComponent_Collision->OnComponentBeginOverlap.AddDynamic(this, &AActor_PlayerThrowingWeapon::HanldeOnComponentBeginOverlap_SphereCollision);
}

void AActor_PlayerThrowingWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AActor_PlayerThrowingWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}





/**
 * Public member functions
 */

void AActor_PlayerThrowingWeapon::SetReferenceValues(ACharacter_PlayerHuman* p_CharacterPlayerHuman, FStruct_AttackStateDefinition* p_AttackState)
{
	m_CharacterPlayerHumanREF = p_CharacterPlayerHuman;
	m_AttackStateREF = p_AttackState;
}






/**
 * Private member functions
 */

void AActor_PlayerThrowingWeapon::HanldeOnComponentBeginOverlap_SphereCollision(UPrimitiveComponent* p_OverlappedComponent, AActor* p_OtherActor, UPrimitiveComponent* p_OtherComp, int32 p_OtherBodyIndex, bool p_bFromSweep, const FHitResult& p_SweepResult)
{
	if (m_ProjectileMovement_01 == nullptr || !p_OtherActor->ActorHasTag(FName(TEXT("ThrowingWeaponTarget")))) return;
	IInterface_Attackable* IAttackable = Cast<IInterface_Attackable>(p_OtherActor);
	if (IAttackable != nullptr)
	{
		if (m_CharacterPlayerHumanREF != nullptr) m_CharacterPlayerHumanREF->m_AssassinHeavyAttack_C3_1->m_GotHitActor = p_OtherActor;
		FStruct_AttackDefinition AttackDefinition = FStruct_AttackDefinition(m_CharacterPlayerHumanREF, p_OtherActor, m_AttackStateREF, &FHitResult());
		IAttackable->TakeHit(AttackDefinition);
	}
	if (m_NiagaraSystem_HitFire != nullptr)
	{
		UNiagaraComponent* NiaComponent_HitFire = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, m_NiagaraSystem_HitFire, GetActorLocation());
	}
	if (m_SoundBase_Explosion != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, m_SoundBase_Explosion, GetActorLocation());
	}

	m_ProjectileMovement_01->ProjectileGravityScale = 0.0f;
	m_ProjectileMovement_01->StopMovementImmediately();
	
	FTimerHandle TimerHandle_DelayDestroy;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelayDestroy, [&]()
		{
			Destroy();
		}, 0.1f, false);
}
