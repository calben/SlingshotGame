// Fill out your copyright notice in the Description page of Project Settings.

#include "Slingshot.h"
#include "GravityComponent.h"


UGravityComponent::UGravityComponent()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetCollisionProfileName("OverlapAll");
	SphereCollision->AttachTo(GetAttachmentRoot());

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &UGravityComponent::OnSphereOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &UGravityComponent::OnSphereOverlapEnd);
}

void UGravityComponent::BeginPlay()
{
	Super::BeginPlay();
	GetAttachmentRootActor()->GetOverlappingActors(AffectedActorsArray);
}

void UGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	for (AActor* actor : AffectedActorsArray)
	{
		TArray<UStaticMeshComponent*> comps;

		actor->GetComponents(comps);
		for (auto StaticMeshComponent : comps)
		{
			if (StaticMeshComponent->IsSimulatingPhysics())
			{
				const FVector direction = (StaticMeshComponent->GetComponentLocation() - this->GetComponentLocation()) * GravityPower;
				StaticMeshComponent->AddForce(direction);
			}
		}
	}
}

void UGravityComponent::OnSphereOverlapBegin(AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AffectedActorsArray.Add(OtherActor);
}

void UGravityComponent::OnSphereOverlapEnd(AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AffectedActorsArray.Remove(OtherActor);
}
