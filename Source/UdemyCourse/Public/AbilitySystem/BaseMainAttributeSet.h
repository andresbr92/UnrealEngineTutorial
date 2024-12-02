// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseMainAttributeSet.generated.h"
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties() {}
	// Source
	FGameplayEffectContextHandle SourceEffectContextHandle;
	UPROPERTY()
	UAbilitySystemComponent * SourceASC = nullptr;
	UPROPERTY()
	AActor * SourceAvatarActor = nullptr;
	UPROPERTY()
	AController * SourceController = nullptr;
	UPROPERTY()
	ACharacter * SourceCharacter = nullptr;
	// Target
	FGameplayEffectContextHandle TargetEffectContextHandle;
	UPROPERTY()
	UAbilitySystemComponent * TargetASC = nullptr;
	UPROPERTY()
	AActor * TargetAvatarActor = nullptr;
	UPROPERTY()
	AController * TargetController = nullptr;
	UPROPERTY()
	ACharacter * TargetCharacter = nullptr;
};
UCLASS()
class UDEMYCOURSE_API UBaseMainAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	
	UBaseMainAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category= "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBaseMainAttributeSet, Health)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category= "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBaseMainAttributeSet, MaxHealth)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Mana, Category= "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UBaseMainAttributeSet, Mana)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxMana, Category= "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UBaseMainAttributeSet, MaxMana)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Stamina, Category= "Vital Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UBaseMainAttributeSet, Stamina)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxStamina, Category= "Vital Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UBaseMainAttributeSet, MaxStamina)
	
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;
	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;
private:
	void SetEffectPropperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProperties);
};
