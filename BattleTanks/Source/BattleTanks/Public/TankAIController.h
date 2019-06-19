// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "AIController.h"
#include "TankAIController.generated.h"


UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	//the minimum distance the ai can come close to the player
	float AcceptanceRadius = 3000;

public:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
};
