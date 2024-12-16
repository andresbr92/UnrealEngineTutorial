// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseMainAbilitySystemComponent.h"

void UBaseMainAbilitySystemComponent::AbilityActorInfoSet()
{
	// Bind function to the OnGameplayEffectAppliedDelegateToSelf delegate
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UBaseMainAbilitySystemComponent::BindedFunction);
}

void UBaseMainAbilitySystemComponent::BindedFunction(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle Handle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	OnEffectAssetTags.Broadcast(TagContainer);
	for (FGameplayTag Tag : TagContainer)
	{
		const FString Msg = FString::Printf(TEXT("Tag: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Msg);
	}
}

void UBaseMainAbilitySystemComponent::AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>> StartupAbilities)
{
	for (TSubclassOf<UGameplayAbility> Ability: StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}


