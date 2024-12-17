// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MainAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class UDEMYCOURSE_API UMainAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UMainAssetManager& Get();
private:
	static UMainAssetManager AssetManager;
protected:
	virtual void StartInitialLoading() override;
	
};
