// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class URadialForceComponent;
class UParticleSystemComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* LaunchBlast;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* ImpactBlast;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* Explosion = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float DestroyDelay = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float ProjectileDamage = 20;

	UFUNCTION(BlueprintCallable, Category = Input)
	void OnHit(AActor * HitComponent, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit);

	void OnTimerExpire();




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float Speed);
	
};
