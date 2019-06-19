// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* SetRightTrack, UTankTrack* SetLeftTrack);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurn(float Throw);


private:
	//Called from the pathfinding logic by the AI contrllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	UTankTrack* TrackRight = nullptr;
	UTankTrack* TrackLeft = nullptr;
};
