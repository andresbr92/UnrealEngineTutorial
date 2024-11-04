// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"


class USphereComponent;

UCLASS()
class UDEMYCOURSE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AItem();
	virtual void Tick(float DeltaTime) override;
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sine parameters")
	float Amplitude = 0.25f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Sine parameters")
	float RunningTime;

	UFUNCTION(BlueprintPure)
	float TransformedSin();

	UFUNCTION(BlueprintPure)
	float TransformedCos();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ItemMesh;

	template <typename T>
	T Average(T firstParameter, T secondParameter);
	
	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float TimeConstant = 5.f;



	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereCollider;
	
	

};

template<typename T>
inline T AItem::Average(T firstParameter, T secondParameter)
{
	return (firstParameter + secondParameter) / 2;
}
