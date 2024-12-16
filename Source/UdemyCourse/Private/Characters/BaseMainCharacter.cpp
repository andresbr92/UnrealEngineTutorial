// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseMainCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/BaseMainAbilitySystemComponent.h"

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

void ABaseMainCharacter::InitAbilityActorInfo()
{
}

void ABaseMainCharacter::InitializeAttributes()
{
	if (!IsValid(AbilitySystemComponent)) return;
	if (!IsValid(DefaultAttributes))
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
	}
	
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	// Add source
	EffectContext.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1.f, EffectContext);
	if (EffectSpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}

void ABaseMainCharacter::AddCharacterAbilities()
{
	if (!HasAuthority() || !IsValid(AbilitySystemComponent)) return;
	UBaseMainAbilitySystemComponent* BaseMainAbilitySystemComponent = CastChecked<UBaseMainAbilitySystemComponent>(AbilitySystemComponent);
	BaseMainAbilitySystemComponent->AddCharacterAbilities(StartupAbilities);
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

