// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *  Singleton containing native GamplayTags
 */
struct FMainGameplayTags
{
public:
	static const FMainGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
	
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
protected:
private:
	static FMainGameplayTags GameplayTags;
};
