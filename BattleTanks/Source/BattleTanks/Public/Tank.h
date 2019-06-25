// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:	
	// Called every frame
	ATank();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;
private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float TankMaxHealth = 100;
	UPROPERTY(EditAnywhere, Category = "Health")
	float CurrentHealth = TankMaxHealth;
};
