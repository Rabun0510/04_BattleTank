// Fill out your copyright notice in the Description page of Project Settings.
#include "../Public/TankAIController.h"
#include "../Public/TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"


void ATankAIController::Tick(float DeltaTime)
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (PlayerTank)
	{
		//Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		auto AITank = GetPawn();
		auto AimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		if (AimingComponent->GetFiringState() ==  EFiringStatus::Locked)
		{ 
			AimingComponent->Fire();
		}
		//AITank->Fire();
	}
		
		
}

void ATankAIController::SetPawn(APawn * Pawn)
{
	Super::SetPawn(Pawn);
	if (Pawn)
	{
		auto PossessedTank = Cast<ATank>(Pawn);
		if (!ensure(PossessedTank))
		{
			return;
		}

		//Subscribe to OnDeath of ATank
	}
}
