// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterTypes.h"
#include "MainCharacterAnimInstance.generated.h"


/**
 * 
 */
UCLASS()
class UDEMYCOURSE_API UMainCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	
	// Event Blueprint Initialize animation analog
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadOnly)
	class AMainCharacter* MainCharacter;
	
	UPROPERTY(BlueprintReadOnly, Category=Movement)
	class UCharacterMovementComponent* MainCharacterMovementComponent;
	
	UPROPERTY(BlueprintReadOnly, Category=Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category=Movement)
	bool isFalling;
	
	UPROPERTY(BlueprintReadOnly, Category=State);
	ECharacterState CharacterState;
};
		