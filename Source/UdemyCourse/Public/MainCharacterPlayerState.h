// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "Characters/CharacterTypes.h"
#include "MainCharacterPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * @enum ECharacterState
 * @brief Defines the different states of a character.
 *
 * This enumeration is used to represent the possible states a character can be in,
 * primarily focusing on their equipment status.
 */

UCLASS()
class UDEMYCOURSE_API AMainCharacterPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	
	AMainCharacterPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	
	FORCEINLINE void SetCharacterState(ECharacterState newState);
	
	ECharacterState GetCharacterState() const { return CharacterState; }

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
private:
	UPROPERTY(EditAnywhere, Category = "Character State")
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
};
