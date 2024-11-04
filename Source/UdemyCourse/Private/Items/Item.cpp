// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
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
		
		// FVector ActorLocation = GetActorLocation();
		//DrawDebugSphere(World, ActorLocation, 50.f, THIRTY_SECONDS, FColor::Black, true, -1.f, 0, 1.f);

		//SetActorLocation(FVector(Location.X, Location.Y, Location.Z + 10.f));
		// SetActorRotation(FRotator(0.f, 45.f, 0.f));
		// FVector Location = GetActorLocation();
		// FVector ForwardVector = GetActorForwardVector();
		//
		// DRAW_VECTOR(Location, Location + ForwardVector * 1000.f);
	}
	// float averageFloat = Average<float>(1.f, 2.f);
	// UE_LOG(LogTemp, Warning, TEXT("Average of 1 and 2 is: %f"), averageFloat);
	// int32 averageInt = Average<int32>(1, 2);
	//
	// UE_LOG(LogTemp, Warning, TEXT("Average of 1 and 2 is: %d"), averageInt);
	//
	// FVector vectorToSum = FVector(1.f, 1.f, 1.f);
	//
	// FVector vectorResult = Average<FVector>(vectorToSum, vectorToSum);
	// UE_LOG(LogTemp, Warning, TEXT("Average of 1 and 2 is: %d"), vectorResult);

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
	const FString MainActorName = OverlappedComponent->GetName();

	const FString OtherActorName = OtherActor->GetName();
	const FString OtherCompName = OtherComp->GetName();
	if (GEngine)
	{
		// GEngine->AddOnScreenDebugMessage(2, 30.f, FColor::Red, MainActorName);
		//
		// GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, OtherActorName);
		// GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, OtherCompName);
		 GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, TEXT("BeginOberlap"));
		

		
	}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	FString MainActorName = OverlappedComponent->GetName();
	FString OtherActorName = OtherActor->GetName();
	FString OtherCompName = OtherComp->GetName();
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(2, 30.f, FColor::Red, TEXT("EndOverlap"));

		
		
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

