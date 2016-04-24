// Fill out your copyright notice in the Description page of Project Settings.

#include "Slingshot.h"
#include "SlingshotUtils.h"
#include "SpaceObstacle.h"
#include "AsteroidHandler.h"

AAsteroidHandler::AAsteroidHandler()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetCollisionProfileName("OverlapAll");
	SphereCollision->SetSphereRadius(1000.0f);
	SphereCollision->AttachTo(RootComponent);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AAsteroidHandler::OnSphereOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AAsteroidHandler::OnSphereOverlapEnd);

}

void AAsteroidHandler::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < MaximumNumberOfBodies; i++)
	{
		Asteroids.Add(SpawnAsteroidWithinSphere());
	}
}

AActor* AAsteroidHandler::SpawnAsteroidWithinSphere()
{
	FVector spawn_location;
	spawn_location = FMath::VRand();
	spawn_location.Z = 0;
	spawn_location *= SphereCollision->GetScaledSphereRadius();
	spawn_location = spawn_location.GetClampedToSize2D(0, SphereCollision->GetScaledSphereRadius());
	ASpaceObstacle* body = GetWorld()->SpawnActor<ASpaceObstacle>(AsteroidTemplate, spawn_location, FRotator::ZeroRotator);
	body->MeshComponent->AddImpulse(FMath::VRand() * body->MeshComponent->GetMass() * 1000);
	return body;
}

AActor* AAsteroidHandler::SpawnAsteroidOnEdgeOfSphere()
{
	FVector spawn_location = USlingshotUtils::GetPointOnEdgeOfCircle(SphereCollision->GetComponentLocation(), SphereCollision->GetScaledSphereRadius());
	ASpaceObstacle* body = GetWorld()->SpawnActor<ASpaceObstacle>(AsteroidTemplate, spawn_location, FRotator::ZeroRotator);
	body->MeshComponent->AddImpulse(FMath::VRand() * body->MeshComponent->GetMass() * 1000);
	return body;
}

void AAsteroidHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAsteroidHandler::OnSphereOverlapBegin(AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

void AAsteroidHandler::OnSphereOverlapEnd(AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetClass()->IsChildOf(ASpaceObstacle::StaticClass()))
	{
		OtherActor->Destroy();
		Asteroids.Add(SpawnAsteroidOnEdgeOfSphere());
	}
}
