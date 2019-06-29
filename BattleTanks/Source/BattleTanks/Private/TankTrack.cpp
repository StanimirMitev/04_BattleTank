// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"
#include "SprungWheel.h"
#include "SpawnConmponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTrack::DriveTrack(float CurrentTrottle)
{
	auto ForceApplied = CurrentTrottle * TrackMaxDrivinfForce;
	auto Wheels = GetWheel();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentTrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentTrottle);
}



TArray<ASprungWheel*> UTankTrack::GetWheel() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnConmponent>(Child);
		if (!SpawnPointChild) { continue; }

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) {continue;}
		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}

