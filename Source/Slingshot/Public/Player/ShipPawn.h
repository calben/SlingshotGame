// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
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
		float MovementForceStrength = 200000;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FueldReserve = 1000;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		bool bUseFueld = true;

	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	
};
