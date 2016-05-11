// Fill out your copyright notice in the Description page of Project Settings.

#include "Slingshot.h"
#include "PreferredDistanceParticle.h"
#include "ShipPawn.h"

const FName AShipPawn::MoveForwardBinding("MoveForward");
const FName AShipPawn::MoveRightBinding("MoveRight");
const FName AShipPawn::ForwardThrustBinding("ForwardThrust");

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
	MeshComponent->SetLinearDamping(ShipLinearDamping);
	MeshComponent->SetAngularDamping(ShipAngularDamping);
	MeshComponent->BodyInstance.bLockXRotation = true;
	MeshComponent->BodyInstance.bLockYRotation = true;


	RootComponent = MeshComponent;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->TargetArmLength = 20000.f;
	CameraBoom->RelativeRotation = FRotator(-80.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
}

void AShipPawn::BeginPlay()
{
	Super::BeginPlay();
	for (auto i = 0; i < numParticles; i++)
	{
		auto spawn_location = this->GetActorLocation();
		spawn_location.X -= 2000.0f;
		spawn_location.Y += i * 200.0f - numParticles / 2 * 200.0f;
		auto particle = GetWorld()->SpawnActor<APreferredDistanceParticle>(APreferredDistanceParticle::StaticClass(), spawn_location, FRotator::ZeroRotator);
		particle->AffectingActors.Add(this);
		particle->PreferredDistances.Add(2000.0f);
		particle->BaseSpeed = 10.0f;
		particle->SpeedExponential = 1.0f;
	}
}

void AShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bUseFuel)
		FuelReserve += FuelRecoveryRate;

	const FVector MoveDirection = FVector(GetInputAxisValue(MoveForwardBinding), GetInputAxisValue(MoveRightBinding), 0.f).GetClampedToMaxSize(1.0f);
	const float MoveDirectionSizeSquared = MoveDirection.SizeSquared();
	if (MoveDirectionSizeSquared > 0.2f)
	{
		MeshComponent->SetRelativeRotation(MoveDirection.Rotation());

		auto base_force = 1000 * MeshComponent->GetForwardVector() * MovementSpeed;
		auto input_thrust = 0.0f;
		if (bUseSeparateThrusterAxes)
		{
			input_thrust = GetInputAxisValue(ForwardThrustBinding);
		}
		else
		{
			input_thrust = MoveDirectionSizeSquared;
		}

		if (bUseFuel)
		{
			FuelReserve -= input_thrust * FuelUsageRate;
			if (FuelReserve < 0)
				FuelReserve = 0.0f;
		}

		if (bUseShipMomentum)
		{
			MeshComponent->AddForce(base_force * DeltaTime * MeshComponent->GetMass());
		}
		else
		{
			MeshComponent->SetPhysicsLinearVelocity(base_force / 50);
		}
	}
}

void AShipPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis(MoveForwardBinding);
	InputComponent->BindAxis(MoveRightBinding);
	InputComponent->BindAxis(ForwardThrustBinding);
}

