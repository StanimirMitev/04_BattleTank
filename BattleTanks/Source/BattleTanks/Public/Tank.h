// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankTurret;
class UTankBarrel;
class UTankAimingComponent;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.0;
	
	double LastFireTime = 0.0;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4500.0;

	void BindActionFire();

protected:
	UTankBarrel* BarrelPtr;
	UTankAimingComponent * TankAimingComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovement = nullptr;
public:	
	// Called every frame
	ATank();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	void AimAt(FVector HitLocation);
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelComponent);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretComponent);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();
};
