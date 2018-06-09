// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector Location, float LaunchSpeed)
{
	if (!Barrel || !Turret) { return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("GunPoint"));
	
	//if successfull print and normalize launch velocity
	if (HasAimSollution(OutLaunchVelocity, StartLocation, Location, LaunchSpeed))
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		RotateTurretTowads(AimDirection);
		MoveBarrelTowards(AimDirection);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("%f: failed to find solution"), GetWorld()->GetTimeSeconds())
	}

}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelComponent)
{
	this->Barrel = BarrelComponent;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretComponent)
{
	this->Turret = TurretComponent;
}

bool UTankAimingComponent::HasAimSollution(FVector& LaunchVelocity, const FVector& StarLocation, const FVector EndLocation, float LaunchSpeed)
{
	return UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		LaunchVelocity,
		StarLocation,
		EndLocation,
		LaunchSpeed,
		false,
		0.0,
		0.0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	if (!Barrel) { return; }
	FRotator DeltaRotation = AimDirection.Rotation() - Barrel->GetForwardVector().Rotation();
	Barrel->Elevate(DeltaRotation.Pitch);
}

void UTankAimingComponent::RotateTurretTowads(const FVector& AimDirection)
{
	if (!Turret) { return; }
	FRotator DeltaRotation = AimDirection.Rotation() - Turret->GetForwardVector().Rotation();
	Turret->Rotate(DeltaRotation.Yaw);
}