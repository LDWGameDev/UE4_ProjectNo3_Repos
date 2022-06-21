// Fill out your copyright notice in the Description page of Project Settings.

#include "Character_PlayerHuman.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

#include "../StateMachine/Player/ContainerPlayerStates.h"
#include "../Library/Library_CustomMath.h"



/**
 * Override member Functions
 */

ACharacter_PlayerHuman::ACharacter_PlayerHuman()
{
	PrimaryActorTick.bCanEverTick = true;

	// Character defaults
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// CapsuleComponent defaults
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// CharacterMovementt defaults
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);
	GetCharacterMovement()->GravityScale = 2.5f;
	GetCharacterMovement()->MaxWalkSpeed = 350.0f;
	GetCharacterMovement()->bMaintainHorizontalGroundVelocity = false;
	GetCharacterMovement()->AirControl = 1.0f;

	// SpringArm component defaults
	m_SpringArm_Follow_01 = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm Follow 01"));
	m_SpringArm_Follow_01->SetupAttachment(RootComponent);
	m_SpringArm_Follow_01->TargetArmLength = c_DefaultArmLength_Follow_01;
	m_SpringArm_Follow_01->bUsePawnControlRotation = true;
	m_SpringArm_Follow_01->bEnableCameraLag = true;
	m_SpringArm_Follow_01->CameraLagSpeed = 18.0f;

	// Camera defaults
	m_Camera_Follow_01 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Follow 01"));
	m_Camera_Follow_01->SetupAttachment(m_SpringArm_Follow_01);
	
	// StateMachine
	m_StateMachine_01 = CreateDefaultSubobject<UStateMachineComponent>(TEXT("State Machine 01"));
	m_StateMachine_01->m_BackStateWhenError = TEXT("PlayerHumanState_UnarmedIdle");

	// ControlRig
	m_ControlRig_01 = CreateDefaultSubobject<UControlRigComponent>(TEXT("Control Rig 01"));
	m_ControlRig_01->SetupAttachment(GetMesh());
}

void ACharacter_PlayerHuman::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (m_Subclass_CameraSystemActor != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		m_CameraSystemActor = GetWorld()->SpawnActor<AActor_CameraSystem>(m_Subclass_CameraSystemActor, this->GetActorTransform(), SpawnParams);
	}
}

void ACharacter_PlayerHuman::BeginPlay()
{
	Super::BeginPlay();
	m_AnimInstance_PlayerHuman_REF = Cast<UAnimInstance_PlayerHuman>(GetMesh()->GetAnimInstance());
	InitStateMachine();
	InitTimelines();

	// Bind handling functions to delegates
	if (m_CameraSystemActor != nullptr)
	{
		(m_CameraSystemActor->m_Delegate_ReturnViewTarget).AddUObject(this, &ACharacter_PlayerHuman::HandleDelegate_ReturnViewTarget);
	}

	if (m_StateMachine_01 != nullptr)
	{
		(m_StateMachine_01->m_Delegate_ChangeState).AddUObject(this, &ACharacter_PlayerHuman::HandleDelegate_ChangeState);
	}
}

void ACharacter_PlayerHuman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateMovement();
	TimelineTicks(DeltaTime);
}

void ACharacter_PlayerHuman::PossessedBy(AController* NewController) 
{
	Super::PossessedBy(NewController);
	HandleOnPossessed(NewController);
}

void ACharacter_PlayerHuman::UnPossessed() 
{
	Super::UnPossessed();
	HandleOnUnPossessed();
}

void ACharacter_PlayerHuman::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	if (m_Delegate_Landed.IsBound()) 
	{
		m_Delegate_Landed.Broadcast();
	}
}

void ACharacter_PlayerHuman::Falling()
{
	Super::Falling();
	if (m_Delegate_StartFalling.IsBound())
	{
		m_Delegate_StartFalling.Broadcast();
	}
}





/**
 * Get, Set functions
 */

float ACharacter_PlayerHuman::GetMovingSpeed() { return m_MovingSpeed; }

UStateMachineComponent* ACharacter_PlayerHuman::GetStateMachine() { return m_StateMachine_01; }



/**
 * Public member functions
 */

void ACharacter_PlayerHuman::MoveCharacter(float p_MoveForwardValue, float p_MoveRightValue)
{
	FRotator ControllerRotator = GetControlRotation();
	ControllerRotator.Roll = 0.0f;
	ControllerRotator.Pitch = 0.0f;
	FVector ControllerForwardVector = UKismetMathLibrary::GetForwardVector(ControllerRotator);
	FVector ControllerRightVector = UKismetMathLibrary::GetRightVector(ControllerRotator);
	AddMovementInput(ControllerForwardVector * p_MoveForwardValue, 1.0f, false);
	AddMovementInput(ControllerRightVector * p_MoveRightValue, 1.0f, false);
}

void ACharacter_PlayerHuman::SetControlRigFootIKAlpha(float p_NewValue, float p_BlendTime)
{
	if (m_AnimInstance_PlayerHuman_REF == nullptr) return;
	float ClampedValue = FMath::Clamp(p_NewValue, 0.0f, 1.0f);
	m_SavedControlRigFootIKAlpha = m_AnimInstance_PlayerHuman_REF->m_ControlRigFootIKAlpha;
	m_NewValueControlRigFootIKAlpha = ClampedValue;
	if (p_BlendTime <= 0.0f) m_AnimInstance_PlayerHuman_REF->m_ControlRigFootIKAlpha = ClampedValue;
	else 
	{
		m_Timeline_ControlRigFootIK.SetPlayRate(1.0 / p_BlendTime);
		m_Timeline_ControlRigFootIK.PlayFromStart();
	}
}

void ACharacter_PlayerHuman::RotateToRotation(const FRotator& p_NewRotation, float p_BlendTime)
{
	if (p_BlendTime <= 0.0f)
	{
		SetActorRotation(p_NewRotation, ETeleportType::None);
	}
	else
	{
		m_SavedRotator = GetActorRotation();
		m_NewRotator = p_NewRotation;
		m_Timeline_Rotation.SetPlayRate(1.0f / p_BlendTime);
		m_Timeline_Rotation.PlayFromStart();
	}
}

void ACharacter_PlayerHuman::RotateToFaceTarget(const AActor* p_ActorToFace, float p_BlendTime)
{
	if (p_ActorToFace == nullptr) return;
	FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), p_ActorToFace->GetActorLocation());
	LookAtRotator.Pitch = 0.0f;
	LookAtRotator.Roll = 0.0f;
	RotateToRotation(LookAtRotator, p_BlendTime);
}

bool ACharacter_PlayerHuman::PlayMontageFromTable(const FName& p_MontageID)
{
	FStruct_MontageToPlay* MontageToPlay = m_DataTable_Montages->FindRow<FStruct_MontageToPlay>(p_MontageID, "");
	if (MontageToPlay == nullptr || MontageToPlay->m_AnimMontage == nullptr) return false;
	PlayAnimMontage(MontageToPlay->m_AnimMontage);
	return true;
}

void ACharacter_PlayerHuman::DisableRootMotionForTime(float p_DisableTime)
{
	if (m_AnimInstance_PlayerHuman_REF == nullptr) return;
	m_AnimInstance_PlayerHuman_REF->RootMotionMode = ERootMotionMode::IgnoreRootMotion;
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACharacter_PlayerHuman::EnableRootMotion, 1.0f, false, p_DisableTime);
}

void ACharacter_PlayerHuman::SetArmLength_CameraFollow_01(float p_AdditionalLengthToDefault, float p_BlendTime)
{
	float NewArmLength = c_DefaultArmLength_Follow_01 + p_AdditionalLengthToDefault;
	if (NewArmLength <= 10.0f || m_SpringArm_Follow_01 == nullptr) return;
	if (p_BlendTime <= 0.0f) m_SpringArm_Follow_01->TargetArmLength = NewArmLength;
	else
	{
		m_SavedSocketOffset_Follow_01 = m_SpringArm_Follow_01->SocketOffset;
		m_NewSocketOffset_Follow_01 = FVector::ZeroVector;
		m_SavedArmLength_Follow_01 = m_SpringArm_Follow_01->TargetArmLength;
		m_NewArmLength_Follow_01 = NewArmLength;
		m_Timeline_CameraFollow_01.SetPlayRate(1.0f / p_BlendTime);
		m_Timeline_CameraFollow_01.PlayFromStart();
	}
}

void ACharacter_PlayerHuman::SetCameraFollow_01(float p_AdditionalLengthToDefault, const FVector& p_SocketOffset, float p_BlendTime)
{
	float NewArmLength = c_DefaultArmLength_Follow_01 + p_AdditionalLengthToDefault;
	if (NewArmLength <= 10.0f || m_SpringArm_Follow_01 == nullptr) return;
	if (p_BlendTime <= 0.0f)
	{
		m_SpringArm_Follow_01->TargetArmLength = NewArmLength;
		m_SpringArm_Follow_01->SocketOffset = p_SocketOffset;
	}
	else
	{
		m_SavedSocketOffset_Follow_01 = m_SpringArm_Follow_01->SocketOffset;
		m_NewSocketOffset_Follow_01 = p_SocketOffset;
		m_SavedArmLength_Follow_01 = m_SpringArm_Follow_01->TargetArmLength;
		m_NewArmLength_Follow_01 = NewArmLength;
		m_Timeline_CameraFollow_01.SetPlayRate(1.0f / p_BlendTime);
		m_Timeline_CameraFollow_01.PlayFromStart();
	}
}

bool ACharacter_PlayerHuman::EquipWeapon(const FName& p_NewWeaponID)
{
	FStruct_Weapon* TempWeaponStruct = m_DataTable_Weapons->FindRow<FStruct_Weapon>(p_NewWeaponID, "");
	if (TempWeaponStruct == nullptr) return false;
	m_CurrentWeaponStruct = TempWeaponStruct;
	CreateHoldingWeapon();
	// Change to appropriate equip state
	switch (m_CurrentWeaponStruct->m_EnumWeaponType)
	{
	case EWeaponType::None:
	{
		return true;
	}
	case EWeaponType::AssassinSword:
	{
		m_StateMachine_01->ChangeState("PlayerHumanState_AssassinEquip");
		return true;
	}
	default:
		break;
	}
	return false;
}

void ACharacter_PlayerHuman::SetViewToCameraFollow_01(float p_BlendTime, EViewTargetBlendFunction p_BlendFunction, float p_BlendHardness, bool p_LockViewToTarget)
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	PlayerController->SetViewTargetWithBlend(this, p_BlendTime, p_BlendFunction, p_BlendHardness, p_LockViewToTarget);
}

void ACharacter_PlayerHuman::SetViewToCameraSequence(const FName& p_SequenceID, bool p_ResetCameraSystemTransform)
{
	if (m_CameraSystemActor == nullptr) return;
	if (p_ResetCameraSystemTransform)
	{
		FTransform CharacterTransform = this->GetActorTransform();
		m_CameraSystemActor->SetActorTransform(CharacterTransform);
	}
	m_CameraSystemActor->SetViewTargetToActorSequence(p_SequenceID, Cast<APlayerController>(Controller));
}







/**
 * Protected member functions
 */






/**
 * Private member functions
 */

void ACharacter_PlayerHuman::HandleTimeline_ControlRigFootIK_FloatProgress_01(float p_Value)
{
	m_AnimInstance_PlayerHuman_REF->m_ControlRigFootIKAlpha = FMath::Lerp(m_SavedControlRigFootIKAlpha, m_NewValueControlRigFootIKAlpha, p_Value);
}

void ACharacter_PlayerHuman::HandleTimeline_ControlRigFootIK_EndEvent()
{

}

void ACharacter_PlayerHuman::HandleTimeline_Rotation_FloatProgress_01(float p_Value)
{
	SetActorRotation(FMath::Lerp(m_SavedRotator, m_NewRotator, p_Value), ETeleportType::None);
}

void ACharacter_PlayerHuman::HandleTimeline_Rotation_EndEvent()
{

}

void ACharacter_PlayerHuman::HandleTimeline_CameraFollow_01_FloatProgress_01(float p_Value)
{
	m_SpringArm_Follow_01->TargetArmLength = FMath::Lerp(m_SavedArmLength_Follow_01, m_NewArmLength_Follow_01, p_Value);
	m_SpringArm_Follow_01->SocketOffset = FMath::Lerp(m_SavedSocketOffset_Follow_01, m_NewSocketOffset_Follow_01, p_Value);
}

void ACharacter_PlayerHuman::HandleTimeline_CameraFollow_01_EndEvent()
{

}

void ACharacter_PlayerHuman::HandleTimeline_WeaponBuff_01_FloatProgress_01(float p_Value)
{

}

void ACharacter_PlayerHuman::HandleTimeline_WeaponBuff_01_EndEvent()
{
	b_IsBuffingWeapon_01 = false;
	UE_LOG(LogTemp, Warning, TEXT("CharPlayerHuman - HandleTimelineEndEvent - BuffWeapon_01 Ended"));
}

void ACharacter_PlayerHuman::InitStateMachine()
{
	if (!m_StateMachine_01) return;
	auto* AvailableStatesList = m_StateMachine_01->GetAvailableStatesList();
	if (AvailableStatesList == nullptr) return;

	AvailableStatesList->Reserve(26);

	m_UnarmedIdleState = NewObject<UPlayerHumanState_UnarmedIdle>();
	m_UnarmedIdleState->InitState_PlayerHuman(this, m_StateMachine_01);
	m_UnarmedJogState = NewObject<UPlayerHumanState_UnarmedJog>();
	m_UnarmedJogState->InitState_PlayerHuman(this, m_StateMachine_01);
	m_UnarmedJumpState = NewObject<UPlayerHumanState_UnarmedJump>();
	m_UnarmedJumpState->InitState_PlayerHuman(this, m_StateMachine_01);
	m_UnarmedFallingState = NewObject<UPlayerHumanState_UnarmedFalling>();
	m_UnarmedFallingState->InitState_PlayerHuman(this, m_StateMachine_01);
	m_UnarmedDashState = NewObject<UPlayerHumanState_UnarmedDash>();
	m_UnarmedDashState->InitState_PlayerHuman(this, m_StateMachine_01);
	m_UnarmedRunState = NewObject<UPlayerHumanState_UnarmedRun>();
	m_UnarmedRunState->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinEquipState = NewObject<UPlayerHumanState_AssassinEquip>();
	m_AssassinEquipState->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinUnequipState = NewObject<UPlayerHumanState_AssassinUnequip>();
	m_AssassinUnequipState->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinIdleState = NewObject<UPlayerHumanState_AssassinIdle>();
	m_AssassinIdleState->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinJogState = NewObject<UPlayerHumanState_AssassinJog>();
	m_AssassinJogState->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinRunState = NewObject<UPlayerHumanState_AssassinRun>();
	m_AssassinRunState->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinDashState = NewObject<UPlayerHumanState_AssassinDash>();
	m_AssassinDashState->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinFallingState = NewObject<UPlayerHumanState_AssassinFalling>();
	m_AssassinFallingState->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinJumpState = NewObject<UPlayerHumanState_AssassinJump>();
	m_AssassinJumpState->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinDash_2_State = NewObject<UPlayerHumanState_AssassinDash_2>();
	m_AssassinDash_2_State->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinLightAttack_C1_1 = NewObject<UPlayerHumanState_AssassinLA_C1_1>();
	m_AssassinLightAttack_C1_1->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinLightAttack_C1_2 = NewObject<UPlayerHumanState_AssassinLA_C1_2>();
	m_AssassinLightAttack_C1_2->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinLightAttack_C1_3 = NewObject<UPlayerHumanState_AssassinLA_C1_3>();
	m_AssassinLightAttack_C1_3->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinHeavyAttack_C1_1 = NewObject<UPlayerHumanState_AssassinHA_C1_1>();
	m_AssassinHeavyAttack_C1_1->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinHeavyAttack_C1_2 = NewObject<UPlayerHumanState_AssassinHA_C1_2>();
	m_AssassinHeavyAttack_C1_2->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinHeavyAttack_C2_1 = NewObject<UPlayerHumanState_AssassinHA_C2_1>();
	m_AssassinHeavyAttack_C2_1->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinHeavyAttack_C2_2 = NewObject<UPlayerHumanState_AssassinHA_C2_2>();
	m_AssassinHeavyAttack_C2_2->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinHeavyAttack_C2_3 = NewObject<UPlayerHumanState_AssassinHA_C2_3>();
	m_AssassinHeavyAttack_C2_3->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinHeavyAttack_C2_4 = NewObject<UPlayerHumanState_AssassinHA_C2_4>();
	m_AssassinHeavyAttack_C2_4->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinHeavyAttack_C3_1 = NewObject<UPlayerHumanState_AssassinHA_C3_1>();
	m_AssassinHeavyAttack_C3_1->InitState_PlayerHuman(this, m_StateMachine_01);
	m_AssassinHeavyAttack_C3_2 = NewObject<UPlayerHumanState_AssassinHA_C3_2>();
	m_AssassinHeavyAttack_C3_2->InitState_PlayerHuman(this, m_StateMachine_01);

	AvailableStatesList->Add(m_UnarmedIdleState);
	AvailableStatesList->Add(m_UnarmedJogState);
	AvailableStatesList->Add(m_UnarmedJumpState);
	AvailableStatesList->Add(m_UnarmedFallingState);
	AvailableStatesList->Add(m_UnarmedDashState);
	AvailableStatesList->Add(m_UnarmedRunState);
	AvailableStatesList->Add(m_AssassinEquipState);
	AvailableStatesList->Add(m_AssassinUnequipState);
	AvailableStatesList->Add(m_AssassinIdleState);
	AvailableStatesList->Add(m_AssassinJogState);
	AvailableStatesList->Add(m_AssassinRunState);
	AvailableStatesList->Add(m_AssassinDashState);
	AvailableStatesList->Add(m_AssassinFallingState);
	AvailableStatesList->Add(m_AssassinJumpState);
	AvailableStatesList->Add(m_AssassinDash_2_State);
	AvailableStatesList->Add(m_AssassinLightAttack_C1_1);
	AvailableStatesList->Add(m_AssassinLightAttack_C1_2);
	AvailableStatesList->Add(m_AssassinLightAttack_C1_3);
	AvailableStatesList->Add(m_AssassinHeavyAttack_C1_1);
	AvailableStatesList->Add(m_AssassinHeavyAttack_C1_2);
	AvailableStatesList->Add(m_AssassinHeavyAttack_C2_1);
	AvailableStatesList->Add(m_AssassinHeavyAttack_C2_2);
	AvailableStatesList->Add(m_AssassinHeavyAttack_C2_3);
	AvailableStatesList->Add(m_AssassinHeavyAttack_C2_4);
	AvailableStatesList->Add(m_AssassinHeavyAttack_C3_1);
	AvailableStatesList->Add(m_AssassinHeavyAttack_C3_2);
}

void ACharacter_PlayerHuman::HandleOnPossessed(AController* p_Controller)
{
	// Called DelayHandleOnPossessed()
	FTimerHandle TimerHandle01;
	GetWorldTimerManager().SetTimer(TimerHandle01, this, &ACharacter_PlayerHuman::DelayHandleOnPossessed, 1.0f, false, 0.5f);

	// Bind handling functions of this character to delegates of PlayerController
	if (Controller != nullptr)
	{
		IInterface_PlayerControllerInput* IPlayerInput = Cast<IInterface_PlayerControllerInput>(Controller);
		if (IPlayerInput != nullptr)
		{
			m_BuffWeapon_01_DelegateREF = IPlayerInput->GetDelegate_BuffWeapon_01();
			if (m_BuffWeapon_01_DelegateREF != nullptr) m_BuffWeapon_01_DelegateREF->AddUObject(this, &ACharacter_PlayerHuman::HandleDelegate_BuffWeapon_01);
		}
	}
}

void ACharacter_PlayerHuman::HandleOnUnPossessed()
{
	// Controller is null now so we can't unbind using direct reference to delegate of Controller and have to store delegate in pointer.
	if (m_StateMachine_01 == nullptr) return;

	// Unbind handling functions to delegate of PlayerController
	if (m_BuffWeapon_01_DelegateREF != nullptr) m_BuffWeapon_01_DelegateREF->RemoveAll(this);
	m_BuffWeapon_01_DelegateREF = nullptr;

	// Deactivate m_StateMachine
	m_StateMachine_01->DeactivateStateMachine();

	// Unbind handling functions in each state
	auto* StatesList = m_StateMachine_01->GetAvailableStatesList();
	if (StatesList != nullptr)
	{
		for (UBaseState* State : *StatesList)
		{
			UPlayerHuman_BaseState* PlayerHumanState = Cast<UPlayerHuman_BaseState>(State);
			if (PlayerHumanState != nullptr)
			{
				PlayerHumanState->UnBindInputHandlingFunctions();
			}
		}
	}
}

void ACharacter_PlayerHuman::DelayHandleOnPossessed()
{
	if (m_StateMachine_01 != nullptr)
	{
		// Activate m_StateMachine
		m_StateMachine_01->ActivateStateMachine(TEXT("PlayerHumanState_UnarmedIdle"));

		// Bind handling functions of states to delegate of PlayerController
		auto* StatesList = m_StateMachine_01->GetAvailableStatesList();
		if (StatesList != nullptr)
		{
			for (UBaseState* State : *StatesList)
			{
				UPlayerHuman_BaseState* PlayerHumanState = Cast<UPlayerHuman_BaseState>(State);
				if (PlayerHumanState != nullptr) PlayerHumanState->BindInputHandlingFunctions(Controller);
			}
		}
	}
}

void ACharacter_PlayerHuman::CalculateMovement() 
{
	m_MovingSpeed = GetVelocity().Size();
}

void ACharacter_PlayerHuman::InitTimelines()
{
	if (m_CurveFloat_EaseInOutAlpha == nullptr || m_CurveFloat_LinearAlpha == nullptr) return;
	
	// Create timeline handles ControlRigFootIKAlpha
	FOnTimelineFloat OnTimelineControlRig_FloatProgress;
	FOnTimelineEvent OnTimelineControlRig_EndEvent;
	OnTimelineControlRig_FloatProgress.BindUFunction(this, FName(TEXT("HandleTimeline_ControlRigFootIK_FloatProgress_01")));
	OnTimelineControlRig_EndEvent.BindUFunction(this, FName(TEXT("HandleTimeline_ControlRigFootIK_EndEvent")));
	m_Timeline_ControlRigFootIK.AddInterpFloat(m_CurveFloat_EaseInOutAlpha, OnTimelineControlRig_FloatProgress);
	m_Timeline_ControlRigFootIK.SetTimelineFinishedFunc(OnTimelineControlRig_EndEvent);
	m_Timeline_ControlRigFootIK.SetTimelineLength(1.0f);
	m_Timeline_ControlRigFootIK.SetLooping(false);

	// Create timeline handles this character's rotation
	FOnTimelineFloat OnTimelineFloat_Rotation_Progress_01;
	FOnTimelineEvent OnTimelineEvent_Rotation_EndEvent;
	OnTimelineFloat_Rotation_Progress_01.BindUFunction(this, FName(TEXT("HandleTimeline_Rotation_FloatProgress_01")));
	OnTimelineEvent_Rotation_EndEvent.BindUFunction(this, FName(TEXT("HandleTimeline_Rotation_EndEvent")));
	m_Timeline_Rotation.AddInterpFloat(m_CurveFloat_EaseInOutAlpha, OnTimelineFloat_Rotation_Progress_01);
	m_Timeline_Rotation.SetTimelineFinishedFunc(OnTimelineEvent_Rotation_EndEvent);
	m_Timeline_Rotation.SetTimelineLength(1.0f);
	m_Timeline_Rotation.SetLooping(false);

	// Create timeline handles camera group 01 (m_Camera_Follow_01 + m_SpringArm_Follow_01)
	FOnTimelineFloat OnTimelineFloat_CameraFollow_01_Progress_01;
	FOnTimelineEvent OnTimelineEvent_CameraFollow_01_EndEvent;
	OnTimelineFloat_CameraFollow_01_Progress_01.BindUFunction(this, FName(TEXT("HandleTimeline_CameraFollow_01_FloatProgress_01")));
	OnTimelineEvent_CameraFollow_01_EndEvent.BindUFunction(this, FName(TEXT("HandleTimeline_CameraFollow_01_EndEvent")));
	m_Timeline_CameraFollow_01.AddInterpFloat(m_CurveFloat_EaseInOutAlpha, OnTimelineFloat_CameraFollow_01_Progress_01);
	m_Timeline_CameraFollow_01.SetTimelineFinishedFunc(OnTimelineEvent_CameraFollow_01_EndEvent);
	m_Timeline_CameraFollow_01.SetTimelineLength(1.0f);
	m_Timeline_CameraFollow_01.SetLooping(false);

	// Create timeline handles weapon buff effect 01
	FOnTimelineFloat OnTimelineFloat_WeaponBuff_01_Progress_01;
	FOnTimelineEvent OnTimelineEvent_WeaponBuff_01_EndEvent;
	OnTimelineFloat_WeaponBuff_01_Progress_01.BindUFunction(this, FName(TEXT("HandleTimeline_WeaponBuff_01_FloatProgress_01")));
	OnTimelineEvent_WeaponBuff_01_EndEvent.BindUFunction(this, FName(TEXT("HandleTimeline_WeaponBuff_01_EndEvent")));
	m_Timeline_WeaponBuff_01.AddInterpFloat(m_CurveFloat_LinearAlpha, OnTimelineFloat_WeaponBuff_01_Progress_01);
	m_Timeline_WeaponBuff_01.SetTimelineFinishedFunc(OnTimelineEvent_WeaponBuff_01_EndEvent);
	m_Timeline_WeaponBuff_01.SetTimelineLength(1.0f);
	m_Timeline_WeaponBuff_01.SetLooping(false);


}

void ACharacter_PlayerHuman::TimelineTicks(float p_DeltaTime)
{
	m_Timeline_ControlRigFootIK.TickTimeline(p_DeltaTime);
	m_Timeline_Rotation.TickTimeline(p_DeltaTime);
	m_Timeline_CameraFollow_01.TickTimeline(p_DeltaTime);
	m_Timeline_WeaponBuff_01.TickTimeline(p_DeltaTime);
}

void ACharacter_PlayerHuman::EnableRootMotion()
{
	m_AnimInstance_PlayerHuman_REF->RootMotionMode = ERootMotionMode::RootMotionFromEverything;
}

void ACharacter_PlayerHuman::CreateHoldingWeapon()
{
	USkeletalMeshComponent* CurrentMesh = GetMesh();
	if (CurrentMesh == nullptr || m_CurrentWeaponStruct == nullptr || !(CurrentMesh->DoesSocketExist(m_CurrentWeaponStruct->m_AttachingSocketName))
		|| !m_CurrentWeaponStruct->CheckValid()) return;

	AActor_HoldingWeapon* NewHoldingWeapon = GetWorld()->SpawnActor<AActor_HoldingWeapon>(m_CurrentWeaponStruct->m_HoldingWeapon);
	NewHoldingWeapon->AttachToComponent(CurrentMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, m_CurrentWeaponStruct->m_AttachingSocketName);

	if (m_CurrentHoldingWeapon != nullptr) m_CurrentHoldingWeapon->Destroy();
	m_CurrentHoldingWeapon = NewHoldingWeapon;
}

void ACharacter_PlayerHuman::HandleDelegate_ChangeState()
{
	if (m_AnimInstance_PlayerHuman_REF != nullptr) m_AnimInstance_PlayerHuman_REF->CheckForCurrentState();
}

void ACharacter_PlayerHuman::HandleDelegate_BuffWeapon_01()
{
	float BuffTime = c_BuffWeapon_01_BuffTime;
	b_IsBuffingWeapon_01 = true;
	m_SavedTimeValue_WeaponBuff_01 = BuffTime;
	m_Timeline_WeaponBuff_01.SetPlayRate(1.0f / BuffTime);
	m_Timeline_WeaponBuff_01.PlayFromStart();

	UE_LOG(LogTemp, Warning, TEXT("CharPlayerHuman - HandleDelegate_BuffWeapon - BuffWeapon_01 Started"));
}

void ACharacter_PlayerHuman::HandleDelegate_ReturnViewTarget()
{
	if (m_SpringArm_Follow_01 == nullptr) return;
	FRotator CurrentTargetRotation = m_SpringArm_Follow_01->GetTargetRotation();
	float YawValue = (c_SpringArm_DefaultTargetRotation.Yaw - CurrentTargetRotation.Yaw) / 2.5f;
	float PitchValue = (c_SpringArm_DefaultTargetRotation.Pitch - CurrentTargetRotation.Pitch) / 2.5f;
	this->AddControllerYawInput(YawValue);
	this->AddControllerPitchInput(PitchValue * -1.0f);

	m_SpringArm_Follow_01->TargetArmLength = c_DefaultArmLength_Follow_01 + 120.0f;
	m_SpringArm_Follow_01->SocketOffset = FVector(0.0f, -100.0f, 0.0f);

	SetArmLength_CameraFollow_01(0.0f, 2.0f);
	SetViewToCameraFollow_01(0.0f);
}









void ACharacter_PlayerHuman::TestFunction(FName p_ActorSequenceID)
{

}