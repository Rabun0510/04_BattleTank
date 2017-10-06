// Fill out your copyright notice in the Description page of Project Settings.
#include "../Public/TankAIController.h"
#include "../Public/TankAimingComponent.h"
#include "Engine/World.h"


void ATankAIController::Tick(float DeltaTime)
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (PlayerTank)
	{
		//Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		auto AITank = GetPawn();
		AITank->FindComponentByClass<UTankAimingComponent>()->AimAt(PlayerTank->GetActorLocation());
		//AITank->Fire();
	}
		
		
}


