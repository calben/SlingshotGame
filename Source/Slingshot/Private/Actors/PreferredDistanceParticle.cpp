// Fill out your copyright notice in the Description page of Project Settings.

#include "Slingshot.h"
#include "PreferredDistanceParticle.h"


// Sets default values
APreferredDistanceParticle::APreferredDistanceParticle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Assets/Auxiliary/PreferredDistanceParticle"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetStaticMesh(Mesh.Object);
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MeshComponent->SetMobility(EComponentMobility::Movable);
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->BodyInstance.bLockZTranslation = true;
	MeshComponent->BodyInstance.bLockRotation = true;
	MeshComponent->SetEnableGravity(false);
	MeshComponent->SetLinearDamping(0.05f);
	MeshComponent->SetAngularDamping(1.0f);
}

// Called when the game starts or when spawned
void APreferredDistanceParticle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APreferredDistanceParticle::Tick( float DeltaTime )
{
	// MeshComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
	Super::Tick( DeltaTime );
	for (auto i = 0; i < AffectingActors.Num(); i++)
	{
		auto distance = FVector::Dist(AffectingActors[i]->GetActorLocation(), this->GetActorLocation());
		auto forward_direction = AffectingActors[i]->GetActorLocation() - this->GetActorLocation();
		auto distance_from_optimal = forward_direction.Size() - PreferredDistances[i];
		forward_direction /= forward_direction.Size();
		auto force = forward_direction * BaseSpeed * FMath::Pow(FMath::Abs(distance_from_optimal), SpeedExponential) * MeshComponent->GetMass();
		if (distance_from_optimal > 0)
			MeshComponent->AddForce(PushMultiplier * force);
		else
			MeshComponent->AddForce(PullMultiplier * -force);
	}
}

