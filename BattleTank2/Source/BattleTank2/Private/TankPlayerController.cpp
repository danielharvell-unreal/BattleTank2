// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "BattleTank2.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair() const
{
	if(!GetControlledTank())
	{
		return;
	}


	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{

		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

		//Get world location if linetrace through crosshair, true if hits landscape
		//If it hits the landscape
			//Tell controlled tank to aim at this point

	}
}

bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	//"De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	GetLookDirection(ScreenLocation, LookDirection);

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line-trace along that LookDirection, and see what we hit (up to max range)

		if (GetLookVectorHitLocation(LookDirection, HitLocation))
		{
			GetControlledTank()->AimAt(HitLocation);
		}
	}


	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, OUT FVector& HitLocation) const
{
	struct FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility;
	const FCollisionQueryParams Params;
	const FCollisionResponseParams ResponseParam;

	auto HitSomething = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		TraceChannel, 
		Params, 
		ResponseParam
	);

	if (HitSomething)
	{
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0);
	return false;
}