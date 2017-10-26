// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile movement component"));
	ProjectileMovementComponent->bAutoActivate = false;

	//Instantiate the static mesh component
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	//Instantiate the particle system component
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch blast"));
	//LaunchBlast->SetupAttachment(CollisionMesh, FName("LaunchBlast"));

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact blast"));
	ImpactBlast->bAutoActivate = false;

	LaunchBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);

	Explosion = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion"));
	Explosion->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//UE_LOG(LogTemp, Warning, TEXT("Particle spawn location %s"), *LaunchBlast->GetComponentLocation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Collision mesh spawn location %s"), *CollisionMesh->GetComponentLocation().ToString());

	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::OnHit(AActor * HitComponent, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	Explosion->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::OnTimerExpire, DestroyDelay, false);

	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),
		Explosion->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>());
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed) 
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
}

