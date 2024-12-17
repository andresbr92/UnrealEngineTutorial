// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputConfig.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FInputAction_LinkTo_GameplayTag
{
	GENERATED_BODY()

	
	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag GameplayTag = FGameplayTag();
	
};

UCLASS()
class UDEMYCOURSE_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FInputAction_LinkTo_GameplayTag> AbilityInputActions;
	
};
