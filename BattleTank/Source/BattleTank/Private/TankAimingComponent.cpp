// Fill out your copyright notice in the Description page of Project Settings.

#include "public/TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	auto MyTankName = GetOwner()->GetName();
	
	if (!Barrel) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No barrel has been set!"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s is aiming from %s at %s"),*Barrel->GetComponentLocation().ToString(),*MyTankName, *HitLocation.ToString());
}

void UTankAimingComponent::SetBarrel(UStaticMeshComponent* BarrelToSet)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting the barrel to %s"), *BarrelToSet->GetName())
	Barrel = BarrelToSet;
}

