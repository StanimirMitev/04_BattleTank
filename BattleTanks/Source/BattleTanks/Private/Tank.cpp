// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshSocket.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = TankMaxHealth;
	HealthPercentage = CurrentHealth / TankMaxHealth;
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float DamageToApply = FMath::Clamp<float>(DamageAmount, 0.0f, CurrentHealth);
	CurrentHealth -= DamageToApply;
	UpdateHealthPercentage();
	if (CurrentHealth <= 0)
	{
		OnTankDeath.Broadcast();
	}
	return DamageToApply;
}

void ATank::UpdateHealthPercentage()
{
	HealthPercentage = CurrentHealth / TankMaxHealth;
}

//FTankDelegate ATank::OnTankDeath()
//{
//	
//}