// Fill out your copyright notice in the Description page of Project Settings.
#include "Characters/MainCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GroomComponent.h"
#include "Items/Weapons/Weapon.h"
#include "Items/Item.h"
#include "Animation/AnimMontage.h"


AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCameraComponent"));
	CameraComponent->SetupAttachment(SpringArm);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair-> AttachmentName =	FString("head");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows-> AttachmentName = FString("head");
	bUseControllerRotationYaw = false;
	
	//get the player state
	

	
	
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for server
	InitAbilityActorInfo();
	
	
}
void AMainCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Init ability actor info for client
	InitAbilityActorInfo();
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController *PlayerController = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(MainCharacterImc, 0);
		}
	}

}


void AMainCharacter::Move(const FInputActionValue& Value)
{
	AMainCharacterPlayerState* MainCharacterPlayerState = GetPlayerState<AMainCharacterPlayerState>();
	if (MainCharacterPlayerState->GetActionState() == EActionState::EAS_Attacking)
		return;
	
	const FVector2D MovementVector = Value.Get<FVector2D>();

	
	if (!Controller || MovementVector.IsNearlyZero())
	{
		return;
	}

	
	const FRotator CameraRotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, CameraRotation.Yaw, 0);
	
	
	


	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	
	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
	
}

void AMainCharacter::Look(const FInputActionValue& Value)
{

	const FVector2D LookAxisVector = Value.Get<FVector2d>();
	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
	
}

void AMainCharacter::Dodge(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Dodge"));
}

void AMainCharacter::PlayAttackAnimation()
{
	
	
	TObjectPtr<UAnimInstance> AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage, 1.5f);
		
		const int32 Selection = FMath::RandRange(0, 1);
		FName SelectionName = FName();
		
		switch (Selection)
		{
		case 0:
			SelectionName = FName("Attack1");
			break;
		case 1:
			SelectionName = FName("Attack2");
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(SelectionName, AttackMontage);
		
	}
}

void AMainCharacter::AttackEnd()
{

	if (AMainCharacterPlayerState* MainCharacterPlayerState = GetPlayerState<AMainCharacterPlayerState>())
		MainCharacterPlayerState->SetActionState(EActionState::EAS_Unoccupied);
}

bool AMainCharacter::CanAttack()
{
	AMainCharacterPlayerState* MainCharacterPlayerState = GetPlayerState<AMainCharacterPlayerState>();
	return MainCharacterPlayerState->GetActionState() == EActionState::EAS_Unoccupied &&
		MainCharacterPlayerState->GetCharacterState() != ECharacterState::ECS_Unequipped;
}

void AMainCharacter::Attack(const FInputActionValue& Value)
{
	AMainCharacterPlayerState* MainCharacterPlayerState = GetPlayerState<AMainCharacterPlayerState>();
	
	if (CanAttack())
	{
		PlayAttackAnimation();
		MainCharacterPlayerState->SetActionState(EActionState::EAS_Attacking);
	}
		
	
}

void AMainCharacter::EKey(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("EKey"));
	AWeapon* Weapon = Cast<AWeapon>(OverlappingItem);
	if(Weapon)
	{
		Weapon->Equip(GetMesh(),FName("RightHandSocket"));
		if(AMainCharacterPlayerState* MainCharacterPs = GetPlayerState<AMainCharacterPlayerState>())
		{
			MainCharacterPs->SetCharacterState(ECharacterState::ECS_EquippedOneHandedWeapon);
		}
	}
}

void AMainCharacter::InitAbilityActorInfo()
{
	AMainCharacterPlayerState* MainCharacterPlayerState = GetPlayerState<AMainCharacterPlayerState>();
	check(MainCharacterPlayerState);

	AbilitySystemComponent = MainCharacterPlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(MainCharacterPlayerState, this);
	AttributeSet = MainCharacterPlayerState->GetAttributeSet();
}




void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent *MyInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		MyInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		MyInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
		MyInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &AMainCharacter::Jump);
		MyInputComponent->BindAction(DodgeInputAction, ETriggerEvent::Triggered, this, &AMainCharacter::Dodge);
		MyInputComponent->BindAction(AttackInputAction, ETriggerEvent::Triggered, this, &AMainCharacter::Attack);
		MyInputComponent->BindAction(EKeyInputAction, ETriggerEvent::Triggered, this, &AMainCharacter::EKey);
	}
}