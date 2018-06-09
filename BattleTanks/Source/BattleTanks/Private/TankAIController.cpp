// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* PlayerTank = GetPlayerControlledTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController cant find player tank"), *(PlayerTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *(PlayerTank->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerControlledTank() const
{
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank) {return nullptr;}
	return Cast<ATank>(PlayerTank);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardEnemy();
}

void ATankAIController::AimTowardEnemy()
{
	//change to enemy in range
	if (!GetPlayerControlledTank()) { return; }

	FVector HitLocation = GetPlayerControlledTank()->GetTargetLocation();
	//chech if line of sight is available
		//aim at enemy tank
		GetControlledTank()->AimAt(HitLocation);
		//fire
}
