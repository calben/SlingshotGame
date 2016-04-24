// Fill out your copyright notice in the Description page of Project Settings.

#include "Slingshot.h"
#include "SlingshotUtils.h"


FVector USlingshotUtils::GetPointOnEdgeOfCircle(FVector location, float radius)
{
	float polarAngle = FMath::FRandRange(0, 6.28318531);
	FVector result;
	result.X = radius * FMath::Cos(polarAngle);
	result.Y = radius * FMath::Sin(polarAngle);
	result.Z = 0;
	result += location;
	return result;
}

