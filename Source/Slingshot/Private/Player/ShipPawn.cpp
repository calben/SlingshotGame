// Fill out your copyright notice in the Description page of Project Settings.

#include "Slingshot.h"
#include "ShipPawn.h"

const FName AShipPawn::MoveForwardBinding("MoveForward");
const FName AShipPawn::MoveRightBinding("MoveRight");

AShipPawn::AShipPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Game/Assets/Ships/DroneShip"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MeshComponent->SetStaticMesh(SphereMesh.Object);
	MeshComponent->SetMobility(EComponentMobility::Movable);
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->BodyInstance.bLockZTranslation = true;
	MeshComponent->SetEnableGravity(false);
	MeshComponent->SetLinearDamping(0.2f);
	MeshComponent->SetAngularDamping(0.8f);

	RootComponent = MeshComponent;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->TargetArmLength = 8000.f;
	CameraBoom->RelativeRotation = FRotator(-80.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

}

void AShipPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShipPawn::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);

	const FVector MoveDirection = FVector(GetInputAxisValue(MoveForwardBinding), GetInputAxisValue(MoveRightBinding), 0.f).GetClampedToMaxSize(1.0f);

	if (MoveDirection.SizeSquared() > 0.0f)
	{
		MeshComponent->AddForce(MeshComponent->GetForwardVector() * MeshComponent->GetMass() * MovementForceStrength * DeltaTime);
		MeshComponent->SetRelativeRotation(FRotator(FQuat::FastLerp(MeshComponent->RelativeRotation.Quaternion(), MoveDirection.Rotation().Quaternion(), 0.05f)), true);
	}

}

void AShipPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis(MoveForwardBinding);
	InputComponent->BindAxis(MoveRightBinding);
}

