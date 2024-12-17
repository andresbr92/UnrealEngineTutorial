// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig.h"

const UInputAction* UInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (FInputAction_LinkTo_GameplayTag FInputAction_LinkTo_GameplayTagElement: AbilityInputActions)
	{
		if (FInputAction_LinkTo_GameplayTagElement.InputAction && InputTag == FInputAction_LinkTo_GameplayTagElement.GameplayTag)
		{
			return FInputAction_LinkTo_GameplayTagElement.InputAction;
		} 
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
