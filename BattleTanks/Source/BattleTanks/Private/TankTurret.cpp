// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTurret.h"

void UTankTurret::Rotate(float RotationSpeed)
{
	RotationSpeed = FMath::Clamp<float>(RotationSpeed, -1.0, 1.0);
	float NewRotaion = RelativeRotation.Yaw + RotationSpeed * MaxRotationAngle * GetWorld()->DeltaTimeSeconds;
	SetRelativeRotation(FRotator(0.0, NewRotaion, 0.0));
}

