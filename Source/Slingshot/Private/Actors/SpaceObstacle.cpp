// Fill out your copyright notice in the Description page of Project Settings.

#include "Slingshot.h"
#include "SpaceObstacle.h"


// Sets default values
ASpaceObstacle::ASpaceObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetMobility(EComponentMobility::Movable);
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->BodyInstance.bLockZTranslation = true;
	MeshComponent->SetEnableGravity(false);
	RootComponent = MeshComponent;

}

// Called when the game starts or when spawned
void ASpaceObstacle::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->SetLinearDamping(0.0f);
	MeshComponent->SetAngularDamping(0.8f);
	
}

// Called every frame
void ASpaceObstacle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

