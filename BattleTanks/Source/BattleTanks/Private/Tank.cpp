// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshSocket.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	HealthPercentage = CurrentHealth / TankMaxHealth;
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

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float DamageToApply = FMath::Clamp<float>(DamageAmount, 0.0f, CurrentHealth);
	UE_LOG(LogTemp, Warning, TEXT("Damage Ammount: %f  || DamageToApply: %f"), DamageAmount, DamageToApply)
	CurrentHealth -= DamageToApply;
	UpdateHealthPercentage();
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank has gone kaboom"))
	}
	return DamageToApply;
}

void ATank::UpdateHealthPercentage()
{
	HealthPercentage = CurrentHealth / TankMaxHealth;
}