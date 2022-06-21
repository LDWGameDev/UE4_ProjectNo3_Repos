// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_HoldingWeapon.h"

AActor_HoldingWeapon::AActor_HoldingWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	m_SceneRootComponent = CreateDefaultSubobject<USceneComponent>("Root Scene Component");
	SetRootComponent(m_SceneRootComponent);
	m_StaticMesh_Weapon = CreateDefaultSubobject<UStaticMeshComponent>("Weapon StaticMesh");
	m_StaticMesh_Weapon->SetupAttachment(m_SceneRootComponent);
}

void AActor_HoldingWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AActor_HoldingWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

