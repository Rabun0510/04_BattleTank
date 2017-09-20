// Fill out your copyright notice in the Description page of Project Settings.
#include "../Public/TankAIController.h"
#include "Engine/World.h"


void ATankAIController::Tick(float DeltaTime)
{
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank)
	{
		auto AITank = Cast<ATank>(GetPawn());
		AITank->AimAt(PlayerTank->GetActorLocation());
		AITank->Fire();
	}
		
		
}


