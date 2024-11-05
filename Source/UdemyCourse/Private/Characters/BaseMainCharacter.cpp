// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseMainCharacter.h"

// Sets default values
ABaseMainCharacter::ABaseMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* ABaseMainCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ABaseMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

