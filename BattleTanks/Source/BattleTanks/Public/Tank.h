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
	

};
