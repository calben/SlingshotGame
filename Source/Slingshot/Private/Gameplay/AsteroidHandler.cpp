// Fill out your copyright notice in the Description page of Project Settings.

#include "Slingshot.h"
#include "AsteroidHandler.h"

AAsteroidHandler::AAsteroidHandler()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetCollisionProfileName("OverlapAll");
	BoxCollision->SetSimulatePhysics(true);
	BoxCollision->AttachTo(RootComponent);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAsteroidHandler::OnBoxOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AAsteroidHandler::OnBoxOverlapEnd);

}

void AAsteroidHandler::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < MaximumNumberOfBodies; i++)
	{
		Asteroids.Add(SpawnAsteroid());
	}
}

AActor* AAsteroidHandler::SpawnAsteroid()
{
	FVector extent = BoxCollision->GetScaledBoxExtent();
	auto x = FMath::FRandRange(-extent.X, extent.X) + BoxCollision->GetComponentLocation().X;
	auto y = FMath::FRandRange(-extent.Y, extent.Y) + BoxCollision->GetComponentLocation().Y;
	auto z = 0.0f;
	AActor* body = GetWorld()->SpawnActor<AActor>(AsteroidTemplate, FVector(x, y, z), FRotator::ZeroRotator);
	return body;
}

void AAsteroidHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAsteroidHandler::OnBoxOverlapEnd(AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("COLLISION ENDED!"));
}

void AAsteroidHandler::OnBoxOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("COLLISION BEGUN!"));
}
