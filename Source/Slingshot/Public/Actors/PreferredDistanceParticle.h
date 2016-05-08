// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PreferredDistanceParticle.generated.h"

UCLASS()
class SLINGSHOT_API APreferredDistanceParticle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APreferredDistanceParticle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
		TArray<AActor*> AffectingActors;

	UPROPERTY(EditAnywhere)
		TArray<float> PreferredDistances;

	UPROPERTY(EditAnywhere)
		float BaseSpeed = 1000.0f;

	UPROPERTY(EditAnywhere)
		float SpeedExponential = 2.0f;
	
};
