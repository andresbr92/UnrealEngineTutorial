// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMainCharacter.h"
#include "InputActionValue.h"
#include "MainCharacterPlayerState.h"
#include "MainCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class UEnhancedInputComponent;
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class UAnimMontage;



UCLASS()
class UDEMYCOURSE_API AMainCharacter : public ABaseMainCharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
	
	
	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext *MainCharacterImc;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction *MoveInputAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction *LookInputAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction *JumpInputAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction *DodgeInputAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction *EKeyInputAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction *AttackInputAction;


	void Move(const FInputActionValue &Value);
	void Look(const FInputActionValue &Value);
	void Dodge(const FInputActionValue &Value);
	void Attack(const FInputActionValue &Value);
	void EKey(const FInputActionValue &Value);

	

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent *SpringArm;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent *CameraComponent;
	
	UPROPERTY(VisibleAnywhere, Category=Hair)
	UGroomComponent *Hair;
	
	UPROPERTY(VisibleAnywhere, Category=Hair)
	UGroomComponent *Eyebrows;
	
	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<AItem> OverlappingItem;
	/*
	* Animation montages
	*/
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	TObjectPtr<UAnimMontage> AttackMontage;

	void InitAbilityActorInfo();
	

	
	// getters y setters
public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	
	
};
