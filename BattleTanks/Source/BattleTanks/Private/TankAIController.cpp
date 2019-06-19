// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	
	
	if (!ensure(PlayerTank && ControlledTank)) { return ;}
	
	//move toward the player
	MoveToActor(PlayerTank, AcceptanceRadius);
	
	//aim at the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetTargetLocation());
	
	AimingComponent->Fire();
}