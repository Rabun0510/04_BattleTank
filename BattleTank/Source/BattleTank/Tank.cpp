// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Public/TankBarrel.h"
#include "Engine/StaticMeshSocket.h"
#include "Public/Projectile.h"
#include "Engine/World.h"
#include "Public/TankMovementComponent.h"
#include "TankPlayerController.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATank::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	//UE_LOG(LogTemp, Warning, TEXT("DamageAmount=%f, DamageToApply=%i"), Damage, DamageToApply);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("%s is broadcasting OnDeath!"), *GetName());
		
	}

	return 0.0f;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartupHealth;
}



