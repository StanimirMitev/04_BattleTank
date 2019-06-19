// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Camera/PlayerCameraManager.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimComponentRef);

private:
	//start moving the barrel of the tank so that the shot can hit where th crosshair intersects the world
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	void CalculateScreenLocation(FVector2D& ScreenLocation) const;

	bool GetLookDirection(const FVector2D* ScreenLocation, FVector& OutCameraWorldLocation, FVector& OutWorldDirection) const;

	bool GetLookVectorHitLocation(FVector& StartLocation, FVector& EndLocation) const;

public:

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
};
