// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "BattleTank2.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	
	if (PlayerTank)
	{
		//Todo move towards player 

		//Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//fire if ready
		ControlledTank->Fire();
	}
}