// Fill out your copyright notice in the Description page of Project Settings.

#include "public/TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed) {

	//Clamp relative speed
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto ClampedNewElevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(ClampedNewElevation, 0.0, 0.0));
}


