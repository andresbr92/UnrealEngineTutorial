// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Fly.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
//#include "Components/InputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

//#include "InputAction.h"
// Sets default values
AFly::AFly()
{
 
	PrimaryActorTick.bCanEverTick = true;
	// CAPSULE COMPONENT
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	
	Capsule->SetCapsuleHalfHeight(20.f);
	Capsule->SetCapsuleRadius(15.f);
	SetRootComponent(Capsule);

	// SKELETAL COMPONENT
	FlyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletonComponent"));
	FlyMesh->SetupAttachment(GetRootComponent()); // That way, if the root component moves, our bird mesh will move along with it.

	//MOVEMENT COMPONENT
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	// SPRING COMPONENT
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetRootComponent());

	// CAMERA COMPONENT
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;



	AutoPossessPlayer = EAutoReceiveInput::Player0;

}


void AFly::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(FlyMappingContext, 0);
		}
	}
	
	
}

void AFly::MoveForward(float Value)
{
}

void AFly::Move(const FInputActionValue& Value)
{
	const float DirectionValue = Value.Get<float>();
	if (Controller && (DirectionValue != 0.f))
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, DirectionValue);
	}
	
	
}

void AFly::Look(const FInputActionValue& Value)
{
	const FVector2D LookDirectionAxis = Value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(LookDirectionAxis.X);
		AddControllerPitchInput(LookDirectionAxis.Y);
	}
}


void AFly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFly::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* MyInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		MyInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFly::Move);
		MyInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFly::Look);

	}

}

