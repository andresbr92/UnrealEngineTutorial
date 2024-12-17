// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputConfig.h"
#include "MainInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class UDEMYCOURSE_API UMainInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(UInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UMainInputComponent::BindAbilityActions(UInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc,
	ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig)
	for (const auto AbilityWithTag: InputConfig->AbilityInputActions)
	{
		if (AbilityWithTag.InputAction && AbilityWithTag.GameplayTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(AbilityWithTag.InputAction, ETriggerEvent::Started, Object, PressedFunc, AbilityWithTag.GameplayTag);
			}
			if (ReleasedFunc)
			{
				BindAction(AbilityWithTag.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, AbilityWithTag.GameplayTag);
			}
			if (HeldFunc)
			{
				BindAction(AbilityWithTag.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, AbilityWithTag.GameplayTag);
			}
		}
	}
}
