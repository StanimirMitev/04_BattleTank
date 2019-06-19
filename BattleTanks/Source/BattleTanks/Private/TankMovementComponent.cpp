// Fill out your copyright notice in the Description page of Project Settings.

#include "PUblic/TankMovementComponent.h"
#include "Public/TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(TrackRight && TrackLeft)) { return; }

	TrackRight->SetThrottle(Throw);
	TrackLeft->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurn(float Throw)
{
	if (!ensure(TrackRight && TrackLeft)) { return; }
	TrackRight->SetThrottle(-Throw);
	TrackLeft->SetThrottle(Throw);
}

void UTankMovementComponent::Initialise(UTankTrack* SetRightTrack, UTankTrack* SetLeftTrack)
{
	if (!ensure(SetRightTrack && SetLeftTrack)) { return; }
	
	TrackRight = SetRightTrack;
	TrackLeft = SetLeftTrack;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntension  = MoveVelocity.GetSafeNormal();
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntension);
	IntendMoveForward(ForwardThrow);
	FVector SideTurnThrow = FVector::CrossProduct(TankForward, AIForwardIntension);
	IntendTurn(SideTurnThrow.Z);
}
