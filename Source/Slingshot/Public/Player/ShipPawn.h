// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PreferredDistanceParticle.h"
#include "ShipPawn.generated.h"

UCLASS()
class SLINGSHOT_API AShipPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShipPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(Category = Mesh, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MovementSpeed = 500;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		bool bUseShipMomentum = false;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float ShipLinearDamping = 0.6f;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float ShipAngularDamping = 0.8f;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FuelReserve = 1000.0f;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FuelUsageRate = 10.0f;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FuelRecoveryRate = 5.0f;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		bool bUseFuel = true;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		int32 numParticles = 6;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		bool bUseSword = false;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		bool bUseSpear = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bUseSeparateThrusterAxes = false;

	UPROPERTY(EditAnywhere)
		TArray<APreferredDistanceParticle*> Particles;

	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName ForwardThrustBinding;

};
