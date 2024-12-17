// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseMainAbilitySystemComponent.h"
#include "MainGameplayTags.h"
#include "AbilitySystem/Abilities/GameplayAbilityBase.h"

void UBaseMainAbilitySystemComponent::AbilityActorInfoSet()
{
	// Bind function to the OnGameplayEffectAppliedDelegateToSelf delegate
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UBaseMainAbilitySystemComponent::BindedFunction);
	FMainGameplayTags MainGameplayTags = FMainGameplayTags::Get();
	// Other way to get gameplay tags
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Blue, FString::Printf(TEXT("tag: %s"), *MainGameplayTags.Attributes_Secondary_Armor.ToString()));		
	}
	
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
		// Remember that FGameplayAbilitySpec is a struct that holds the ability and the level of the ability
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		
		UGameplayAbilityBase* AbilityBase = Cast<UGameplayAbilityBase>(AbilitySpec.Ability);
		if(AbilityBase)
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityBase->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UBaseMainAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Blue, FString::Printf(TEXT("Held") ));	
	for (FGameplayAbilitySpec& AbilitySpec: GetActivatableAbilities())
	{
		
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
			
		}
	}
	
}

void UBaseMainAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Blue, FString::Printf(TEXT("Held") ));	
	for (FGameplayAbilitySpec& AbilitySpec: GetActivatableAbilities())
	{
		
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
	
}



