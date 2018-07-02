// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"
#include "Public/Projectile.h"
#include "Public/TankMovementComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshSocket.h"
#include "Public/TankTurret.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelComponent)
{
	if (!BarrelComponent) { return; }
	
	TankAimingComponent->SetBarrelReference(BarrelComponent);
	BarrelPtr = BarrelComponent;
}

void ATank::SetTurretReference(UTankTurret* TurretComponent)
{
	if (!TurretComponent) { return; }
	
	TankAimingComponent->SetTurretReference(TurretComponent);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (!BarrelPtr || !isReloaded) { return; }
	
	FTransform SocketTransformDate = BarrelPtr->GetSocketTransform("GunPoint");
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketTransformDate);
	if (!Projectile) { return; }
	Projectile->LaunchProjectile(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}