// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_StringID.h"
#include "Interface_AnimNotifyControl.h"



/**
 * Override functions
 */

void UAnimNotify_StringID::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp == nullptr || MeshComp->GetAnimInstance() == nullptr) return;
	IInterface_AnimNotifyControl* IAnimNotifyControl = Cast<IInterface_AnimNotifyControl>(MeshComp->GetAnimInstance());
	if (IAnimNotifyControl != nullptr)
	{
		IAnimNotifyControl->HandleAnimNotify_StringID(m_StringID);
	}
}

