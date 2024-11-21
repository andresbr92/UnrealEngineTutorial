// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainCharacterAnimInstance.h"
#include "Characters/MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
	if(MainCharacter)
	{
		 MainCharacterMovementComponent = MainCharacter->GetCharacterMovement();
		printf("MainCharacterMovementComponent %p\n", MainCharacterMovementComponent);
		
	}
}

void UMainCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if(MainCharacterMovementComponent)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(MainCharacterMovementComponent->Velocity);

		isFalling = MainCharacterMovementComponent->IsFalling();
		if (AMainCharacterPlayerState* MainCharacterPs = MainCharacter->GetPlayerState<AMainCharacterPlayerState>())
		{
			CharacterState = MainCharacterPs->GetCharacterState();
		}
		
	}
}
