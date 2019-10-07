// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
 
//Forward Declarations
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK2_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;

	void AimTowardCrosshair() const;

	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, OUT FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float CrossHairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float LineTraceRange = 1000000;

};
