// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "Characters/CharacterTypes.h"
#include "MainCharacterPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;



UCLASS()
class UDEMYCOURSE_API AMainCharacterPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	
	AMainCharacterPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	


protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
private:
	UPROPERTY(EditAnywhere, Category = "Character State")
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category = "Character State")
	EActionState ActionState = EActionState::EAS_Unoccupied;
	/*
	 * getters & setters
	 */
public:
	// Character State
	void SetCharacterState(ECharacterState newState);
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	
	// Combat state
	void SetActionState(EActionState newState);
	FORCEINLINE EActionState GetActionState() const { return ActionState; }
	
};
