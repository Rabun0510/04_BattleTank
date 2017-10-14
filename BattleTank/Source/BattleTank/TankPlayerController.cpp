// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find an aiming component"));
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Aim at crosshair
	//UE_LOG(LogTemp, Warning, TEXT("Player controller ticking"));
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }

	FVector HitLocation; //Out parameter

	if (GetSightRayHitLocation(HitLocation)) 
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY); //Uses out parameters

	FVector2D ScreenLocation(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector LookDirection;
	
	//De-project to find the unit vector we are pointing at
	if (GetLookDirection(ScreenLocation, LookDirection)) 
	{

		//Draw a debug line for aiming
		

		if (GetLookVectorHitLocation(LookDirection, OutHitLocation))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Pointing at location: %s"), *OutHitLocation.ToString());
			return true;
		}		
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection)  const
{
	FVector CameraWorldLocation;

	DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	);

	//UE_LOG(LogTemp, Warning, TEXT("Pointing in direction: %s"), *LookDirection.ToString());

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = StartLocation + LineTraceRange * LookDirection;

	//UKismetSystemLibrary::DrawDebugLine(GetWorld(), StartLocation, LineTraceEnd, FLinearColor::Red, 1.0, 3.0);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, LineTraceEnd, ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		//UKismetSystemLibrary::DrawDebugCircle(GetWorld(), HitLocation, 10, 12, FLinearColor::Red, 1, 10);
		return true;
	}
	HitLocation = FVector(0.0);
	return false;
}