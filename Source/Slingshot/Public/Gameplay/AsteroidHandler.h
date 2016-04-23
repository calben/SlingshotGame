// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "GameFramework/Actor.h"
#include "AsteroidHandler.generated.h"


UENUM(BlueprintType)
enum class EBodySpawnShape : uint8
{
	Disc 		UMETA(DisplayName = "Disc"),
	Random		UMETA(DisplayName = "Random")
};

UCLASS()
class SLINGSHOT_API AAsteroidHandler : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAsteroidHandler();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Template")
		TSubclassOf<class AActor> AsteroidTemplate;

	UPROPERTY(EditAnywhere)
		EBodySpawnShape BodySpawnShape = EBodySpawnShape::Disc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaximumNumberOfBodies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere)
		TArray<AActor*> Asteroids;

	AActor* SpawnAsteroid();

	UFUNCTION()
		void OnBoxOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnBoxOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
