// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	//out parameter
	FVector HitLocation;
	if(GetSightRayHitLocation(HitLocation) )
	{
		AimingComponent->AimAt(HitLocation);
	}
}

void ATankPlayerController::CalculateScreenLocation(FVector2D& ScreenLocation) const
{
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	ScreenLocation.X = (float)ViewPortSizeX * this->CrossHairXLocation;
	ScreenLocation.Y = (float)ViewPortSizeY * this->CrossHairYLocation;
}

//Get world location if line trace through crosshair,true if it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//find the crosshair position
	FVector2D ScreenLocation;
	CalculateScreenLocation(ScreenLocation);

	FVector CameraWorldDirection;
	FVector WorldDirection;
	if (GetLookDirection(&ScreenLocation, CameraWorldDirection, WorldDirection))
	{		
		return GetLookVectorHitLocation(WorldDirection, OutHitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(const FVector2D* ScreenLocation, FVector& OutCameraWorldLocation, FVector& OutWorldDirection) const
{
	return DeprojectScreenPositionToWorld(ScreenLocation->X, ScreenLocation->Y, OutCameraWorldLocation, OutWorldDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& LookDirection, FVector& OutHitLocation) const
{
	FHitResult Result;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	
	if (GetWorld()->LineTraceSingleByChannel(Result, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = Result.Location;
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, 1.0,5.0,2.0);
		return true;
	}
	return false;
}