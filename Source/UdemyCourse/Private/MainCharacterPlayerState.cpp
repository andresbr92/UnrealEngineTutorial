// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterPlayerState.h"

#include "AbilitySystem/BaseMainAbilitySystemComponent.h"
#include "AbilitySystem/BaseMainAttributeSet.h"

AMainCharacterPlayerState::AMainCharacterPlayerState()
{
	NetUpdateFrequency = 2.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UBaseMainAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AttributeSet = CreateDefaultSubobject<UBaseMainAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AMainCharacterPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMainCharacterPlayerState::SetCharacterState(ECharacterState newState) {  CharacterState = newState; }

void AMainCharacterPlayerState::SetActionState(EActionState newState)
{
	ActionState = newState;
}
