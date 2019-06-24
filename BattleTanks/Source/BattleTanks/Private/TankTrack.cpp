// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"
#include "Runtime/Engine/Classes/Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce()
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//calculate the required acceleration to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//calculate and apply sideways
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass()* CorrectionAcceleration) / 2; //two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentTrottle = FMath::Clamp<float>(CurrentTrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentTrottle * TrackMaxDrivinfForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentTrottle = 0;
}


