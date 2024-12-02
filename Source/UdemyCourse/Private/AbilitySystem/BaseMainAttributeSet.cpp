// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseMainAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UBaseMainAttributeSet::UBaseMainAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(100.f);
	InitMaxMana(100.f);
	InitStamina(100.f);
	InitMaxStamina(100.f);
}

void UBaseMainAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseMainAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseMainAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseMainAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseMainAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseMainAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseMainAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void UBaseMainAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		// clamp health
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}
void UBaseMainAttributeSet::SetEffectPropperties(const FGameplayEffectModCallbackData& Data,
	FEffectProperties& EffectProperties)
{
	// [Source] is the cause of the effect, [target] is the receiver of the effect
	// SOURCE
	EffectProperties.SourceEffectContextHandle = Data.EffectSpec.GetContext();
	 EffectProperties.SourceASC = EffectProperties.SourceEffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	// Extraer el Avatar del asc. Primero checkeamos que el Source tenga un ASC, un actor info y un avatar.
	
	if (IsValid(EffectProperties.SourceASC) && EffectProperties.SourceASC->AbilityActorInfo.IsValid() && EffectProperties.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{

		
		EffectProperties.SourceAvatarActor = EffectProperties.SourceASC->AbilityActorInfo->AvatarActor.Get();
		EffectProperties.SourceController = EffectProperties.SourceASC->AbilityActorInfo->PlayerController.Get();
		// El controller puede ser null
		if (EffectProperties.SourceController == nullptr && EffectProperties.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(EffectProperties.SourceAvatarActor))
			{
				EffectProperties.SourceController = Pawn->GetController();
			}
			
		}
		if (EffectProperties.SourceController)
		{
			const ACharacter* SourceCharacter = Cast<ACharacter>(EffectProperties.SourceController);
		}
		
	}
	if (Data.Target.AbilityActorInfo.IsValid() &&  Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		EffectProperties.TargetCharacter = Cast<ACharacter>(EffectProperties.TargetAvatarActor);
		EffectProperties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProperties.TargetAvatarActor);
		
	}
}


void UBaseMainAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties EffectProperties;
	SetEffectPropperties(Data, EffectProperties);
	
}

void UBaseMainAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseMainAttributeSet, Health, OldHealth);
}

void UBaseMainAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseMainAttributeSet, MaxHealth, OldMaxHealth)
}
void UBaseMainAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseMainAttributeSet, Mana, OldMana);
}

void UBaseMainAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseMainAttributeSet, MaxMana, OldMaxMana);
}

void UBaseMainAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseMainAttributeSet, Stamina, OldStamina);
}

void UBaseMainAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseMainAttributeSet, MaxStamina, OldMaxStamina);
}





