// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (PlayerTank)
	{
		//move toward the player
		MoveToActor(PlayerTank, AcceptanceRadius);
		//aim at the player
		ControlledTank->AimAt(PlayerTank->GetTargetLocation());
		//fire at the player
		ControlledTank->Fire();
	}
}