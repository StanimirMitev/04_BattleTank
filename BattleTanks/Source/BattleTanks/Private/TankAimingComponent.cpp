// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* SetBarrel, UTankTurret* SetTurret)
{
	if(!ensure(SetBarrel && SetTurret)) { return; }

	Barrel = SetBarrel;
	Turret = SetTurret;
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

void UTankAimingComponent::AimAt(FVector Location)
{
	if (!ensure(Barrel && Turret)) { return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("GunPoint"));
	
	//if successfull print and normalize launch velocity
	if (HasAimSollution(OutLaunchVelocity, StartLocation, Location, LaunchSpeed))
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		RotateTurretTowads(AimDirection);
		MoveBarrelTowards(AimDirection);
	}
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
	if (!ensure(Barrel)) { return; }

	FRotator DeltaRotation = AimDirection.Rotation() - Barrel->GetForwardVector().Rotation();
	Barrel->Elevate(DeltaRotation.Pitch);
}

void UTankAimingComponent::RotateTurretTowads(const FVector& AimDirection)
{
	if (!ensure(Turret)) { return; }

	FRotator DeltaRotation = AimDirection.Rotation() - Turret->GetForwardVector().Rotation();
	Turret->Rotate(DeltaRotation.Yaw);
}

void UTankAimingComponent::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	// TODO fix
	if (!ensure(Barrel && Turret && ProjectileBlueprint)) { return; }

	FTransform SocketTransformDate = Barrel->GetSocketTransform("GunPoint");
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketTransformDate);
	if (!Projectile) { return; }
	Projectile->LaunchProjectile(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}