// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	FVector AimDirection;
	double LastFireTime = 0.0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankAimingComponent();
	bool HasAimSollution(FVector& LaunchVelocity, const FVector& StarLocation, const FVector EndLocation, float LaunchSpeed);
	void MoveBarrelTowards(const FVector& AimDirection);
	void RotateTurretTowads(const FVector& AimDirection);
	bool IsBarrelMoving();
	void BindActionFire();
	int GetAmmo() const;

public:	
	// Sets default values for this component's properties
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* SetBarrel, UTankTurret* SetTurret);

	void AimAt(FVector Location);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3.0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4500.0;

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();
	
	EFiringState GetTankFiringState();
	
	UPROPERTY(BlueprintReadOnly, Category = "Tank")
	int Ammo = 13;


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState TankFiringState = EFiringState::Reloading;
	// Called when the game starts
	virtual void BeginPlay() override;
};