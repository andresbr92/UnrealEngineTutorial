// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"

#include "Characters/MainCharacter.h"
#include "Components/SphereComponent.h"




// Sets default values
AItem::AItem()
{
 
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereCollider->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	
	// Bind function
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereBeginOverlap);
	SphereCollider->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
	
	



	

	

	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Cyan, FString("item from c++ class"));
	}
	UWorld* World = GetWorld();
	if (World)
	{
		
	}
	

}

float AItem::TransformedSin()
{
	
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformedCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}

void AItem::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
	{
		
		MainCharacter->SetOverlappingItem(this);
		
	}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
	{
		MainCharacter->SetOverlappingItem(nullptr);
		
	}
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;


	//AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin(RunningTime)));
	//AddActorWorldRotation(FRotator(0.f, 1.f, 0.f));

	//DRAW_SPHERE(GetActorLocation());
	

}

