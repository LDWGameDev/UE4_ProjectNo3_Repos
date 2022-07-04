// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_GameplayTagContainer.h"
#include "Interface_AnimNotifyControl.h"


void UAnimNotify_GameplayTagContainer::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp == nullptr || MeshComp->GetAnimInstance() == nullptr) return;
	IInterface_AnimNotifyControl* IAnimNotifyControl = Cast<IInterface_AnimNotifyControl>(MeshComp->GetAnimInstance());
	if (IAnimNotifyControl != nullptr && m_TagContainer.IsValid())
	{
		IAnimNotifyControl->HandleAnimNotify_GameplayTagContainer(m_TagContainer);
	}
}
