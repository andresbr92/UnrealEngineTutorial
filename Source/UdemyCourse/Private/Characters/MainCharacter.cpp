// Fill out your copyright notice in the Description page of Project Settings.
#include "Characters/MainCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GroomComponent.h"


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

void AMainCharacter::Attack(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Attack"));
	
}

void AMainCharacter::EKey(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("EKey"));
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