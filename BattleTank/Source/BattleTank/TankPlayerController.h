// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be the last include

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void virtual BeginPlay() override;

	//Get the tank to aim towards where the crosshair is pointing
	void AimTowardsCrosshair();

	

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	
	
private:

	virtual void SetPawn(APawn* InPawn) override;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 10000000;

	UFUNCTION()
	void OnTankDeathDelegate();

	void Tick(float DeltaSeconds) override;
	bool GetSightRayHitLocation(FVector & HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UTankAimingComponent* AimingComponent = nullptr;
};
