// Fill out your copyright notice in the Description page of Project Settings.

#include "PUblic/TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * (GetWorld()->DeltaTimeSeconds);
	auto RawNewElevation = FMath::Clamp<float>((RelativeRotation.Pitch + ElevationChange), MinElevationDegree, MaxElevationDegree);
	SetRelativeRotation(FRotator(RawNewElevation, 0.0, 0.0));
}
