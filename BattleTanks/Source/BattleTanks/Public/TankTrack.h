// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	virtual void BeginPlay() override;
	UTankTrack();
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivinfForce = 56000;
private:

	TArray<class ASprungWheel*> GetWheel() const;

	void DriveTrack(float CurrentTrottle);
};
